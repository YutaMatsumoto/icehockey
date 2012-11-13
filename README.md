* Compilation : ` $ make bin/j7.out ` OR ` $ make`
* Run : ` $ make run2 `

# Modifications
* 11/13 : Changed shaders so that the code compiles in ecc. ECC opengl is old and does not accept new glsl keywords, layout, in, out.

# Misc
* OpenGL version
  * ecc opengl version : 2.1 Mesa 8.0.4 (output from `glGetString(GL_VERSION)` )
  * http://stackoverflow.com/questions/7909358/how-do-i-know-which-version-of-opengl-i-am-using

# TODO
* camera around sphere
  * This should be intuitive instead of rotatint around x,y,z-axis. I.e., should be rotation around an arbitrary vector depending on the current view.
* lighting
  * multiple lights ?
  * better interface to change lighting
* mesh objects
  * paddlers 
  * board
* physics
  * make bullet objects for paddler and board
  * move paddler appropriately
* clear up j7.cpp 
* how to use j7.out and makefile
