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
include Demos/ThreadingDemo/CMakeFiles/AppThreadingDemo.dir/depend.make

# Include the progress variables for this target.
include Demos/ThreadingDemo/CMakeFiles/AppThreadingDemo.dir/progress.make

# Include the compile flags for this target's objects.
include Demos/ThreadingDemo/CMakeFiles/AppThreadingDemo.dir/flags.make

Demos/ThreadingDemo/CMakeFiles/AppThreadingDemo.dir/main.o: Demos/ThreadingDemo/CMakeFiles/AppThreadingDemo.dir/flags.make
Demos/ThreadingDemo/CMakeFiles/AppThreadingDemo.dir/main.o: Demos/ThreadingDemo/main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /tmp/a/b/icehockey/bullet-2.80-rev2531/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object Demos/ThreadingDemo/CMakeFiles/AppThreadingDemo.dir/main.o"
	cd /tmp/a/b/icehockey/bullet-2.80-rev2531/Demos/ThreadingDemo && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/AppThreadingDemo.dir/main.o -c /tmp/a/b/icehockey/bullet-2.80-rev2531/Demos/ThreadingDemo/main.cpp

Demos/ThreadingDemo/CMakeFiles/AppThreadingDemo.dir/main.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AppThreadingDemo.dir/main.i"
	cd /tmp/a/b/icehockey/bullet-2.80-rev2531/Demos/ThreadingDemo && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /tmp/a/b/icehockey/bullet-2.80-rev2531/Demos/ThreadingDemo/main.cpp > CMakeFiles/AppThreadingDemo.dir/main.i

Demos/ThreadingDemo/CMakeFiles/AppThreadingDemo.dir/main.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AppThreadingDemo.dir/main.s"
	cd /tmp/a/b/icehockey/bullet-2.80-rev2531/Demos/ThreadingDemo && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /tmp/a/b/icehockey/bullet-2.80-rev2531/Demos/ThreadingDemo/main.cpp -o CMakeFiles/AppThreadingDemo.dir/main.s

Demos/ThreadingDemo/CMakeFiles/AppThreadingDemo.dir/main.o.requires:
.PHONY : Demos/ThreadingDemo/CMakeFiles/AppThreadingDemo.dir/main.o.requires

Demos/ThreadingDemo/CMakeFiles/AppThreadingDemo.dir/main.o.provides: Demos/ThreadingDemo/CMakeFiles/AppThreadingDemo.dir/main.o.requires
	$(MAKE) -f Demos/ThreadingDemo/CMakeFiles/AppThreadingDemo.dir/build.make Demos/ThreadingDemo/CMakeFiles/AppThreadingDemo.dir/main.o.provides.build
.PHONY : Demos/ThreadingDemo/CMakeFiles/AppThreadingDemo.dir/main.o.provides

Demos/ThreadingDemo/CMakeFiles/AppThreadingDemo.dir/main.o.provides.build: Demos/ThreadingDemo/CMakeFiles/AppThreadingDemo.dir/main.o

# Object files for target AppThreadingDemo
AppThreadingDemo_OBJECTS = \
"CMakeFiles/AppThreadingDemo.dir/main.o"

# External object files for target AppThreadingDemo
AppThreadingDemo_EXTERNAL_OBJECTS =

Demos/ThreadingDemo/AppThreadingDemo: Demos/ThreadingDemo/CMakeFiles/AppThreadingDemo.dir/main.o
Demos/ThreadingDemo/AppThreadingDemo: src/BulletMultiThreaded/libBulletMultiThreaded.a
Demos/ThreadingDemo/AppThreadingDemo: src/BulletDynamics/libBulletDynamics.a
Demos/ThreadingDemo/AppThreadingDemo: src/BulletCollision/libBulletCollision.a
Demos/ThreadingDemo/AppThreadingDemo: src/LinearMath/libLinearMath.a
Demos/ThreadingDemo/AppThreadingDemo: Demos/ThreadingDemo/CMakeFiles/AppThreadingDemo.dir/build.make
Demos/ThreadingDemo/AppThreadingDemo: Demos/ThreadingDemo/CMakeFiles/AppThreadingDemo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable AppThreadingDemo"
	cd /tmp/a/b/icehockey/bullet-2.80-rev2531/Demos/ThreadingDemo && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/AppThreadingDemo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Demos/ThreadingDemo/CMakeFiles/AppThreadingDemo.dir/build: Demos/ThreadingDemo/AppThreadingDemo
.PHONY : Demos/ThreadingDemo/CMakeFiles/AppThreadingDemo.dir/build

Demos/ThreadingDemo/CMakeFiles/AppThreadingDemo.dir/requires: Demos/ThreadingDemo/CMakeFiles/AppThreadingDemo.dir/main.o.requires
.PHONY : Demos/ThreadingDemo/CMakeFiles/AppThreadingDemo.dir/requires

Demos/ThreadingDemo/CMakeFiles/AppThreadingDemo.dir/clean:
	cd /tmp/a/b/icehockey/bullet-2.80-rev2531/Demos/ThreadingDemo && $(CMAKE_COMMAND) -P CMakeFiles/AppThreadingDemo.dir/cmake_clean.cmake
.PHONY : Demos/ThreadingDemo/CMakeFiles/AppThreadingDemo.dir/clean

Demos/ThreadingDemo/CMakeFiles/AppThreadingDemo.dir/depend:
	cd /tmp/a/b/icehockey/bullet-2.80-rev2531 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /tmp/a/b/icehockey/bullet-2.80-rev2531 /tmp/a/b/icehockey/bullet-2.80-rev2531/Demos/ThreadingDemo /tmp/a/b/icehockey/bullet-2.80-rev2531 /tmp/a/b/icehockey/bullet-2.80-rev2531/Demos/ThreadingDemo /tmp/a/b/icehockey/bullet-2.80-rev2531/Demos/ThreadingDemo/CMakeFiles/AppThreadingDemo.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : Demos/ThreadingDemo/CMakeFiles/AppThreadingDemo.dir/depend

