# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.13.3/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.13.3/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/emma/coding/c-image-processing

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/emma/coding/c-image-processing/build

# Include any dependencies generated for this target.
include CMakeFiles/bmp-filter.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/bmp-filter.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/bmp-filter.dir/flags.make

CMakeFiles/bmp-filter.dir/src/main.cpp.o: CMakeFiles/bmp-filter.dir/flags.make
CMakeFiles/bmp-filter.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/emma/coding/c-image-processing/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/bmp-filter.dir/src/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bmp-filter.dir/src/main.cpp.o -c /Users/emma/coding/c-image-processing/src/main.cpp

CMakeFiles/bmp-filter.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bmp-filter.dir/src/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/emma/coding/c-image-processing/src/main.cpp > CMakeFiles/bmp-filter.dir/src/main.cpp.i

CMakeFiles/bmp-filter.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bmp-filter.dir/src/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/emma/coding/c-image-processing/src/main.cpp -o CMakeFiles/bmp-filter.dir/src/main.cpp.s

# Object files for target bmp-filter
bmp__filter_OBJECTS = \
"CMakeFiles/bmp-filter.dir/src/main.cpp.o"

# External object files for target bmp-filter
bmp__filter_EXTERNAL_OBJECTS =

bmp-filter: CMakeFiles/bmp-filter.dir/src/main.cpp.o
bmp-filter: CMakeFiles/bmp-filter.dir/build.make
bmp-filter: CMakeFiles/bmp-filter.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/emma/coding/c-image-processing/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bmp-filter"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/bmp-filter.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/bmp-filter.dir/build: bmp-filter

.PHONY : CMakeFiles/bmp-filter.dir/build

CMakeFiles/bmp-filter.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/bmp-filter.dir/cmake_clean.cmake
.PHONY : CMakeFiles/bmp-filter.dir/clean

CMakeFiles/bmp-filter.dir/depend:
	cd /Users/emma/coding/c-image-processing/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/emma/coding/c-image-processing /Users/emma/coding/c-image-processing /Users/emma/coding/c-image-processing/build /Users/emma/coding/c-image-processing/build /Users/emma/coding/c-image-processing/build/CMakeFiles/bmp-filter.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/bmp-filter.dir/depend

