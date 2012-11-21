#include <GL/glew.h> // glew must be included before the main gl libs
#include <GL/glut.h> // doing otherwise causes compiler shouting
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <chrono>
#include <math.h>
#include <vector>
//#include "Vertex.cpp" 

#include "loadOBJ.cpp"
#include "boxWall.cpp"

#include "Object.cpp"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp" //Makes passing matrices to shaders easier

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

#include </home/other/hostetle/2013/Graphics/Box2D_v2.1.2/Box2D/Box2D/Box2D.h>


using namespace std;

//--Evil Global variables
int w = 640, h = 480;// Window size

GLuint program;// The GLSL program handle

// VBO's for all objects ( Vertex Buffer Object )
GLuint vbo_Wall;
GLuint vbo_Sphere;
GLuint vbo_Floor;
GLuint vbo_Start;
GLuint vbo_Finish;
GLuint vbo_Dragon;

// UVB's for all objects ( Uniform Vertex Buffer ? )

// NBO's for all objects ( Normal Buffer Object )
GLuint nbo_Floor;


// textures
std::string tex1 = "textures/test.png";
std::string tex2 = "textures/images.jpeg";

//uniform locations
GLuint MVP_ID;  // MVP Matrix Handle
GLuint View_ID;  // View Matrix Handle
GLuint Model_ID;  // Model Matrix Handle
GLuint WORLD_ID:   // World Matrix Handle

GLuint loc_numLights;
GLuint loc_sampler;
GLuint loc_eyeWorldPos;
GLuint loc_BaseColor;
GLuint loc_BaseAI;
GLuint loc_Direction;
GLuint loc_BaseDI;
GLuint loc_SpecInt;
GLuint loc_SpecPower;

//attribute locations
GLint loc_position;
GLint loc_normal;
GLint loc_color;

// Rotation variables
float ROTATIONX = 0.0, TEMPX = 0.0;
float ROTATIONZ = 0.0, TEMPZ = 0.0;
float X_COUNT = 0.0;
float Z_COUNT = 0.0;
float MAX_ROT = 20.0;
float MAX_BALL = 21.5;
float xMove, yMove, zMove;
float oldXAngle = 0.0, oldYAngle = 0.0;
bool Paused = false, RESET = false;
bool showPos = false, dead = false;
float MIN_DISTANCE = 2.5;

glm::vec3 eyePosition = (0.0, 80.0, -0.1);

float oldMouse[2] = { 0, 0 };
bool MOUSE_MOVING = false;
bool dragonToggle = false;
bool won = false;

// lights
// Lighting Variables
GLint h_LightPosition,
  h_AmbientProduct,
  h_DiffuseProduct,
  h_SpecularProduct,
  h_Shineness,
  h_gSampler;


// setup the array of walls
vector< boxWall > listOfWalls;

vector<Obj> objectList;

//transform matrices
/*
glm::mat4 board;//obj->world each object should have its own board matrix
glm::mat4 ball;//obj->world each object should have its own ball matrix
glm::mat4 floorMat;//obj->world each object should have its own floor matrix
glm::mat4 Start;//obj->world each object should have its own Start matrix
glm::mat4 Finish;//obj->world each object should have its own Finish matrix
glm::mat4 Dragon;//obj->world each object should have its own Dragon matrix
*/

glm::mat4 view;//world->eye
glm::mat4 projection;//eye->clip
glm::mat4 world; // world matrix
glm::mat4 mvpWall;//premultiplied boardviewprojection
glm::mat4 mvpBall;//premultiplied ballviewprojection
glm::mat4 mvpFloor;//premultiplied floorviewprojection
glm::mat4 mvpStart;//premultiplied startviewprojection
glm::mat4 mvpFinish;//premultiplied finishviewprojection
glm::mat4 mvpDragon;//premultiplied finishviewprojection

//--GLUT Callbacks
void render();
void update();
void reshape(int n_w, int n_h);
void keyboard(unsigned char key, int x_pos, int y_pos);
void keyup(unsigned char key, int x_pos, int y_pos);
void mouseMove( int x, int y );

//--Resource management
bool initialize();
void cleanUp();

//--Random time things
float getDT();
  chrono::time_point<  chrono::high_resolution_clock> t1,t2; 

// read file function
char *textFileRead( const char *);

bool DoTheImportThing( const std::string& pFile);

// load the obj file function
Vertex* loadOBJ( char* , float , float , float );

// menu prototype
void menu( int id );

// distance function
float dist( float, float, float, float );

// load the dragon file
bool loadDragonFile( const string& fileName );

// analyze dragon scene taken from  assimp readFile (loadDragonFile function )
void  processDragon( const aiScene* );

// function to setup the list of walls
void setupWalls();

// check the ball against where the walls are
bool checkForWalls( float, float, float &, float & );

// setup shader stuff
void init_shader_variables()

//--Main
int main(int argc, char **argv)
{
    // Initialize glut
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(w, h);
    // Name and create the Window
    glutCreateWindow("Awesome Labyrinth Game");

    // Now that the window is created the GL context is fully set up
    // Because of that we can now initialize GLEW to prepare work with shaders
    GLenum status = glewInit();
    if( status != GLEW_OK)
    {
          cerr << "[F] GLEW NOT INITIALIZED: ";
          cerr << glewGetErrorString(status) <<   endl;
        return -1;
    }

    // Set all of the callbacks to GLUT that we need
    glutDisplayFunc(render);// Called when its time to display
    glutReshapeFunc(reshape);// Called if the window is resized
    glutIdleFunc(update);// Called if there is nothing else to do
    glutKeyboardFunc(keyboard);// Called if there is keyboard input
    glutKeyboardUpFunc(keyup);// Called if there is keyboard input
    glutPassiveMotionFunc(mouseMove);// Called if the mouse is moved

    // setup the menu
    glutCreateMenu( menu );
    glutAddMenuEntry( "Start", 1);
    glutAddMenuEntry( "Pause/Resume", 2);
    glutAddMenuEntry( "Quit", 3);
    glutAttachMenu( GLUT_RIGHT_BUTTON );
    

    // Initialize all of our resources(shaders, geometry)
    bool init = initialize();
    if(init)
    {
        t1 =   chrono::high_resolution_clock::now();
        glutMainLoop();
    }

    // Clean up after ourselves
    cleanUp();
    return 0;
}

//--Implementations
void render()
{
    //--Render the scene

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    //clear the screen
    glClearColor(0.0, 0.0, 0.2, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //premultiply the matrix for this example
    mvpWall = projection * view * board;
    mvpBall = projection * view * ball;
    mvpFloor = projection * view * floorMat;
    mvpStart = projection * view * Start;
    mvpFinish = projection * view * Finish;
    mvpDragon = projection * view * Dragon;

    //enable the shader program
    glUseProgram(program);

    // setup the lights
    //setupLights();

// do rendering on the walls
    //upload the matrix to the shader
    glUniformMatrix4fv(MVP_ID, 1, GL_FALSE, glm::value_ptr(mvpWall));

    //set up the Vertex Buffer Object so it can be drawn
    glEnableVertexAttribArray(loc_position);
    glEnableVertexAttribArray(loc_color);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_Wall);
    //set pointers into the vbo for each of the attributes(position and color)
    glVertexAttribPointer( loc_position,//location of attribute
                           3,//number of elements
                           GL_FLOAT,//type
                           GL_FALSE,//normalized?
                           sizeof(Vertex),//stride
                           0);//offset

    glVertexAttribPointer( loc_color,
                           3,
                           GL_FLOAT,
                           GL_FALSE,
                           sizeof(Vertex),
                           (void*)offsetof(Vertex,color));

    glDrawArrays(GL_TRIANGLES, 0, 10000);//mode, starting index, count

    //clean up
    glDisableVertexAttribArray(loc_position);
    glDisableVertexAttribArray(loc_color);


// do the same for the ball
    //upload the matrix to the shader
    glUniformMatrix4fv(MVP_ID, 1, GL_FALSE, glm::value_ptr(mvpBall));

    //set up the Vertex Buffer Object so it can be drawn
    glEnableVertexAttribArray(loc_position);
    glEnableVertexAttribArray(loc_color);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_Sphere);
    //set pointers into the vbo for each of the attributes(position and color)
    glVertexAttribPointer( loc_position,//location of attribute
                           3,//number of elements
                           GL_FLOAT,//type
                           GL_FALSE,//normalized?
                           sizeof(Vertex),//stride
                           0);//offset

    glVertexAttribPointer( loc_color,
                           3,
                           GL_FLOAT,
                           GL_FALSE,
                           sizeof(Vertex),
                           (void*)offsetof(Vertex,color));

    glDrawArrays(GL_TRIANGLES, 0, 10000);//mode, starting index, count

    //clean up
    glDisableVertexAttribArray(loc_position);
    glDisableVertexAttribArray(loc_color);

// do the same for the floor


    //upload the matrixes to the shader
    //glUniformMatrix4fv( MVP_ID, 1, GL_FALSE, &mvpFloor[0][0]);
    //glUniformMatrix4fv( Model_ID, 1, GL_FALSE, &floorMat[0][0]);
    //glUniformMatrix4fv( View_ID, 1, GL_FALSE, &view[0][0]);

    glUniformMatrix4fv(MVP_ID, 1, GL_FALSE, glm::value_ptr(mvpFloor));

    //set up the Vertex Buffer Object so it can be drawn
    glEnableVertexAttribArray( loc_position );
    glDisableVertexAttribArray( loc_color );
//    glEnableVertexAttribArray( loc_color );
    glBindBuffer(GL_ARRAY_BUFFER, vbo_Floor);
    //set pointers into the vbo for each of the attributes(position and color)
    glVertexAttribPointer( loc_position,//location of attribute
                           3,//number of elements
                           GL_FLOAT,//type
                           GL_FALSE,//normalized?
                           sizeof(Vertex),//stride
                           0);//offset
/*
    glVertexAttribPointer( loc_color,
                           3,
                           GL_FLOAT,
                           GL_FALSE,
                           sizeof(Vertex),
                           (void*)offsetof(Vertex,color));

*/
    glEnableVertexAttribArray( loc_normal );
    glBindBuffer(GL_ARRAY_BUFFER, nbo_Floor);
    glVertexAttribPointer( loc_normal,//location of attribute
                           3,//number of elements
                           GL_FLOAT,//type
                           GL_FALSE,//normalized?
                           sizeof(glm::vec3),//stride
                           0);//offset

    glDrawArrays(GL_TRIANGLES, 0, 10000);//mode, starting index, count



// do the same for the Start
    //upload the matrix to the shader
    glUniformMatrix4fv(MVP_ID, 1, GL_FALSE, glm::value_ptr(mvpStart));

    //set up the Vertex Buffer Object so it can be drawn
    glEnableVertexAttribArray(loc_position);
    glEnableVertexAttribArray(loc_color);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_Start);
    //set pointers into the vbo for each of the attributes(position and color)
    glVertexAttribPointer( loc_position,//location of attribute
                           3,//number of elements
                           GL_FLOAT,//type
                           GL_FALSE,//normalized?
                           sizeof(Vertex),//stride
                           0);//offset

    glVertexAttribPointer( loc_color,
                           3,
                           GL_FLOAT,
                           GL_FALSE,
                           sizeof(Vertex),
                           (void*)offsetof(Vertex,color));

    glDrawArrays(GL_TRIANGLES, 0, 1000);//mode, starting index, count


// do the same for the Finish
    //upload the matrix to the shader
    glUniformMatrix4fv(MVP_ID, 1, GL_FALSE, glm::value_ptr(mvpFinish));

    //set up the Vertex Buffer Object so it can be drawn
    glEnableVertexAttribArray(loc_position);
    glEnableVertexAttribArray(loc_color);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_Finish);
    //set pointers into the vbo for each of the attributes(position and color)
    glVertexAttribPointer( loc_position,//location of attribute
                           3,//number of elements
                           GL_FLOAT,//type
                           GL_FALSE,//normalized?
                           sizeof(Vertex),//stride
                           0);//offset

    glVertexAttribPointer( loc_color,
                           3,
                           GL_FLOAT,
                           GL_FALSE,
                           sizeof(Vertex),
                           (void*)offsetof(Vertex,color));

    glDrawArrays(GL_TRIANGLES, 0, 1000);//mode, starting index, count


// do the same for the Dragon
    //upload the matrix to the shader
    glUniformMatrix4fv(MVP_ID, 1, GL_FALSE, glm::value_ptr(mvpDragon));

    //set up the Vertex Buffer Object so it can be drawn
    glEnableVertexAttribArray(loc_position);
    glEnableVertexAttribArray(loc_color);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_Dragon);
    //set pointers into the vbo for each of the attributes(position and color)
    glVertexAttribPointer( loc_position,//location of attribute
                           3,//number of elements
                           GL_FLOAT,//type
                           GL_FALSE,//normalized?
                           sizeof(Vertex),//stride
                           0);//offset

    glVertexAttribPointer( loc_color,
                           3,
                           GL_FLOAT,
                           GL_FALSE,
                           sizeof(Vertex),
                           (void*)offsetof(Vertex,color));

    if ( dragonToggle == true )
        glDrawArrays(GL_TRIANGLES, 0, 1000000);//mode, starting index, count



    // done setting up matrices

    //clean up
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
                           
    //swap the buffers
    glutSwapBuffers(); 
}

void update()
{


    //total time
    static float angle = 0.0;
    static float xPos = 20.5;
    static float zPos = -20.0;
    static float yPos = 0;
    float dt = getDT();// if you have anything moving, use dt.

    // if reset in the menu is selected
    if( RESET )
       {
        // reset all the positions of the models
        board = glm::translate( glm::mat4(1.0f), glm::vec3(0.0, 0.0, 0.0));
        ball = glm::translate( glm::mat4(1.0f), glm::vec3(0.0, 0.0, 0.0) );
        floorMat = glm::translate( glm::mat4(1.0f), glm::vec3(0.0, 0.0, 0.0) );
    
        // reset all the angles and values
        xPos = 20.5;
        zPos = -20.0;
        angle = 0;

        ROTATIONZ = 0;
        ROTATIONX = 0;
        X_COUNT   = 0;
        Z_COUNT   = 0;

        RESET = false;
        Paused = false;
        dead = false;
        won = false;
       }



    if( !Paused and !dead and !won )
       {

        if ( ROTATIONZ != 0 or ROTATIONX != 0 )
           {
            angle += dt * M_PI/2; //move through 90 degrees a second
           }
        else if ( ROTATIONZ == 0 and ROTATIONX == 0 )
           {
            angle = 0;
           }


        // rotate the board   ( 4x4 matrix, const T&, vec3 )
        //                          board,   speed,    about what axis

        // rotate back and forth ( to and away from you )
        if( ROTATIONZ != 0 )
           {
            Z_COUNT += angle*0.3f*ROTATIONZ;
            if ( Z_COUNT < MAX_ROT and Z_COUNT > -MAX_ROT )
               {
                board = glm::translate( glm::mat4(1.0f), glm::vec3(0.0, 0.0, 0.0));
                board = glm::rotate( board, Z_COUNT, glm::vec3(1.f, 0.f, 0.f) );
                board = glm::rotate( board, X_COUNT, glm::vec3(0.f, 0.f, 1.f) );
               }
            else
               {
                    if ( Z_COUNT > MAX_ROT )
                       {
                        Z_COUNT = MAX_ROT;
                       }
                    else
                       {
                        Z_COUNT = -MAX_ROT;
                       }
               }
           }
        if( ROTATIONX != 0 )
           {
            X_COUNT += angle*0.3f*ROTATIONX;
            if ( X_COUNT < MAX_ROT and X_COUNT > -MAX_ROT )
               {
                board = glm::translate( glm::mat4(1.0f), glm::vec3(0.0, 0.0, 0.0));
                board = glm::rotate( board, X_COUNT, glm::vec3(0.f, 0.f, 1.0f) );
                board = glm::rotate( board, Z_COUNT, glm::vec3(1.f, 0.f, 0.f) );
               }
            else
               {
                    if ( X_COUNT > MAX_ROT )
                       {
                        X_COUNT = MAX_ROT;
                       }
                    else
                       {
                        X_COUNT = -MAX_ROT;
                       }
               }
           }
        
        //
        xMove =  float(X_COUNT/10);
        zMove =  float(Z_COUNT/10);

        xMove = -dt*xMove*8;
        zMove = dt*zMove*8;
        
        // if the ball would move into a wall, dont let it
        checkForWalls( xPos, zPos, xMove, zMove );

        xPos += xMove;
        zPos += zMove;


        if( xPos > MAX_BALL )
           {
            xPos = MAX_BALL;
           }
        else if( xPos < -MAX_BALL )
           {
            xPos = -MAX_BALL;
           }
        if( zPos > MAX_BALL )
           {
            zPos = MAX_BALL;
           }
        else if( zPos < -MAX_BALL )
           {
            zPos = -MAX_BALL;
           }



        ball = glm::translate( board, glm::vec3(xPos, 0, zPos) );
    //    ball = glm::rotate( ball, X_COUNT, glm::vec3(0.f, 0.f, 1.0f) );
    //    ball = glm::rotate( ball, Z_COUNT, glm::vec3(1.f, 0.f, 0.f) );

        floorMat = glm::translate( board, glm::vec3(0, 0, 0) );
        Start = glm::translate( board, glm::vec3(0, 0, 0) );
        Finish = glm::translate( board, glm::vec3(0, 0, 0) );
        Dragon = glm::translate( board, glm::vec3(0, 5, 0) );
        


        // make sure your ball is not in a hole ( -1 is dead )
        int status = 0;


        if ( dist( xPos, zPos, 11.8, -3.3 ) < MIN_DISTANCE )
            {
            status = -1;
            ball = glm::translate( board, glm::vec3(11.8, 0, -3.3) );
            xPos = 11.8;
            zPos = -3.3;
            }
        else if ( dist( xPos, zPos, -11.6, -10.5 ) < MIN_DISTANCE )
            {
            status = -2;
            ball = glm::translate( board, glm::vec3(-11.6, 0, -10.5) );
            xPos = -11.6;
            zPos = -10.5;
            }
        else if ( dist( xPos, zPos, -3.7, 4.0 ) < MIN_DISTANCE )
            {
            status = -3;
            ball = glm::translate( board, glm::vec3(-3.7, 0, 4.0) );
            xPos = -3.7;
            zPos = 4.0;
            }
        else if ( dist( xPos, zPos, 11.9, 11.7 ) < MIN_DISTANCE )
            {
            status = -4;
            ball = glm::translate( board, glm::vec3(11.9, 0, 11.7) );
            xPos = 11.9;
            zPos = 11.7;
            }
        else if ( dist( xPos, zPos, -3.6, 12.0 ) < MIN_DISTANCE )
            {
            status = -5;
            ball = glm::translate( board, glm::vec3(-3.6, 0, 12.0) );
            xPos = -3.6;
            zPos = 12.0;
            } 
        else if ( dist( xPos, zPos, -20.3, 12.6 ) < MIN_DISTANCE )
            {
            status = -6;
            ball = glm::translate( board, glm::vec3(-20.3, 0, 12.6) );
            xPos = -20.3;
            zPos = 12.6;
            }

        // determine if u have won or not!  ( 1  = WIN!!!! YAY! )
        if ( dist( xPos, zPos, -3.7, -10.7 ) < MIN_DISTANCE )
           {
            status = 1;
            cout << "YOU WIN!!!!!!" << endl;
            cout << "YOU WIN!!!!!!" << endl;
            cout << "YOU WIN!!!!!!" << endl;
            cout << "YOU WIN!!!!!!" << endl;
            xPos = -3.7;
            zPos = -10.7;
            yPos = 0;

            won = true;
           }


  
        if ( status <= -1 )
           {
            cout << "YOU ARE DEAD..." << endl;
            dead = true;
            yPos = 0.0;
            //ball = glm::translate( board, glm::vec3(xPos, 120, zPos) );
           }

        if ( MOUSE_MOVING == true )
           {
            ROTATIONX = 0;
            ROTATIONZ = 0;
            glutWarpPointer( w/2, h/2);
            MOUSE_MOVING = false;
           }
        
       }

    if( dead )
       {
        yPos += -dt*32;

        if( yPos > -45 )
           {
            ball = glm::translate( board, glm::vec3(xPos, yPos, zPos) );
           }

       }

    if( won )
       {
        yPos += dt*16;

        if( yPos < 80 )
           {
            ball = glm::translate( board, glm::vec3(xPos, yPos, zPos) );
           }

       }

    if( showPos )
       {
        cout << "X: " << xPos << "  Z: " << zPos << endl;
        cout << "X: " << xMove << "  Z: " << zMove << endl;
        showPos = false;
       }

    // Update the state of the scene
    glutPostRedisplay();//call the display callback
}


void reshape(int n_w, int n_h)
{
    w = n_w;
    h = n_h;
    //Change the viewport to be correct
    glViewport( 0, 0, w, h);
    //Update the projection matrix as well
    //See the init function for an explaination
    projection = glm::perspective(45.0f, float(w)/float(h), 0.01f, 100.0f);

}

void keyboard(unsigned char key, int x_pos, int y_pos)
{
    // Handle keyboard input
    if(key == 27)//ESC
    {
        exit(0);
    }
    
    if( key == 32 ) // for showing current Position
    {
     showPos = true;
    }

    // rotate the global variable depending on arrow key pressed
    switch( key ) 
       {
        case 100: 
        case  68:
            // Rotate           RIGHT
            ROTATIONX = 1.0;
//              cout << "RIGHT" <<   endl;
            break;
        case 97: 
        case 65:
            // Rotate           LEFT
            ROTATIONX = -1.0;
//              cout << "LEFT" <<   endl;
            break;
        case 119:
        case  87: 
            // Rotate           UP
            ROTATIONZ = 1.0;
//              cout << "UP" <<   endl;
            break;
        case 115:
        case  83:
            // Rotate           DOWN 
            ROTATIONZ = -1.0;
//              cout << "DOWN" <<   endl;
            break;
       }
    MOUSE_MOVING = false;
}

void keyup(unsigned char key, int x_pos, int y_pos)
{
    // turn off the rotation if the key is let go
    switch( key ) 
       {
        case 100: 
        case  68: 
            // Rotate           RIGHT
            ROTATIONX = 0.0;
            break;
        case 97: 
        case 65: 
            // Rotate           LEFT
            ROTATIONX = 0.0;
            break;
        case 119:
        case  87:  
            // Rotate           UP
            ROTATIONZ = 0.0;
            break;
        case 115:
        case  83:
            // Rotate           DOWN 
            ROTATIONZ = 0.0;
            break;

        // toggle the dragon
        case   9:
            dragonToggle = !dragonToggle;
            cout << "changed" << endl;
            break;
       }
    MOUSE_MOVING = false;
}

bool initialize()
{

    // initialize shader variables
    init_shader_variables();

///// LOAD OBJ FILES ///////////////////////////////////////////////////////////////////
    // create the ball
    Obj ball( "../Meshes/triSphere.obj", identity , tex1); 
    Obj wall( "../Meshes/Maze-NoFloor.obj", identity, tex1);
    Obj floor( "../Meshes/Maze-Floor2.obj", identity , tex1); 
    Obj start( "../Meshes/start.obj", identity , tex1); 
    Obj finish( "../Meshes/finish.obj", identity , tex1); 
    Obj dragon( "/media/KINGSTON/dragon.obj", identity , tex1); 

    objectList.push_back( ball );
    objectList.push_back( wall );
    objectList.push_back( floor );
    objectList.push_back( start );
    objectList.push_back( finish );
    objectList.push_back( dragon );

    //--Geometry done
    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

    //compile the shaders
    GLint Result = GL_FALSE;
    int InfoLogLength;

        // Read the Vertex Shader code from the file
        std::string VertexShaderCode;
        std::ifstream VertexShaderStream("vs.txt", std::ios::in);
        if(VertexShaderStream.is_open()){
                std::string Line = "";
                while(getline(VertexShaderStream, Line))
                        VertexShaderCode += "\n" + Line;
                VertexShaderStream.close();
        }

        // Read the Fragment Shader code from the file
        std::string FragmentShaderCode;
        std::ifstream FragmentShaderStream("fs.txt", std::ios::in);
        if(FragmentShaderStream.is_open()){
                std::string Line = "";
                while(getline(FragmentShaderStream, Line))
                        FragmentShaderCode += "\n" + Line;
                FragmentShaderStream.close();
        }

        // Compile Vertex Shader
        printf("Compiling shader : %s\n", "vs.txt");
        char const * VertexSourcePointer = VertexShaderCode.c_str();
        glShaderSource(vertex_shader, 1, &VertexSourcePointer , NULL);
        glCompileShader(vertex_shader);

    // Check Vertex Shader
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &InfoLogLength);
    std::vector<char> VertexShaderErrorMessage(InfoLogLength);
    glGetShaderInfoLog(vertex_shader, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
    fprintf(stdout, "%s\n", &VertexShaderErrorMessage[0]);



        // Compile Fragment Shader
        printf("Compiling shader : %s\n", "fs.txt");
        char const * FragmentSourcePointer = FragmentShaderCode.c_str();
        glShaderSource(fragment_shader, 1, &FragmentSourcePointer , NULL);
        glCompileShader(fragment_shader); 


    // Check Fragment Shader
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(fragment_shader, GL_INFO_LOG_LENGTH, &InfoLogLength);
    std::vector<char> FragmentShaderErrorMessage(InfoLogLength);
    glGetShaderInfoLog(fragment_shader, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
    fprintf(stdout, "%s\n", &FragmentShaderErrorMessage[0]);



    //Now we link the 2 shader objects into a program
    //This program is what is run on the GPU
    program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);
    //check if everything linked ok
    glGetProgramiv(program, GL_LINK_STATUS, &Result);
    if(!Result)
    {
          cerr << "[F] THE SHADER PROGRAM FAILED TO LINK" <<   endl;
        return false;
    }


    //Now we set the locations of the attributes and uniforms
    //this allows us to access them easily while rendering

    //MVP_ID = glGetUniformLocation(program, "MVP");
    MVP_ID = glGetUniformLocation(program, "mvp");
    WORLD_ID = glGetUniformLocation(program, "gWorld");

    h_LightPosition   = GetUniformLocation( h_program, "LightPosition");
    h_AmbientProduct  = GetUniformLocation( h_program, "AmbientProduct");
    h_DiffuseProduct  = GetUniformLocation( h_program, "DiffuseProduct");
    h_SpecularProduct = GetUniformLocation( h_program, "SpecularProduct");
    h_LightPosition   = GetUniformLocation( h_program, "LightPosition");
    h_Shineness       = GetUniformLocation( h_program, "Shineness");
    h_gSampler        = GetUniformLocation( h_program, "gSampler");


    loc_position = glGetAttribLocation(program, "v_position" );
    //loc_position = glGetAttribLocation(program, "vertexPosition_modelspace" );
    loc_normal = glGetAttribLocation(program, "normal" );
    loc_color = glGetAttribLocation(program, "v_color" );
    
    //--Init the view and projection matrices
    //  if you will be having a moving camera the view matrix will need to more dynamic
    //  ...Like you should update it before you render more dynamic 
    //  for this project having them static will be fine
    view = glm::lookAt( eyePosition, //Eye Position
                        glm::vec3(0.0, 0.0, 0.0), //Focus point
                        glm::vec3(0.0, 1.0, 0.0)); //Positive Y is up

    projection = glm::perspective( 45.0f, //the FoV typically 90 degrees is good which is what this is set to
                                   float(w)/float(h), //Aspect Ratio, so Circles stay Circular
                                   0.01f, //Distance to the near plane, normally a small value like this
                                   100.0f); //Distance to the far plane, 

    

    //enable depth testing
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // remove cursor and snap it to the screen
    glutSetCursor( GLUT_CURSOR_NONE );
    glutWarpPointer( (w/2), (h/2) );

    // setup the list of walls
    setupWalls();

    //and its done
    return true;
}

void cleanUp()
{
    // Clean up, Clean up
    glDeleteProgram(program);
    glDeleteBuffers(1, &vbo_Wall);
    glDeleteBuffers(1, &vbo_Sphere);
    glDeleteBuffers(1, &vbo_Floor);
}

//returns the time delta
float getDT()
{
    float ret;
    t2  =   chrono::high_resolution_clock::now();
    ret =   chrono::duration_cast<   chrono::duration<float> >(t2-t1).count();
    t1  =   chrono::high_resolution_clock::now();
    return ret;
}


void mouseMove( int x, int y )
{

    if( oldMouse[0] - x > 0 )
       {
        ROTATIONX = -100;
        MOUSE_MOVING = true;
       }
    else if( oldMouse[0] - x < 0 )
       {
        ROTATIONX = 100;
        MOUSE_MOVING = true;
       }
//    else
//        ROTATIONX = 0.0;

    if( oldMouse[1] - y > 0 )
       {
        ROTATIONZ = 100;
        MOUSE_MOVING = true;
       }
    else if( oldMouse[1] - y < 0 )
       {
        ROTATIONZ = -100;
        MOUSE_MOVING = true;
       }
//    else
//        ROTATIONZ = 0.0;


    
    oldMouse[0] = w/2;
    oldMouse[1] = h/2;
}

// read the shader files
char *textFileRead( const char *fn ) {
 
    FILE *fp;
    char *content = NULL;
 
    int count=0;
 
    if (fn != NULL) {
        fp = fopen(fn,"rt");
 
        if (fp != NULL) {
 
      fseek(fp, 0, SEEK_END);
      count = ftell(fp);
      rewind(fp);
 
            if (count > 0) {
                content = (char *)malloc(sizeof(char) * (count+1));
                count = fread(content,sizeof(char),count,fp);
                content[count] = '\0';
            }
            fclose(fp);
        }
    }
    return content;
}

void menu( int id )
{
    switch( id )
       {
        case 1:
            RESET = true;
            break;

        case 2:
            Paused = !Paused;
            break;

        case 3:
            exit(0);
            break;
       }
}


float dist( float x1, float y1, float x2, float y2 )
{
    // do distance squared calculations
    float temp1 = ( x1 - x2 );
    float temp2 = ( y1 - y2 );


    return ( ( temp1 * temp1 ) + ( temp2 * temp2 ) );
}



bool loadDragonFile( const string& fileName )
{
      // Create an instance of the Importer class
      Assimp::Importer importer;

      // And have it read the given file with some example postprocessing
      // Usually - if speed is not the most important aspect for you - you'll 
      // propably to request more postprocessing than we do in this example.
      const aiScene* scene = importer.ReadFile( fileName, 
            aiProcess_CalcTangentSpace       | 
            aiProcess_Triangulate            |
            aiProcess_JoinIdenticalVertices  |
            aiProcess_SortByPType);
      
      // If the import failed, report it
      if( !scene)
      {
        cout << endl << endl << importer.GetErrorString() << endl << endl;
        return false;
      }

      // Now we can access the file's contents. 
      processDragon( scene );

      // We're done. Everything will be cleaned up by the importer destructor
      return true;

}

void  processDragon( const aiScene* scene )
{
    //cout << "here" << endl;
    //cout << "NUM meshes: " << (*scene).mNumMeshes << endl;
    cout << "# of Faces              : " << (*scene).mMeshes[0][0].mNumFaces << endl;
    cout << "# of Vertices/coords    : " << (*scene).mMeshes[0][0].mNumVertices << endl;
    cout << "First Vertice           : " << (*scene).mMeshes[0][0].mVertices[0].x << " " << (*scene).mMeshes[0][0].mVertices[0].y << " " << (*scene).mMeshes[0][0].mVertices[0].z << endl;
}


void setupWalls(){
    // for first wall: 

    // create a temp wall
    boxWall temp( 17.8,-14.1,  15.1, -13.9  , 17.8, -22.5 ,  15.3, -22.5  );
    // add it to the vector of walls
    listOfWalls.push_back( temp );


    // wall1
    temp.changeCoords( 15.4, -13.9, 8.4, -16.35 );
    listOfWalls.push_back( temp ); 
 
    // wall2 
    temp.changeCoords( 16.7, -6.0, 8.5, -8.2 );
    listOfWalls.push_back( temp );

    // wall3
    temp.changeCoords( 22.5, 1.1, 8.25, -1.45 );
    listOfWalls.push_back( temp );

    // wall4
    temp.changeCoords( 17.7, 17.5, 15.5, 6.8 ); 
    listOfWalls.push_back( temp );

    // wall5
    temp.changeCoords( 15.6, 9.5, 7.1, 6.8 );
    listOfWalls.push_back( temp );

    // wall6
    temp.changeCoords( 9.5, 17.7, 6.8, 9.2 );
    listOfWalls.push_back( temp );

    // wall7
    temp.changeCoords( 1.28, -8.2, -1.1, -22.5 );
    listOfWalls.push_back( temp );

    // wall8
    temp.changeCoords( 1.38, -5.7, -9.68, -8.1  );
    listOfWalls.push_back( temp );

    // wall9
    temp.changeCoords( -6.6, -8.2, -9.35, -13.9 );
    listOfWalls.push_back( temp );

    // wall10
    temp.changeCoords( -6.6, -14.1, -15.3, -16.6  );
    listOfWalls.push_back( temp );

    // wall11
    temp.changeCoords( -14.4, 1.0, -17.6, -16.6  );
    listOfWalls.push_back( temp );

    // wall12
    temp.changeCoords( -9.5, 1.0, -14.7, -1.2  );
    listOfWalls.push_back( temp );

    // wall13
    temp.changeCoords( -7.0, 18.3, -9.7, -1.2 );
    listOfWalls.push_back( temp );

    // wall14
    temp.changeCoords( -1.2, 9.9, -7.0, 6.8  );
    listOfWalls.push_back( temp );

    // wall15
    temp.changeCoords( -15.2, 17.8, -17.5, 6.8  );
    listOfWalls.push_back( temp );

    // wall16
    temp.changeCoords( -17.2, 9.2, -22.5, 6.8 );
    listOfWalls.push_back( temp );  
}

bool checkForWalls( float oldx, float oldz, float &xMove, float &zMove ){
 
    // determine projected location
    float x, z;
    x = oldx + xMove;  
    z = oldz + zMove;

    // for every wall
    for( unsigned int i = 0; i < listOfWalls.size(); i++ )
       {
        // check to see if the x and z are inside the walls
        if( listOfWalls[i].checkIfInside( x, z ) )
           {

            // check again for another collision
            for( unsigned int p = i+1; p< listOfWalls.size(); p++ )
               {
                // if u are in another wall, stop all movement
                if( listOfWalls[p].checkIfInside( x, z ) )   
                   {             
                    xMove = 0.0;
                    zMove = 0.0;
                    return true;
                   }
               }

            // if no other collision is found, then you continue as normal
                // stop one movement

            // if true stop the correct movement (create sliding)
            int side = listOfWalls[i].whatSideHit( oldx, oldz );

            if( side == 0 )
               {
               xMove = 0.0;
               }
            else
               {
                zMove = 0.0;
               }            

            return true;
            

           }
       }    

    return false;
}

void init_shader_variables()
{

  glm::mat4 id = glm::mat4(1);

  world  =         view * id;

  //glUniformMatrix4fv(h_gWVP,    1, GL_FALSE, glm::value_ptr(gWVP)   );
  //glUniformMatrix4fv(h_gWorld,  1, GL_FALSE, glm::value_ptr(gWorld) );

  glUniform4f( h_LightPosition  , lightoffset_x, lightoffset_y, lightoffset_z, 1 );
  glUniform4f( h_AmbientProduct , 0.3, 0.3, 0.3, 1);
  glUniform4f( h_DiffuseProduct , 0.8, 0.8, 0.8, 1);
  glUniform4f( h_SpecularProduct, 0.8, 0.8, 0.8, 1);
  glUniform4f( h_LightPosition  , 0.8, 0.8, 0.8, 1);
  glUniform1f( h_Shineness      , 0.5 );

  glUniform1i( h_gSampler, 0);

}
























