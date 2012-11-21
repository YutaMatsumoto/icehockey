#include <GL/glew.h> // glew must be included before the main gl libs
#include <GL/glut.h> // doing otherwise causes compiler shouting
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <chrono>
#include <math.h>
//#include "Vertex.cpp" 

#include "loadOBJ.cpp"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp" //Makes passing matrices to shaders easier

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

#include </home/other/hostetle/2013/Graphics/Box2D_v2.1.2/Box2D/Box2D/Box2D.h>


using namespace std;

//--Evil Global variables
//Just for this example!
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

// Light Handle
GLuint lightHandle1;

//uniform locations
GLint loc_mvpmat;// Location of the boardviewprojection matrix in the shader

//attribute locations
GLint loc_position;
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

float oldMouse[2] = { 0, 0 };
bool MOUSE_MOVING = false;

//transform matrices
glm::mat4 board;//obj->world each object should have its own board matrix
glm::mat4 ball;//obj->world each object should have its own ball matrix
glm::mat4 floorMat;//obj->world each object should have its own floor matrix
glm::mat4 Start;//obj->world each object should have its own Start matrix
glm::mat4 Finish;//obj->world each object should have its own Finish matrix
glm::mat4 Dragon;//obj->world each object should have its own Dragon matrix

glm::mat4 view;//world->eye
glm::mat4 projection;//eye->clip
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

//--Main
int main(int argc, char **argv)
{
    // Initialize glut
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(w, h);
    // Name and create the Window
    glutCreateWindow("Labyrinth Game");

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
    glColor3d(1,0,0);


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

// do rendering on the walls
    //upload the matrix to the shader
    glUniformMatrix4fv(loc_mvpmat, 1, GL_FALSE, glm::value_ptr(mvpWall));

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
    glUniformMatrix4fv(loc_mvpmat, 1, GL_FALSE, glm::value_ptr(mvpBall));

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

    //upload the matrix to the shader
    glUniformMatrix4fv(loc_mvpmat, 1, GL_FALSE, glm::value_ptr(mvpFloor));

    //set up the Vertex Buffer Object so it can be drawn
    glEnableVertexAttribArray(loc_position);
    glEnableVertexAttribArray(loc_color);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_Floor);
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



// do the same for the Start
    //upload the matrix to the shader
    glUniformMatrix4fv(loc_mvpmat, 1, GL_FALSE, glm::value_ptr(mvpStart));

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
    glUniformMatrix4fv(loc_mvpmat, 1, GL_FALSE, glm::value_ptr(mvpFinish));

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
    glUniformMatrix4fv(loc_mvpmat, 1, GL_FALSE, glm::value_ptr(mvpDragon));

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

    glDrawArrays(GL_TRIANGLES, 0, 1000000);//mode, starting index, count



    // done setting up matrices

    //clean up
    glDisableVertexAttribArray(loc_position);
    glDisableVertexAttribArray(loc_color);
                           
    //swap the buffers
    glutSwapBuffers(); 
}

void update()
{


    //total time
    static float angle = 0.0;
    static float xPos = 20.5;
    static float zPos = -20.0;
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
       }

    if( !Paused and !dead )
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

        xPos += -dt*xMove*8;
        zPos += dt*zMove*8;

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
            status = -1;
        else if ( dist( xPos, zPos, -11.6, -10.5 ) < MIN_DISTANCE )
            status = -2;
        else if ( dist( xPos, zPos, -3.7, 4.0 ) < MIN_DISTANCE )
            status = -3;
        else if ( dist( xPos, zPos, 11.9, 11.7 ) < MIN_DISTANCE )
            status = -4;
        else if ( dist( xPos, zPos, -3.6, 12.0 ) < MIN_DISTANCE )
            status = -5;
        else if ( dist( xPos, zPos, -20.3, 12.6 ) < MIN_DISTANCE )
            status = -6;

        // determine if u have won or not!  ( 1  = WIN!!!! YAY! )
        if ( dist( xPos, zPos, -3.7, -10.7 ) < MIN_DISTANCE )
           {
            status = 1;
            cout << "YOU WIN!!!!!!" << endl;
           }

        if ( status <= -1 )
           {
            cout << "YOU ARE DEAD..." << endl;
            dead = true;
            ball = glm::translate( board, glm::vec3(xPos, 120, zPos) );
           }

        if ( MOUSE_MOVING == true )
           {
            ROTATIONX = 0;
            ROTATIONZ = 0;
            glutWarpPointer( w/2, h/2);
            MOUSE_MOVING = false;
           }
        
       }

    if( showPos )
       {
        cout << "X: " << xPos << "  Z: " << zPos << endl;
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
       }
    MOUSE_MOVING = false;
}

bool initialize()
{

    // MAYBE ADD VERTEXARRAY........                               #####################


///// LOAD OBJ FILES ///////////////////////////////////////////////////////////////////

    // load in .obj files
    // do this for the ball, the walls, and the floor
    vector<Vertex> SphereVertices; 
    vector<glm::vec2> SphereUVs; // Won't be used at the moment.
    vector<glm::vec3> SphereNormals; // Won't be used at the moment.
    loadOBJ("../Meshes/triSphere.obj", SphereVertices, SphereUVs, SphereNormals, 0,
         0.8, 0.5 ,0.1);

//  "../Meshes/triSphere.obj"
//  "/media/KINGSTON/dragon.obj"

    vector<Vertex> WallVertices;
    vector<glm::vec2> WallUVs; // Won't be used at the moment.
    vector<glm::vec3> WallNormals; // Won't be used at the moment.
    loadOBJ("../Meshes/Maze-NoFloor.obj", WallVertices, WallUVs, WallNormals, 1,
         0.6, 0.6, 0.6);

    vector<Vertex> FloorVertices;
    vector<glm::vec2> FloorUVs; // Won't be used at the moment.
    vector<glm::vec3> FloorNormals; // Won't be used at the moment.
    loadOBJ("../Meshes/Maze-Floor2.obj", FloorVertices, FloorUVs, FloorNormals, 1,
         0.3, 0.55 ,0.2);

    vector<Vertex> StartVertices;
    vector<glm::vec2> StartUVs; // Won't be used at the moment.
    vector<glm::vec3> StartNormals; // Won't be used at the moment.
    loadOBJ("../Meshes/start.obj", StartVertices, StartUVs, StartNormals, 1,
         0.1, 0.38 ,0.05);

    vector<Vertex> FinishVertices;
    vector<glm::vec2> FinishUVs; // Won't be used at the moment.
    vector<glm::vec3> FinishNormals; // Won't be used at the moment.
    loadOBJ("../Meshes/finish.obj", FinishVertices, FinishUVs, FinishNormals, 1,
         0.7, 0.05 ,0.2);


    // try and load the dragon
    vector<Vertex> DragonVertices;
    vector<glm::vec2> DragonUVs; // Won't be used at the moment.
    vector<glm::vec3> DragonNormals; // Won't be used at the moment.
    loadOBJ("/media/KINGSTON/dragon.obj", DragonVertices, DragonUVs, DragonNormals, 0,
         0.5, 0.5, 0.5);
    //loadDragonFile( "/media/KINGSTON/dragon.obj" );


/////// LOAD VBO's ////////////////////////////////////////////////////////////

    // Create a Vertex Buffer object to store this vertex info on the GPU
    
    // BALL
    glGenBuffers(1, &vbo_Sphere);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_Sphere);
    glBufferData(GL_ARRAY_BUFFER, SphereVertices.size()*sizeof(Vertex), &SphereVertices[0], GL_STATIC_DRAW);

    // WALL
    glGenBuffers(1, &vbo_Wall);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_Wall);
    glBufferData(GL_ARRAY_BUFFER, WallVertices.size()*sizeof(Vertex), &WallVertices[0], GL_STATIC_DRAW);


    // FLOOR
    glGenBuffers(1, &vbo_Floor);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_Floor);
    glBufferData(GL_ARRAY_BUFFER, FloorVertices.size()*sizeof(Vertex), &FloorVertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &nbo_Floor);
    glBindBuffer(GL_ARRAY_BUFFER, nbo_Floor);
    glBufferData(GL_ARRAY_BUFFER, FloorNormals.size() * sizeof(glm::vec3), &FloorNormals[0], GL_STATIC_DRAW);

    // START
    glGenBuffers(1, &vbo_Start);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_Start);
    glBufferData(GL_ARRAY_BUFFER, StartVertices.size()*sizeof(Vertex), &StartVertices[0], GL_STATIC_DRAW);

    // FINISH
    glGenBuffers(1, &vbo_Finish);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_Finish);
    glBufferData(GL_ARRAY_BUFFER, FinishVertices.size()*sizeof(Vertex), &FinishVertices[0], GL_STATIC_DRAW);

    // DRAGON
    glGenBuffers(1, &vbo_Dragon);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_Dragon);
    glBufferData(GL_ARRAY_BUFFER, DragonVertices.size()*sizeof(Vertex), &DragonVertices[0], GL_STATIC_DRAW);

    //--Geometry done

    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

    char *fileVS, *fileFS;
    const char* vsName = "vertexShader.txt";
    const char* fsName = "fragmentShader.txt";

    fileVS = textFileRead( vsName );
    fileFS = textFileRead( fsName );

    //Shader Sources
    // Put these into files and write a loader in the future
    // Note the added uniform!
    const char *vs = fileVS;
    const char *fs = fileFS;

    //compile the shaders
    GLint shader_status;

    // Vertex shader first
    glShaderSource(vertex_shader, 1, &vs, NULL);
    glCompileShader(vertex_shader);
    free(fileVS);

    //check the compile status
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &shader_status);
    if(!shader_status)
    {
          cerr << "[F] FAILED TO COMPILE VERTEX SHADER!" <<   endl;
        return false;
    }

    // Now the Fragment shader
    glShaderSource(fragment_shader, 1, &fs, NULL);
    glCompileShader(fragment_shader);
    free(fileFS);

    //check the compile status
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &shader_status);
    if(!shader_status)
    {
          cerr << "[F] FAILED TO COMPILE FRAGMENT SHADER!" <<   endl;
        return false;
    }

    //Now we link the 2 shader objects into a program
    //This program is what is run on the GPU
    program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);
    //check if everything linked ok
    glGetProgramiv(program, GL_LINK_STATUS, &shader_status);
    if(!shader_status)
    {
          cerr << "[F] THE SHADER PROGRAM FAILED TO LINK" <<   endl;
        return false;
    }

    //Now we set the locations of the attributes and uniforms
    //this allows us to access them easily while rendering
    loc_position = glGetAttribLocation(program,
                    const_cast<const char*>("v_position"));
    if(loc_position == -1)
    {
          cerr << "[F] POSITION NOT FOUND" <<   endl;
        return false;
    }

    loc_color = glGetAttribLocation(program,
                    const_cast<const char*>("v_color"));
    if(loc_color == -1)
    {
          cerr << "[F] V_COLOR NOT FOUND" <<   endl;
        return false;
    }

    loc_mvpmat = glGetUniformLocation(program,
                    const_cast<const char*>("mvpMatrix"));
    if(loc_mvpmat == -1)
    {
          cerr << "[F] MVPMATRIX NOT FOUND" <<   endl;
        return false;
    }
    
    //--Init the view and projection matrices
    //  if you will be having a moving camera the view matrix will need to more dynamic
    //  ...Like you should update it before you render more dynamic 
    //  for this project having them static will be fine
    view = glm::lookAt( glm::vec3(0.0, 80.0, -0.1), //Eye Position
                        glm::vec3(0.0, 0.0, 0.0), //Focus point
                        glm::vec3(0.0, 1.0, 0.0)); //Positive Y is up

    projection = glm::perspective( 45.0f, //the FoV typically 90 degrees is good which is what this is set to
                                   float(w)/float(h), //Aspect Ratio, so Circles stay Circular
                                   0.01f, //Distance to the near plane, normally a small value like this
                                   100.0f); //Distance to the far plane, 

    // add the light handle
    lightHandle1 = glGetUniformLocation(program, "LightPosition_worldspace");

    //enable depth testing
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // remove cursor and snap it to the screen
    glutSetCursor( GLUT_CURSOR_NONE );
    glutWarpPointer( (w/2), (h/2) );

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




















