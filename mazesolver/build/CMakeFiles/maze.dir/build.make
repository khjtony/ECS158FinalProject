# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.4

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.4.0/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.4.0/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/khjtony/Google Drive/ArchievedClassMaterial/Spring2016/ECS158/HJK/FinalProject/mazesolver"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/khjtony/Google Drive/ArchievedClassMaterial/Spring2016/ECS158/HJK/FinalProject/mazesolver/build"

# Include any dependencies generated for this target.
include CMakeFiles/maze.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/maze.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/maze.dir/flags.make

CMakeFiles/maze.dir/mazesolver.cpp.o: CMakeFiles/maze.dir/flags.make
CMakeFiles/maze.dir/mazesolver.cpp.o: ../mazesolver.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/khjtony/Google Drive/ArchievedClassMaterial/Spring2016/ECS158/HJK/FinalProject/mazesolver/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/maze.dir/mazesolver.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/maze.dir/mazesolver.cpp.o -c "/Users/khjtony/Google Drive/ArchievedClassMaterial/Spring2016/ECS158/HJK/FinalProject/mazesolver/mazesolver.cpp"

CMakeFiles/maze.dir/mazesolver.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/maze.dir/mazesolver.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/khjtony/Google Drive/ArchievedClassMaterial/Spring2016/ECS158/HJK/FinalProject/mazesolver/mazesolver.cpp" > CMakeFiles/maze.dir/mazesolver.cpp.i

CMakeFiles/maze.dir/mazesolver.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/maze.dir/mazesolver.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/khjtony/Google Drive/ArchievedClassMaterial/Spring2016/ECS158/HJK/FinalProject/mazesolver/mazesolver.cpp" -o CMakeFiles/maze.dir/mazesolver.cpp.s

CMakeFiles/maze.dir/mazesolver.cpp.o.requires:

.PHONY : CMakeFiles/maze.dir/mazesolver.cpp.o.requires

CMakeFiles/maze.dir/mazesolver.cpp.o.provides: CMakeFiles/maze.dir/mazesolver.cpp.o.requires
	$(MAKE) -f CMakeFiles/maze.dir/build.make CMakeFiles/maze.dir/mazesolver.cpp.o.provides.build
.PHONY : CMakeFiles/maze.dir/mazesolver.cpp.o.provides

CMakeFiles/maze.dir/mazesolver.cpp.o.provides.build: CMakeFiles/maze.dir/mazesolver.cpp.o


# Object files for target maze
maze_OBJECTS = \
"CMakeFiles/maze.dir/mazesolver.cpp.o"

# External object files for target maze
maze_EXTERNAL_OBJECTS =

maze: CMakeFiles/maze.dir/mazesolver.cpp.o
maze: CMakeFiles/maze.dir/build.make
maze: /usr/local/lib/libopencv_videostab.3.1.0.dylib
maze: /usr/local/lib/libopencv_superres.3.1.0.dylib
maze: /usr/local/lib/libopencv_stitching.3.1.0.dylib
maze: /usr/local/lib/libopencv_shape.3.1.0.dylib
maze: /usr/local/lib/libopencv_photo.3.1.0.dylib
maze: /usr/local/lib/libopencv_objdetect.3.1.0.dylib
maze: /usr/local/lib/libopencv_calib3d.3.1.0.dylib
maze: /usr/local/lib/libopencv_features2d.3.1.0.dylib
maze: /usr/local/lib/libopencv_ml.3.1.0.dylib
maze: /usr/local/lib/libopencv_highgui.3.1.0.dylib
maze: /usr/local/lib/libopencv_videoio.3.1.0.dylib
maze: /usr/local/lib/libopencv_imgcodecs.3.1.0.dylib
maze: /usr/local/lib/libopencv_flann.3.1.0.dylib
maze: /usr/local/lib/libopencv_video.3.1.0.dylib
maze: /usr/local/lib/libopencv_imgproc.3.1.0.dylib
maze: /usr/local/lib/libopencv_core.3.1.0.dylib
maze: CMakeFiles/maze.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/khjtony/Google Drive/ArchievedClassMaterial/Spring2016/ECS158/HJK/FinalProject/mazesolver/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable maze"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/maze.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/maze.dir/build: maze

.PHONY : CMakeFiles/maze.dir/build

CMakeFiles/maze.dir/requires: CMakeFiles/maze.dir/mazesolver.cpp.o.requires

.PHONY : CMakeFiles/maze.dir/requires

CMakeFiles/maze.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/maze.dir/cmake_clean.cmake
.PHONY : CMakeFiles/maze.dir/clean

CMakeFiles/maze.dir/depend:
	cd "/Users/khjtony/Google Drive/ArchievedClassMaterial/Spring2016/ECS158/HJK/FinalProject/mazesolver/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/khjtony/Google Drive/ArchievedClassMaterial/Spring2016/ECS158/HJK/FinalProject/mazesolver" "/Users/khjtony/Google Drive/ArchievedClassMaterial/Spring2016/ECS158/HJK/FinalProject/mazesolver" "/Users/khjtony/Google Drive/ArchievedClassMaterial/Spring2016/ECS158/HJK/FinalProject/mazesolver/build" "/Users/khjtony/Google Drive/ArchievedClassMaterial/Spring2016/ECS158/HJK/FinalProject/mazesolver/build" "/Users/khjtony/Google Drive/ArchievedClassMaterial/Spring2016/ECS158/HJK/FinalProject/mazesolver/build/CMakeFiles/maze.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/maze.dir/depend

