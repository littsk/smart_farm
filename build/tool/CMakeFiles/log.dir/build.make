# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/littsk/Desktop/SensorCollect

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/littsk/Desktop/SensorCollect/build

# Include any dependencies generated for this target.
include tool/CMakeFiles/log.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include tool/CMakeFiles/log.dir/compiler_depend.make

# Include the progress variables for this target.
include tool/CMakeFiles/log.dir/progress.make

# Include the compile flags for this target's objects.
include tool/CMakeFiles/log.dir/flags.make

tool/CMakeFiles/log.dir/src/log.cpp.o: tool/CMakeFiles/log.dir/flags.make
tool/CMakeFiles/log.dir/src/log.cpp.o: ../tool/src/log.cpp
tool/CMakeFiles/log.dir/src/log.cpp.o: tool/CMakeFiles/log.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/littsk/Desktop/SensorCollect/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tool/CMakeFiles/log.dir/src/log.cpp.o"
	cd /home/littsk/Desktop/SensorCollect/build/tool && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT tool/CMakeFiles/log.dir/src/log.cpp.o -MF CMakeFiles/log.dir/src/log.cpp.o.d -o CMakeFiles/log.dir/src/log.cpp.o -c /home/littsk/Desktop/SensorCollect/tool/src/log.cpp

tool/CMakeFiles/log.dir/src/log.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/log.dir/src/log.cpp.i"
	cd /home/littsk/Desktop/SensorCollect/build/tool && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/littsk/Desktop/SensorCollect/tool/src/log.cpp > CMakeFiles/log.dir/src/log.cpp.i

tool/CMakeFiles/log.dir/src/log.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/log.dir/src/log.cpp.s"
	cd /home/littsk/Desktop/SensorCollect/build/tool && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/littsk/Desktop/SensorCollect/tool/src/log.cpp -o CMakeFiles/log.dir/src/log.cpp.s

# Object files for target log
log_OBJECTS = \
"CMakeFiles/log.dir/src/log.cpp.o"

# External object files for target log
log_EXTERNAL_OBJECTS =

tool/liblog.a: tool/CMakeFiles/log.dir/src/log.cpp.o
tool/liblog.a: tool/CMakeFiles/log.dir/build.make
tool/liblog.a: tool/CMakeFiles/log.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/littsk/Desktop/SensorCollect/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library liblog.a"
	cd /home/littsk/Desktop/SensorCollect/build/tool && $(CMAKE_COMMAND) -P CMakeFiles/log.dir/cmake_clean_target.cmake
	cd /home/littsk/Desktop/SensorCollect/build/tool && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/log.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tool/CMakeFiles/log.dir/build: tool/liblog.a
.PHONY : tool/CMakeFiles/log.dir/build

tool/CMakeFiles/log.dir/clean:
	cd /home/littsk/Desktop/SensorCollect/build/tool && $(CMAKE_COMMAND) -P CMakeFiles/log.dir/cmake_clean.cmake
.PHONY : tool/CMakeFiles/log.dir/clean

tool/CMakeFiles/log.dir/depend:
	cd /home/littsk/Desktop/SensorCollect/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/littsk/Desktop/SensorCollect /home/littsk/Desktop/SensorCollect/tool /home/littsk/Desktop/SensorCollect/build /home/littsk/Desktop/SensorCollect/build/tool /home/littsk/Desktop/SensorCollect/build/tool/CMakeFiles/log.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tool/CMakeFiles/log.dir/depend

