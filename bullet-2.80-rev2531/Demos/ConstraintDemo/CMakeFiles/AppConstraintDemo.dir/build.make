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
CMAKE_SOURCE_DIR = /tmp/icehockey/bullet-2.80-rev2531

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /tmp/icehockey/bullet-2.80-rev2531

# Include any dependencies generated for this target.
include Demos/ConstraintDemo/CMakeFiles/AppConstraintDemo.dir/depend.make

# Include the progress variables for this target.
include Demos/ConstraintDemo/CMakeFiles/AppConstraintDemo.dir/progress.make

# Include the compile flags for this target's objects.
include Demos/ConstraintDemo/CMakeFiles/AppConstraintDemo.dir/flags.make

Demos/ConstraintDemo/CMakeFiles/AppConstraintDemo.dir/ConstraintDemo.o: Demos/ConstraintDemo/CMakeFiles/AppConstraintDemo.dir/flags.make
Demos/ConstraintDemo/CMakeFiles/AppConstraintDemo.dir/ConstraintDemo.o: Demos/ConstraintDemo/ConstraintDemo.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /tmp/icehockey/bullet-2.80-rev2531/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object Demos/ConstraintDemo/CMakeFiles/AppConstraintDemo.dir/ConstraintDemo.o"
	cd /tmp/icehockey/bullet-2.80-rev2531/Demos/ConstraintDemo && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/AppConstraintDemo.dir/ConstraintDemo.o -c /tmp/icehockey/bullet-2.80-rev2531/Demos/ConstraintDemo/ConstraintDemo.cpp

Demos/ConstraintDemo/CMakeFiles/AppConstraintDemo.dir/ConstraintDemo.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AppConstraintDemo.dir/ConstraintDemo.i"
	cd /tmp/icehockey/bullet-2.80-rev2531/Demos/ConstraintDemo && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /tmp/icehockey/bullet-2.80-rev2531/Demos/ConstraintDemo/ConstraintDemo.cpp > CMakeFiles/AppConstraintDemo.dir/ConstraintDemo.i

Demos/ConstraintDemo/CMakeFiles/AppConstraintDemo.dir/ConstraintDemo.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AppConstraintDemo.dir/ConstraintDemo.s"
	cd /tmp/icehockey/bullet-2.80-rev2531/Demos/ConstraintDemo && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /tmp/icehockey/bullet-2.80-rev2531/Demos/ConstraintDemo/ConstraintDemo.cpp -o CMakeFiles/AppConstraintDemo.dir/ConstraintDemo.s

Demos/ConstraintDemo/CMakeFiles/AppConstraintDemo.dir/ConstraintDemo.o.requires:
.PHONY : Demos/ConstraintDemo/CMakeFiles/AppConstraintDemo.dir/ConstraintDemo.o.requires

Demos/ConstraintDemo/CMakeFiles/AppConstraintDemo.dir/ConstraintDemo.o.provides: Demos/ConstraintDemo/CMakeFiles/AppConstraintDemo.dir/ConstraintDemo.o.requires
	$(MAKE) -f Demos/ConstraintDemo/CMakeFiles/AppConstraintDemo.dir/build.make Demos/ConstraintDemo/CMakeFiles/AppConstraintDemo.dir/ConstraintDemo.o.provides.build
.PHONY : Demos/ConstraintDemo/CMakeFiles/AppConstraintDemo.dir/ConstraintDemo.o.provides

Demos/ConstraintDemo/CMakeFiles/AppConstraintDemo.dir/ConstraintDemo.o.provides.build: Demos/ConstraintDemo/CMakeFiles/AppConstraintDemo.dir/ConstraintDemo.o

Demos/ConstraintDemo/CMakeFiles/AppConstraintDemo.dir/main.o: Demos/ConstraintDemo/CMakeFiles/AppConstraintDemo.dir/flags.make
Demos/ConstraintDemo/CMakeFiles/AppConstraintDemo.dir/main.o: Demos/ConstraintDemo/main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /tmp/icehockey/bullet-2.80-rev2531/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object Demos/ConstraintDemo/CMakeFiles/AppConstraintDemo.dir/main.o"
	cd /tmp/icehockey/bullet-2.80-rev2531/Demos/ConstraintDemo && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/AppConstraintDemo.dir/main.o -c /tmp/icehockey/bullet-2.80-rev2531/Demos/ConstraintDemo/main.cpp

Demos/ConstraintDemo/CMakeFiles/AppConstraintDemo.dir/main.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AppConstraintDemo.dir/main.i"
	cd /tmp/icehockey/bullet-2.80-rev2531/Demos/ConstraintDemo && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /tmp/icehockey/bullet-2.80-rev2531/Demos/ConstraintDemo/main.cpp > CMakeFiles/AppConstraintDemo.dir/main.i

Demos/ConstraintDemo/CMakeFiles/AppConstraintDemo.dir/main.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AppConstraintDemo.dir/main.s"
	cd /tmp/icehockey/bullet-2.80-rev2531/Demos/ConstraintDemo && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /tmp/icehockey/bullet-2.80-rev2531/Demos/ConstraintDemo/main.cpp -o CMakeFiles/AppConstraintDemo.dir/main.s

Demos/ConstraintDemo/CMakeFiles/AppConstraintDemo.dir/main.o.requires:
.PHONY : Demos/ConstraintDemo/CMakeFiles/AppConstraintDemo.dir/main.o.requires

Demos/ConstraintDemo/CMakeFiles/AppConstraintDemo.dir/main.o.provides: Demos/ConstraintDemo/CMakeFiles/AppConstraintDemo.dir/main.o.requires
	$(MAKE) -f Demos/ConstraintDemo/CMakeFiles/AppConstraintDemo.dir/build.make Demos/ConstraintDemo/CMakeFiles/AppConstraintDemo.dir/main.o.provides.build
.PHONY : Demos/ConstraintDemo/CMakeFiles/AppConstraintDemo.dir/main.o.provides

Demos/ConstraintDemo/CMakeFiles/AppConstraintDemo.dir/main.o.provides.build: Demos/ConstraintDemo/CMakeFiles/AppConstraintDemo.dir/main.o

# Object files for target AppConstraintDemo
AppConstraintDemo_OBJECTS = \
"CMakeFiles/AppConstraintDemo.dir/ConstraintDemo.o" \
"CMakeFiles/AppConstraintDemo.dir/main.o"

# External object files for target AppConstraintDemo
AppConstraintDemo_EXTERNAL_OBJECTS =

Demos/ConstraintDemo/AppConstraintDemo: Demos/ConstraintDemo/CMakeFiles/AppConstraintDemo.dir/ConstraintDemo.o
Demos/ConstraintDemo/AppConstraintDemo: Demos/ConstraintDemo/CMakeFiles/AppConstraintDemo.dir/main.o
Demos/ConstraintDemo/AppConstraintDemo: Demos/OpenGL/libOpenGLSupport.a
Demos/ConstraintDemo/AppConstraintDemo: Extras/Serialize/BulletWorldImporter/libBulletWorldImporter.a
Demos/ConstraintDemo/AppConstraintDemo: src/BulletDynamics/libBulletDynamics.a
Demos/ConstraintDemo/AppConstraintDemo: src/BulletCollision/libBulletCollision.a
Demos/ConstraintDemo/AppConstraintDemo: src/LinearMath/libLinearMath.a
Demos/ConstraintDemo/AppConstraintDemo: Extras/Serialize/BulletFileLoader/libBulletFileLoader.a
Demos/ConstraintDemo/AppConstraintDemo: /usr/lib/x86_64-linux-gnu/libglut.so
Demos/ConstraintDemo/AppConstraintDemo: /usr/lib/x86_64-linux-gnu/libGL.so
Demos/ConstraintDemo/AppConstraintDemo: /usr/lib/x86_64-linux-gnu/libGLU.so
Demos/ConstraintDemo/AppConstraintDemo: Demos/ConstraintDemo/CMakeFiles/AppConstraintDemo.dir/build.make
Demos/ConstraintDemo/AppConstraintDemo: Demos/ConstraintDemo/CMakeFiles/AppConstraintDemo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable AppConstraintDemo"
	cd /tmp/icehockey/bullet-2.80-rev2531/Demos/ConstraintDemo && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/AppConstraintDemo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Demos/ConstraintDemo/CMakeFiles/AppConstraintDemo.dir/build: Demos/ConstraintDemo/AppConstraintDemo
.PHONY : Demos/ConstraintDemo/CMakeFiles/AppConstraintDemo.dir/build

Demos/ConstraintDemo/CMakeFiles/AppConstraintDemo.dir/requires: Demos/ConstraintDemo/CMakeFiles/AppConstraintDemo.dir/ConstraintDemo.o.requires
Demos/ConstraintDemo/CMakeFiles/AppConstraintDemo.dir/requires: Demos/ConstraintDemo/CMakeFiles/AppConstraintDemo.dir/main.o.requires
.PHONY : Demos/ConstraintDemo/CMakeFiles/AppConstraintDemo.dir/requires

Demos/ConstraintDemo/CMakeFiles/AppConstraintDemo.dir/clean:
	cd /tmp/icehockey/bullet-2.80-rev2531/Demos/ConstraintDemo && $(CMAKE_COMMAND) -P CMakeFiles/AppConstraintDemo.dir/cmake_clean.cmake
.PHONY : Demos/ConstraintDemo/CMakeFiles/AppConstraintDemo.dir/clean

Demos/ConstraintDemo/CMakeFiles/AppConstraintDemo.dir/depend:
	cd /tmp/icehockey/bullet-2.80-rev2531 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /tmp/icehockey/bullet-2.80-rev2531 /tmp/icehockey/bullet-2.80-rev2531/Demos/ConstraintDemo /tmp/icehockey/bullet-2.80-rev2531 /tmp/icehockey/bullet-2.80-rev2531/Demos/ConstraintDemo /tmp/icehockey/bullet-2.80-rev2531/Demos/ConstraintDemo/CMakeFiles/AppConstraintDemo.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : Demos/ConstraintDemo/CMakeFiles/AppConstraintDemo.dir/depend

