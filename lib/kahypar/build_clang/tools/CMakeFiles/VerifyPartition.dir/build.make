# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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
CMAKE_SOURCE_DIR = /home/snelgrov/code/LSOracle/lib/kahypar

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/snelgrov/code/LSOracle/lib/kahypar/build_clang

# Include any dependencies generated for this target.
include tools/CMakeFiles/VerifyPartition.dir/depend.make

# Include the progress variables for this target.
include tools/CMakeFiles/VerifyPartition.dir/progress.make

# Include the compile flags for this target's objects.
include tools/CMakeFiles/VerifyPartition.dir/flags.make

tools/CMakeFiles/VerifyPartition.dir/verify_partition.cc.o: tools/CMakeFiles/VerifyPartition.dir/flags.make
tools/CMakeFiles/VerifyPartition.dir/verify_partition.cc.o: ../tools/verify_partition.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/snelgrov/code/LSOracle/lib/kahypar/build_clang/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tools/CMakeFiles/VerifyPartition.dir/verify_partition.cc.o"
	cd /home/snelgrov/code/LSOracle/lib/kahypar/build_clang/tools && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/VerifyPartition.dir/verify_partition.cc.o -c /home/snelgrov/code/LSOracle/lib/kahypar/tools/verify_partition.cc

tools/CMakeFiles/VerifyPartition.dir/verify_partition.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/VerifyPartition.dir/verify_partition.cc.i"
	cd /home/snelgrov/code/LSOracle/lib/kahypar/build_clang/tools && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/snelgrov/code/LSOracle/lib/kahypar/tools/verify_partition.cc > CMakeFiles/VerifyPartition.dir/verify_partition.cc.i

tools/CMakeFiles/VerifyPartition.dir/verify_partition.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/VerifyPartition.dir/verify_partition.cc.s"
	cd /home/snelgrov/code/LSOracle/lib/kahypar/build_clang/tools && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/snelgrov/code/LSOracle/lib/kahypar/tools/verify_partition.cc -o CMakeFiles/VerifyPartition.dir/verify_partition.cc.s

# Object files for target VerifyPartition
VerifyPartition_OBJECTS = \
"CMakeFiles/VerifyPartition.dir/verify_partition.cc.o"

# External object files for target VerifyPartition
VerifyPartition_EXTERNAL_OBJECTS =

tools/VerifyPartition: tools/CMakeFiles/VerifyPartition.dir/verify_partition.cc.o
tools/VerifyPartition: tools/CMakeFiles/VerifyPartition.dir/build.make
tools/VerifyPartition: tools/CMakeFiles/VerifyPartition.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/snelgrov/code/LSOracle/lib/kahypar/build_clang/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable VerifyPartition"
	cd /home/snelgrov/code/LSOracle/lib/kahypar/build_clang/tools && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/VerifyPartition.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tools/CMakeFiles/VerifyPartition.dir/build: tools/VerifyPartition

.PHONY : tools/CMakeFiles/VerifyPartition.dir/build

tools/CMakeFiles/VerifyPartition.dir/clean:
	cd /home/snelgrov/code/LSOracle/lib/kahypar/build_clang/tools && $(CMAKE_COMMAND) -P CMakeFiles/VerifyPartition.dir/cmake_clean.cmake
.PHONY : tools/CMakeFiles/VerifyPartition.dir/clean

tools/CMakeFiles/VerifyPartition.dir/depend:
	cd /home/snelgrov/code/LSOracle/lib/kahypar/build_clang && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/snelgrov/code/LSOracle/lib/kahypar /home/snelgrov/code/LSOracle/lib/kahypar/tools /home/snelgrov/code/LSOracle/lib/kahypar/build_clang /home/snelgrov/code/LSOracle/lib/kahypar/build_clang/tools /home/snelgrov/code/LSOracle/lib/kahypar/build_clang/tools/CMakeFiles/VerifyPartition.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tools/CMakeFiles/VerifyPartition.dir/depend
