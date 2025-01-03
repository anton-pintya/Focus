# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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
CMAKE_COMMAND = /home/apin/cmake-3.5.1/bin/cmake

# The command to remove a file.
RM = /home/apin/cmake-3.5.1/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/apin/Desktop/ComputerVision/Focus

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/apin/Desktop/ComputerVision/Focus

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/home/apin/cmake-3.5.1/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/home/apin/cmake-3.5.1/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/apin/Desktop/ComputerVision/Focus/CMakeFiles /home/apin/Desktop/ComputerVision/Focus/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/apin/Desktop/ComputerVision/Focus/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named msg_generate

# Build rule for target.
msg_generate: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 msg_generate
.PHONY : msg_generate

# fast build rule for target.
msg_generate/fast:
	$(MAKE) -f CMakeFiles/msg_generate.dir/build.make CMakeFiles/msg_generate.dir/build
.PHONY : msg_generate/fast

#=============================================================================
# Target rules for targets named VINS-Focus

# Build rule for target.
VINS-Focus: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 VINS-Focus
.PHONY : VINS-Focus

# fast build rule for target.
VINS-Focus/fast:
	$(MAKE) -f CMakeFiles/VINS-Focus.dir/build.make CMakeFiles/VINS-Focus.dir/build
.PHONY : VINS-Focus/fast

#=============================================================================
# Target rules for targets named core

# Build rule for target.
core: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 core
.PHONY : core

# fast build rule for target.
core/fast:
	$(MAKE) -f build/core/CMakeFiles/core.dir/build.make build/core/CMakeFiles/core.dir/build
.PHONY : core/fast

#=============================================================================
# Target rules for targets named sensors

# Build rule for target.
sensors: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 sensors
.PHONY : sensors

# fast build rule for target.
sensors/fast:
	$(MAKE) -f build/sensors/CMakeFiles/sensors.dir/build.make build/sensors/CMakeFiles/sensors.dir/build
.PHONY : sensors/fast

#=============================================================================
# Target rules for targets named utils

# Build rule for target.
utils: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 utils
.PHONY : utils

# fast build rule for target.
utils/fast:
	$(MAKE) -f build/utils/CMakeFiles/utils.dir/build.make build/utils/CMakeFiles/utils.dir/build
.PHONY : utils/fast

#=============================================================================
# Target rules for targets named nodes

# Build rule for target.
nodes: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 nodes
.PHONY : nodes

# fast build rule for target.
nodes/fast:
	$(MAKE) -f build/nodes/CMakeFiles/nodes.dir/build.make build/nodes/CMakeFiles/nodes.dir/build
.PHONY : nodes/fast

main.o: main.cpp.o

.PHONY : main.o

# target to build an object file
main.cpp.o:
	$(MAKE) -f CMakeFiles/VINS-Focus.dir/build.make CMakeFiles/VINS-Focus.dir/main.cpp.o
.PHONY : main.cpp.o

main.i: main.cpp.i

.PHONY : main.i

# target to preprocess a source file
main.cpp.i:
	$(MAKE) -f CMakeFiles/VINS-Focus.dir/build.make CMakeFiles/VINS-Focus.dir/main.cpp.i
.PHONY : main.cpp.i

main.s: main.cpp.s

.PHONY : main.s

# target to generate assembly for a file
main.cpp.s:
	$(MAKE) -f CMakeFiles/VINS-Focus.dir/build.make CMakeFiles/VINS-Focus.dir/main.cpp.s
.PHONY : main.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... msg_generate"
	@echo "... VINS-Focus"
	@echo "... core"
	@echo "... sensors"
	@echo "... utils"
	@echo "... nodes"
	@echo "... main.o"
	@echo "... main.i"
	@echo "... main.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

