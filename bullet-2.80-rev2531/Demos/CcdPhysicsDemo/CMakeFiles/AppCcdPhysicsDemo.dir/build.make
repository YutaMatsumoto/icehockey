# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /tmp/a/icehockey/bullet-2.80-rev2531

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /tmp/a/icehockey/bullet-2.80-rev2531

# Include any dependencies generated for this target.
include Demos/CcdPhysicsDemo/CMakeFiles/AppCcdPhysicsDemo.dir/depend.make

# Include the progress variables for this target.
include Demos/CcdPhysicsDemo/CMakeFiles/AppCcdPhysicsDemo.dir/progress.make

# Include the compile flags for this target's objects.
include Demos/CcdPhysicsDemo/CMakeFiles/AppCcdPhysicsDemo.dir/flags.make

Demos/CcdPhysicsDemo/CMakeFiles/AppCcdPhysicsDemo.dir/main.o: Demos/CcdPhysicsDemo/CMakeFiles/AppCcdPhysicsDemo.dir/flags.make
Demos/CcdPhysicsDemo/CMakeFiles/AppCcdPhysicsDemo.dir/main.o: Demos/CcdPhysicsDemo/main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /tmp/a/icehockey/bullet-2.80-rev2531/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object Demos/CcdPhysicsDemo/CMakeFiles/AppCcdPhysicsDemo.dir/main.o"
	cd /tmp/a/icehockey/bullet-2.80-rev2531/Demos/CcdPhysicsDemo && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/AppCcdPhysicsDemo.dir/main.o -c /tmp/a/icehockey/bullet-2.80-rev2531/Demos/CcdPhysicsDemo/main.cpp

Demos/CcdPhysicsDemo/CMakeFiles/AppCcdPhysicsDemo.dir/main.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AppCcdPhysicsDemo.dir/main.i"
	cd /tmp/a/icehockey/bullet-2.80-rev2531/Demos/CcdPhysicsDemo && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /tmp/a/icehockey/bullet-2.80-rev2531/Demos/CcdPhysicsDemo/main.cpp > CMakeFiles/AppCcdPhysicsDemo.dir/main.i

Demos/CcdPhysicsDemo/CMakeFiles/AppCcdPhysicsDemo.dir/main.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AppCcdPhysicsDemo.dir/main.s"
	cd /tmp/a/icehockey/bullet-2.80-rev2531/Demos/CcdPhysicsDemo && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /tmp/a/icehockey/bullet-2.80-rev2531/Demos/CcdPhysicsDemo/main.cpp -o CMakeFiles/AppCcdPhysicsDemo.dir/main.s

Demos/CcdPhysicsDemo/CMakeFiles/AppCcdPhysicsDemo.dir/main.o.requires:
.PHONY : Demos/CcdPhysicsDemo/CMakeFiles/AppCcdPhysicsDemo.dir/main.o.requires

Demos/CcdPhysicsDemo/CMakeFiles/AppCcdPhysicsDemo.dir/main.o.provides: Demos/CcdPhysicsDemo/CMakeFiles/AppCcdPhysicsDemo.dir/main.o.requires
	$(MAKE) -f Demos/CcdPhysicsDemo/CMakeFiles/AppCcdPhysicsDemo.dir/build.make Demos/CcdPhysicsDemo/CMakeFiles/AppCcdPhysicsDemo.dir/main.o.provides.build
.PHONY : Demos/CcdPhysicsDemo/CMakeFiles/AppCcdPhysicsDemo.dir/main.o.provides

Demos/CcdPhysicsDemo/CMakeFiles/AppCcdPhysicsDemo.dir/main.o.provides.build: Demos/CcdPhysicsDemo/CMakeFiles/AppCcdPhysicsDemo.dir/main.o

Demos/CcdPhysicsDemo/CMakeFiles/AppCcdPhysicsDemo.dir/CcdPhysicsDemo.o: Demos/CcdPhysicsDemo/CMakeFiles/AppCcdPhysicsDemo.dir/flags.make
Demos/CcdPhysicsDemo/CMakeFiles/AppCcdPhysicsDemo.dir/CcdPhysicsDemo.o: Demos/CcdPhysicsDemo/CcdPhysicsDemo.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /tmp/a/icehockey/bullet-2.80-rev2531/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object Demos/CcdPhysicsDemo/CMakeFiles/AppCcdPhysicsDemo.dir/CcdPhysicsDemo.o"
	cd /tmp/a/icehockey/bullet-2.80-rev2531/Demos/CcdPhysicsDemo && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/AppCcdPhysicsDemo.dir/CcdPhysicsDemo.o -c /tmp/a/icehockey/bullet-2.80-rev2531/Demos/CcdPhysicsDemo/CcdPhysicsDemo.cpp

Demos/CcdPhysicsDemo/CMakeFiles/AppCcdPhysicsDemo.dir/CcdPhysicsDemo.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AppCcdPhysicsDemo.dir/CcdPhysicsDemo.i"
	cd /tmp/a/icehockey/bullet-2.80-rev2531/Demos/CcdPhysicsDemo && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /tmp/a/icehockey/bullet-2.80-rev2531/Demos/CcdPhysicsDemo/CcdPhysicsDemo.cpp > CMakeFiles/AppCcdPhysicsDemo.dir/CcdPhysicsDemo.i

Demos/CcdPhysicsDemo/CMakeFiles/AppCcdPhysicsDemo.dir/CcdPhysicsDemo.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AppCcdPhysicsDemo.dir/CcdPhysicsDemo.s"
	cd /tmp/a/icehockey/bullet-2.80-rev2531/Demos/CcdPhysicsDemo && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /tmp/a/icehockey/bullet-2.80-rev2531/Demos/CcdPhysicsDemo/CcdPhysicsDemo.cpp -o CMakeFiles/AppCcdPhysicsDemo.dir/CcdPhysicsDemo.s

Demos/CcdPhysicsDemo/CMakeFiles/AppCcdPhysicsDemo.dir/CcdPhysicsDemo.o.requires:
.PHONY : Demos/CcdPhysicsDemo/CMakeFiles/AppCcdPhysicsDemo.dir/CcdPhysicsDemo.o.requires

Demos/CcdPhysicsDemo/CMakeFiles/AppCcdPhysicsDemo.dir/CcdPhysicsDemo.o.provides: Demos/CcdPhysicsDemo/CMakeFiles/AppCcdPhysicsDemo.dir/CcdPhysicsDemo.o.requires
	$(MAKE) -f Demos/CcdPhysicsDemo/CMakeFiles/AppCcdPhysicsDemo.dir/build.make Demos/CcdPhysicsDemo/CMakeFiles/AppCcdPhysicsDemo.dir/CcdPhysicsDemo.o.provides.build
.PHONY : Demos/CcdPhysicsDemo/CMakeFiles/AppCcdPhysicsDemo.dir/CcdPhysicsDemo.o.provides

Demos/CcdPhysicsDemo/CMakeFiles/AppCcdPhysicsDemo.dir/CcdPhysicsDemo.o.provides.build: Demos/CcdPhysicsDemo/CMakeFiles/AppCcdPhysicsDemo.dir/CcdPhysicsDemo.o

# Object files for target AppCcdPhysicsDemo
AppCcdPhysicsDemo_OBJECTS = \
"CMakeFiles/AppCcdPhysicsDemo.dir/main.o" \
"CMakeFiles/AppCcdPhysicsDemo.dir/CcdPhysicsDemo.o"

# External object files for target AppCcdPhysicsDemo
AppCcdPhysicsDemo_EXTERNAL_OBJECTS =

Demos/CcdPhysicsDemo/AppCcdPhysicsDemo: Demos/CcdPhysicsDemo/CMakeFiles/AppCcdPhysicsDemo.dir/main.o
Demos/CcdPhysicsDemo/AppCcdPhysicsDemo: Demos/CcdPhysicsDemo/CMakeFiles/AppCcdPhysicsDemo.dir/CcdPhysicsDemo.o
Demos/CcdPhysicsDemo/AppCcdPhysicsDemo: Demos/OpenGL/libOpenGLSupport.a
Demos/CcdPhysicsDemo/AppCcdPhysicsDemo: src/BulletDynamics/libBulletDynamics.a
Demos/CcdPhysicsDemo/AppCcdPhysicsDemo: src/BulletCollision/libBulletCollision.a
Demos/CcdPhysicsDemo/AppCcdPhysicsDemo: src/LinearMath/libLinearMath.a
Demos/CcdPhysicsDemo/AppCcdPhysicsDemo: /usr/lib/x86_64-linux-gnu/libglut.so
Demos/CcdPhysicsDemo/AppCcdPhysicsDemo: /usr/lib/x86_64-linux-gnu/libGL.so
Demos/CcdPhysicsDemo/AppCcdPhysicsDemo: /usr/lib/x86_64-linux-gnu/libGLU.so
Demos/CcdPhysicsDemo/AppCcdPhysicsDemo: Demos/CcdPhysicsDemo/CMakeFiles/AppCcdPhysicsDemo.dir/build.make
Demos/CcdPhysicsDemo/AppCcdPhysicsDemo: Demos/CcdPhysicsDemo/CMakeFiles/AppCcdPhysicsDemo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable AppCcdPhysicsDemo"
	cd /tmp/a/icehockey/bullet-2.80-rev2531/Demos/CcdPhysicsDemo && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/AppCcdPhysicsDemo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Demos/CcdPhysicsDemo/CMakeFiles/AppCcdPhysicsDemo.dir/build: Demos/CcdPhysicsDemo/AppCcdPhysicsDemo
.PHONY : Demos/CcdPhysicsDemo/CMakeFiles/AppCcdPhysicsDemo.dir/build

Demos/CcdPhysicsDemo/CMakeFiles/AppCcdPhysicsDemo.dir/requires: Demos/CcdPhysicsDemo/CMakeFiles/AppCcdPhysicsDemo.dir/main.o.requires
Demos/CcdPhysicsDemo/CMakeFiles/AppCcdPhysicsDemo.dir/requires: Demos/CcdPhysicsDemo/CMakeFiles/AppCcdPhysicsDemo.dir/CcdPhysicsDemo.o.requires
.PHONY : Demos/CcdPhysicsDemo/CMakeFiles/AppCcdPhysicsDemo.dir/requires

Demos/CcdPhysicsDemo/CMakeFiles/AppCcdPhysicsDemo.dir/clean:
	cd /tmp/a/icehockey/bullet-2.80-rev2531/Demos/CcdPhysicsDemo && $(CMAKE_COMMAND) -P CMakeFiles/AppCcdPhysicsDemo.dir/cmake_clean.cmake
.PHONY : Demos/CcdPhysicsDemo/CMakeFiles/AppCcdPhysicsDemo.dir/clean

Demos/CcdPhysicsDemo/CMakeFiles/AppCcdPhysicsDemo.dir/depend:
	cd /tmp/a/icehockey/bullet-2.80-rev2531 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /tmp/a/icehockey/bullet-2.80-rev2531 /tmp/a/icehockey/bullet-2.80-rev2531/Demos/CcdPhysicsDemo /tmp/a/icehockey/bullet-2.80-rev2531 /tmp/a/icehockey/bullet-2.80-rev2531/Demos/CcdPhysicsDemo /tmp/a/icehockey/bullet-2.80-rev2531/Demos/CcdPhysicsDemo/CMakeFiles/AppCcdPhysicsDemo.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : Demos/CcdPhysicsDemo/CMakeFiles/AppCcdPhysicsDemo.dir/depend

