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

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/xueguoliang/cpp6/linux-network/day06/tufao

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/xueguoliang/cpp6/linux-network/day06/tufao/build

# Utility rule file for tufao1_automoc.

# Include the progress variables for this target.
include src/CMakeFiles/tufao1_automoc.dir/progress.make

src/CMakeFiles/tufao1_automoc:
	$(CMAKE_COMMAND) -E cmake_progress_report /home/xueguoliang/cpp6/linux-network/day06/tufao/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Automoc for target tufao1"
	cd /home/xueguoliang/cpp6/linux-network/day06/tufao/build/src && /usr/bin/cmake -E cmake_automoc /home/xueguoliang/cpp6/linux-network/day06/tufao/build/src/CMakeFiles/tufao1_automoc.dir/ ""

tufao1_automoc: src/CMakeFiles/tufao1_automoc
tufao1_automoc: src/CMakeFiles/tufao1_automoc.dir/build.make
.PHONY : tufao1_automoc

# Rule to build all files generated by this target.
src/CMakeFiles/tufao1_automoc.dir/build: tufao1_automoc
.PHONY : src/CMakeFiles/tufao1_automoc.dir/build

src/CMakeFiles/tufao1_automoc.dir/clean:
	cd /home/xueguoliang/cpp6/linux-network/day06/tufao/build/src && $(CMAKE_COMMAND) -P CMakeFiles/tufao1_automoc.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/tufao1_automoc.dir/clean

src/CMakeFiles/tufao1_automoc.dir/depend:
	cd /home/xueguoliang/cpp6/linux-network/day06/tufao/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/xueguoliang/cpp6/linux-network/day06/tufao /home/xueguoliang/cpp6/linux-network/day06/tufao/src /home/xueguoliang/cpp6/linux-network/day06/tufao/build /home/xueguoliang/cpp6/linux-network/day06/tufao/build/src /home/xueguoliang/cpp6/linux-network/day06/tufao/build/src/CMakeFiles/tufao1_automoc.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/tufao1_automoc.dir/depend

