# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/yinshuhua/Work/FilterDataSetKit

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/yinshuhua/Work/FilterDataSetKit/build

# Include any dependencies generated for this target.
include CMakeFiles/FilterDataSetKit.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/FilterDataSetKit.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/FilterDataSetKit.dir/flags.make

CMakeFiles/FilterDataSetKit.dir/main.cpp.o: CMakeFiles/FilterDataSetKit.dir/flags.make
CMakeFiles/FilterDataSetKit.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yinshuhua/Work/FilterDataSetKit/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/FilterDataSetKit.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/FilterDataSetKit.dir/main.cpp.o -c /home/yinshuhua/Work/FilterDataSetKit/main.cpp

CMakeFiles/FilterDataSetKit.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/FilterDataSetKit.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yinshuhua/Work/FilterDataSetKit/main.cpp > CMakeFiles/FilterDataSetKit.dir/main.cpp.i

CMakeFiles/FilterDataSetKit.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/FilterDataSetKit.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yinshuhua/Work/FilterDataSetKit/main.cpp -o CMakeFiles/FilterDataSetKit.dir/main.cpp.s

CMakeFiles/FilterDataSetKit.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/FilterDataSetKit.dir/main.cpp.o.requires

CMakeFiles/FilterDataSetKit.dir/main.cpp.o.provides: CMakeFiles/FilterDataSetKit.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/FilterDataSetKit.dir/build.make CMakeFiles/FilterDataSetKit.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/FilterDataSetKit.dir/main.cpp.o.provides

CMakeFiles/FilterDataSetKit.dir/main.cpp.o.provides.build: CMakeFiles/FilterDataSetKit.dir/main.cpp.o


# Object files for target FilterDataSetKit
FilterDataSetKit_OBJECTS = \
"CMakeFiles/FilterDataSetKit.dir/main.cpp.o"

# External object files for target FilterDataSetKit
FilterDataSetKit_EXTERNAL_OBJECTS =

FilterDataSetKit: CMakeFiles/FilterDataSetKit.dir/main.cpp.o
FilterDataSetKit: CMakeFiles/FilterDataSetKit.dir/build.make
FilterDataSetKit: /usr/local/lib/libopencv_videostab.so.2.4.9
FilterDataSetKit: /usr/local/lib/libopencv_ts.a
FilterDataSetKit: /usr/local/lib/libopencv_superres.so.2.4.9
FilterDataSetKit: /usr/local/lib/libopencv_stitching.so.2.4.9
FilterDataSetKit: /usr/local/lib/libopencv_contrib.so.2.4.9
FilterDataSetKit: /usr/local/lib/libopencv_nonfree.so.2.4.9
FilterDataSetKit: /usr/local/lib/libopencv_ocl.so.2.4.9
FilterDataSetKit: /usr/local/lib/libopencv_gpu.so.2.4.9
FilterDataSetKit: /usr/local/lib/libopencv_photo.so.2.4.9
FilterDataSetKit: /usr/local/lib/libopencv_objdetect.so.2.4.9
FilterDataSetKit: /usr/local/lib/libopencv_legacy.so.2.4.9
FilterDataSetKit: /usr/local/lib/libopencv_video.so.2.4.9
FilterDataSetKit: /usr/local/lib/libopencv_ml.so.2.4.9
FilterDataSetKit: /usr/local/lib/libopencv_calib3d.so.2.4.9
FilterDataSetKit: /usr/local/lib/libopencv_features2d.so.2.4.9
FilterDataSetKit: /usr/local/lib/libopencv_highgui.so.2.4.9
FilterDataSetKit: /usr/local/lib/libopencv_imgproc.so.2.4.9
FilterDataSetKit: /usr/local/lib/libopencv_flann.so.2.4.9
FilterDataSetKit: /usr/local/lib/libopencv_core.so.2.4.9
FilterDataSetKit: CMakeFiles/FilterDataSetKit.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/yinshuhua/Work/FilterDataSetKit/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable FilterDataSetKit"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/FilterDataSetKit.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/FilterDataSetKit.dir/build: FilterDataSetKit

.PHONY : CMakeFiles/FilterDataSetKit.dir/build

CMakeFiles/FilterDataSetKit.dir/requires: CMakeFiles/FilterDataSetKit.dir/main.cpp.o.requires

.PHONY : CMakeFiles/FilterDataSetKit.dir/requires

CMakeFiles/FilterDataSetKit.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/FilterDataSetKit.dir/cmake_clean.cmake
.PHONY : CMakeFiles/FilterDataSetKit.dir/clean

CMakeFiles/FilterDataSetKit.dir/depend:
	cd /home/yinshuhua/Work/FilterDataSetKit/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yinshuhua/Work/FilterDataSetKit /home/yinshuhua/Work/FilterDataSetKit /home/yinshuhua/Work/FilterDataSetKit/build /home/yinshuhua/Work/FilterDataSetKit/build /home/yinshuhua/Work/FilterDataSetKit/build/CMakeFiles/FilterDataSetKit.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/FilterDataSetKit.dir/depend
