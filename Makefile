# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.27.6/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.27.6/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/stefano/devel/repos/fifteen

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/stefano/devel/repos/fifteen

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Running CMake cache editor..."
	/usr/local/Cellar/cmake/3.27.6/bin/ccmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Running CMake to regenerate build system..."
	/usr/local/Cellar/cmake/3.27.6/bin/cmake --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/stefano/devel/repos/fifteen/CMakeFiles /Users/stefano/devel/repos/fifteen//CMakeFiles/progress.marks
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/stefano/devel/repos/fifteen/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named fifteen

# Build rule for target.
fifteen: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 fifteen
.PHONY : fifteen

# fast build rule for target.
fifteen/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/fifteen.dir/build.make CMakeFiles/fifteen.dir/build
.PHONY : fifteen/fast

main.o: main.cpp.o
.PHONY : main.o

# target to build an object file
main.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/fifteen.dir/build.make CMakeFiles/fifteen.dir/main.cpp.o
.PHONY : main.cpp.o

main.i: main.cpp.i
.PHONY : main.i

# target to preprocess a source file
main.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/fifteen.dir/build.make CMakeFiles/fifteen.dir/main.cpp.i
.PHONY : main.cpp.i

main.s: main.cpp.s
.PHONY : main.s

# target to generate assembly for a file
main.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/fifteen.dir/build.make CMakeFiles/fifteen.dir/main.cpp.s
.PHONY : main.cpp.s

src/fifteen_application.o: src/fifteen_application.cpp.o
.PHONY : src/fifteen_application.o

# target to build an object file
src/fifteen_application.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/fifteen.dir/build.make CMakeFiles/fifteen.dir/src/fifteen_application.cpp.o
.PHONY : src/fifteen_application.cpp.o

src/fifteen_application.i: src/fifteen_application.cpp.i
.PHONY : src/fifteen_application.i

# target to preprocess a source file
src/fifteen_application.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/fifteen.dir/build.make CMakeFiles/fifteen.dir/src/fifteen_application.cpp.i
.PHONY : src/fifteen_application.cpp.i

src/fifteen_application.s: src/fifteen_application.cpp.s
.PHONY : src/fifteen_application.s

# target to generate assembly for a file
src/fifteen_application.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/fifteen.dir/build.make CMakeFiles/fifteen.dir/src/fifteen_application.cpp.s
.PHONY : src/fifteen_application.cpp.s

src/tile_position.o: src/tile_position.cpp.o
.PHONY : src/tile_position.o

# target to build an object file
src/tile_position.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/fifteen.dir/build.make CMakeFiles/fifteen.dir/src/tile_position.cpp.o
.PHONY : src/tile_position.cpp.o

src/tile_position.i: src/tile_position.cpp.i
.PHONY : src/tile_position.i

# target to preprocess a source file
src/tile_position.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/fifteen.dir/build.make CMakeFiles/fifteen.dir/src/tile_position.cpp.i
.PHONY : src/tile_position.cpp.i

src/tile_position.s: src/tile_position.cpp.s
.PHONY : src/tile_position.s

# target to generate assembly for a file
src/tile_position.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/fifteen.dir/build.make CMakeFiles/fifteen.dir/src/tile_position.cpp.s
.PHONY : src/tile_position.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... fifteen"
	@echo "... main.o"
	@echo "... main.i"
	@echo "... main.s"
	@echo "... src/fifteen_application.o"
	@echo "... src/fifteen_application.i"
	@echo "... src/fifteen_application.s"
	@echo "... src/tile_position.o"
	@echo "... src/tile_position.i"
	@echo "... src/tile_position.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

