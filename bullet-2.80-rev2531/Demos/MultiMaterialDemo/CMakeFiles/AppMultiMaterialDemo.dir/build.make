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
CMAKE_SOURCE_DIR = /tmp/a/b/icehockey/bullet-2.80-rev2531

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /tmp/a/b/icehockey/bullet-2.80-rev2531

# Include any dependencies generated for this target.
include Demos/MultiMaterialDemo/CMakeFiles/AppMultiMaterialDemo.dir/depend.make

# Include the progress variables for this target.
include Demos/MultiMaterialDemo/CMakeFiles/AppMultiMaterialDemo.dir/progress.make

# Include the compile flags for this target's objects.
include Demos/MultiMaterialDemo/CMakeFiles/AppMultiMaterialDemo.dir/flags.make

Demos/MultiMaterialDemo/CMakeFiles/AppMultiMaterialDemo.dir/MultiMaterialDemo.o: Demos/MultiMaterialDemo/CMakeFiles/AppMultiMaterialDemo.dir/flags.make
Demos/MultiMaterialDemo/CMakeFiles/AppMultiMaterialDemo.dir/MultiMaterialDemo.o: Demos/MultiMaterialDemo/MultiMaterialDemo.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /tmp/a/b/icehockey/bullet-2.80-rev2531/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object Demos/MultiMaterialDemo/CMakeFiles/AppMultiMaterialDemo.dir/MultiMaterialDemo.o"
	cd /tmp/a/b/icehockey/bullet-2.80-rev2531/Demos/MultiMaterialDemo && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/AppMultiMaterialDemo.dir/MultiMaterialDemo.o -c /tmp/a/b/icehockey/bullet-2.80-rev2531/Demos/MultiMaterialDemo/MultiMaterialDemo.cpp

Demos/MultiMaterialDemo/CMakeFiles/AppMultiMaterialDemo.dir/MultiMaterialDemo.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AppMultiMaterialDemo.dir/MultiMaterialDemo.i"
	cd /tmp/a/b/icehockey/bullet-2.80-rev2531/Demos/MultiMaterialDemo && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /tmp/a/b/icehockey/bullet-2.80-rev2531/Demos/MultiMaterialDemo/MultiMaterialDemo.cpp > CMakeFiles/AppMultiMaterialDemo.dir/MultiMaterialDemo.i

Demos/MultiMaterialDemo/CMakeFiles/AppMultiMaterialDemo.dir/MultiMaterialDemo.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AppMultiMaterialDemo.dir/MultiMaterialDemo.s"
	cd /tmp/a/b/icehockey/bullet-2.80-rev2531/Demos/MultiMaterialDemo && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /tmp/a/b/icehockey/bullet-2.80-rev2531/Demos/MultiMaterialDemo/MultiMaterialDemo.cpp -o CMakeFiles/AppMultiMaterialDemo.dir/MultiMaterialDemo.s

Demos/MultiMaterialDemo/CMakeFiles/AppMultiMaterialDemo.dir/MultiMaterialDemo.o.requires:
.PHONY : Demos/MultiMaterialDemo/CMakeFiles/AppMultiMaterialDemo.dir/MultiMaterialDemo.o.requires

Demos/MultiMaterialDemo/CMakeFiles/AppMultiMaterialDemo.dir/MultiMaterialDemo.o.provides: Demos/MultiMaterialDemo/CMakeFiles/AppMultiMaterialDemo.dir/MultiMaterialDemo.o.requires
	$(MAKE) -f Demos/MultiMaterialDemo/CMakeFiles/AppMultiMaterialDemo.dir/build.make Demos/MultiMaterialDemo/CMakeFiles/AppMultiMaterialDemo.dir/MultiMaterialDemo.o.provides.build
.PHONY : Demos/MultiMaterialDemo/CMakeFiles/AppMultiMaterialDemo.dir/MultiMaterialDemo.o.provides

Demos/MultiMaterialDemo/CMakeFiles/AppMultiMaterialDemo.dir/MultiMaterialDemo.o.provides.build: Demos/MultiMaterialDemo/CMakeFiles/AppMultiMaterialDemo.dir/MultiMaterialDemo.o

Demos/MultiMaterialDemo/CMakeFiles/AppMultiMaterialDemo.dir/main.o: Demos/MultiMaterialDemo/CMakeFiles/AppMultiMaterialDemo.dir/flags.make
Demos/MultiMaterialDemo/CMakeFiles/AppMultiMaterialDemo.dir/main.o: Demos/MultiMaterialDemo/main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /tmp/a/b/icehockey/bullet-2.80-rev2531/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object Demos/MultiMaterialDemo/CMakeFiles/AppMultiMaterialDemo.dir/main.o"
	cd /tmp/a/b/icehockey/bullet-2.80-rev2531/Demos/MultiMaterialDemo && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/AppMultiMaterialDemo.dir/main.o -c /tmp/a/b/icehockey/bullet-2.80-rev2531/Demos/MultiMaterialDemo/main.cpp

Demos/MultiMaterialDemo/CMakeFiles/AppMultiMaterialDemo.dir/main.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AppMultiMaterialDemo.dir/main.i"
	cd /tmp/a/b/icehockey/bullet-2.80-rev2531/Demos/MultiMaterialDemo && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /tmp/a/b/icehockey/bullet-2.80-rev2531/Demos/MultiMaterialDemo/main.cpp > CMakeFiles/AppMultiMaterialDemo.dir/main.i

Demos/MultiMaterialDemo/CMakeFiles/AppMultiMaterialDemo.dir/main.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AppMultiMaterialDemo.dir/main.s"
	cd /tmp/a/b/icehockey/bullet-2.80-rev2531/Demos/MultiMaterialDemo && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /tmp/a/b/icehockey/bullet-2.80-rev2531/Demos/MultiMaterialDemo/main.cpp -o CMakeFiles/AppMultiMaterialDemo.dir/main.s

Demos/MultiMaterialDemo/CMakeFiles/AppMultiMaterialDemo.dir/main.o.requires:
.PHONY : Demos/MultiMaterialDemo/CMakeFiles/AppMultiMaterialDemo.dir/main.o.requires

Demos/MultiMaterialDemo/CMakeFiles/AppMultiMaterialDemo.dir/main.o.provides: Demos/MultiMaterialDemo/CMakeFiles/AppMultiMaterialDemo.dir/main.o.requires
	$(MAKE) -f Demos/MultiMaterialDemo/CMakeFiles/AppMultiMaterialDemo.dir/build.make Demos/MultiMaterialDemo/CMakeFiles/AppMultiMaterialDemo.dir/main.o.provides.build
.PHONY : Demos/MultiMaterialDemo/CMakeFiles/AppMultiMaterialDemo.dir/main.o.provides

Demos/MultiMaterialDemo/CMakeFiles/AppMultiMaterialDemo.dir/main.o.provides.build: Demos/MultiMaterialDemo/CMakeFiles/AppMultiMaterialDemo.dir/main.o

# Object files for target AppMultiMaterialDemo
AppMultiMaterialDemo_OBJECTS = \
"CMakeFiles/AppMultiMaterialDemo.dir/MultiMaterialDemo.o" \
"CMakeFiles/AppMultiMaterialDemo.dir/main.o"

# External object files for target AppMultiMaterialDemo
AppMultiMaterialDemo_EXTERNAL_OBJECTS =

Demos/MultiMaterialDemo/AppMultiMaterialDemo: Demos/MultiMaterialDemo/CMakeFiles/AppMultiMaterialDemo.dir/MultiMaterialDemo.o
Demos/MultiMaterialDemo/AppMultiMaterialDemo: Demos/MultiMaterialDemo/CMakeFiles/AppMultiMaterialDemo.dir/main.o
Demos/MultiMaterialDemo/AppMultiMaterialDemo: Demos/OpenGL/libOpenGLSupport.a
Demos/MultiMaterialDemo/AppMultiMaterialDemo: src/BulletDynamics/libBulletDynamics.a
Demos/MultiMaterialDemo/AppMultiMaterialDemo: src/BulletCollision/libBulletCollision.a
Demos/MultiMaterialDemo/AppMultiMaterialDemo: src/LinearMath/libLinearMath.a
Demos/MultiMaterialDemo/AppMultiMaterialDemo: /usr/lib/x86_64-linux-gnu/libglut.so
Demos/MultiMaterialDemo/AppMultiMaterialDemo: /usr/lib/x86_64-linux-gnu/libGL.so
Demos/MultiMaterialDemo/AppMultiMaterialDemo: /usr/lib/x86_64-linux-gnu/libGLU.so
Demos/MultiMaterialDemo/AppMultiMaterialDemo: Demos/MultiMaterialDemo/CMakeFiles/AppMultiMaterialDemo.dir/build.make
Demos/MultiMaterialDemo/AppMultiMaterialDemo: Demos/MultiMaterialDemo/CMakeFiles/AppMultiMaterialDemo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable AppMultiMaterialDemo"
	cd /tmp/a/b/icehockey/bullet-2.80-rev2531/Demos/MultiMaterialDemo && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/AppMultiMaterialDemo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Demos/MultiMaterialDemo/CMakeFiles/AppMultiMaterialDemo.dir/build: Demos/MultiMaterialDemo/AppMultiMaterialDemo
.PHONY : Demos/MultiMaterialDemo/CMakeFiles/AppMultiMaterialDemo.dir/build

Demos/MultiMaterialDemo/CMakeFiles/AppMultiMaterialDemo.dir/requires: Demos/MultiMaterialDemo/CMakeFiles/AppMultiMaterialDemo.dir/MultiMaterialDemo.o.requires
Demos/MultiMaterialDemo/CMakeFiles/AppMultiMaterialDemo.dir/requires: Demos/MultiMaterialDemo/CMakeFiles/AppMultiMaterialDemo.dir/main.o.requires
.PHONY : Demos/MultiMaterialDemo/CMakeFiles/AppMultiMaterialDemo.dir/requires

Demos/MultiMaterialDemo/CMakeFiles/AppMultiMaterialDemo.dir/clean:
	cd /tmp/a/b/icehockey/bullet-2.80-rev2531/Demos/MultiMaterialDemo && $(CMAKE_COMMAND) -P CMakeFiles/AppMultiMaterialDemo.dir/cmake_clean.cmake
.PHONY : Demos/MultiMaterialDemo/CMakeFiles/AppMultiMaterialDemo.dir/clean

Demos/MultiMaterialDemo/CMakeFiles/AppMultiMaterialDemo.dir/depend:
	cd /tmp/a/b/icehockey/bullet-2.80-rev2531 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /tmp/a/b/icehockey/bullet-2.80-rev2531 /tmp/a/b/icehockey/bullet-2.80-rev2531/Demos/MultiMaterialDemo /tmp/a/b/icehockey/bullet-2.80-rev2531 /tmp/a/b/icehockey/bullet-2.80-rev2531/Demos/MultiMaterialDemo /tmp/a/b/icehockey/bullet-2.80-rev2531/Demos/MultiMaterialDemo/CMakeFiles/AppMultiMaterialDemo.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : Demos/MultiMaterialDemo/CMakeFiles/AppMultiMaterialDemo.dir/depend

