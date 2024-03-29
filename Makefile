# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/joao/IC/Common Blocks/NFC - MRSH-SD - main folder/NCF_MRSH-SD - to commit"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/joao/IC/Common Blocks/NFC - MRSH-SD - main folder/NCF_MRSH-SD - to commit"

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/usr/bin/cmake-gui -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start "/home/joao/IC/Common Blocks/NFC - MRSH-SD - main folder/NCF_MRSH-SD - to commit/CMakeFiles" "/home/joao/IC/Common Blocks/NFC - MRSH-SD - main folder/NCF_MRSH-SD - to commit/CMakeFiles/progress.marks"
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start "/home/joao/IC/Common Blocks/NFC - MRSH-SD - main folder/NCF_MRSH-SD - to commit/CMakeFiles" 0
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
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named mrsh_sd

# Build rule for target.
mrsh_sd: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 mrsh_sd
.PHONY : mrsh_sd

# fast build rule for target.
mrsh_sd/fast:
	$(MAKE) -f CMakeFiles/mrsh_sd.dir/build.make CMakeFiles/mrsh_sd.dir/build
.PHONY : mrsh_sd/fast

src/bloomfilter.o: src/bloomfilter.cpp.o

.PHONY : src/bloomfilter.o

# target to build an object file
src/bloomfilter.cpp.o:
	$(MAKE) -f CMakeFiles/mrsh_sd.dir/build.make CMakeFiles/mrsh_sd.dir/src/bloomfilter.cpp.o
.PHONY : src/bloomfilter.cpp.o

src/bloomfilter.i: src/bloomfilter.cpp.i

.PHONY : src/bloomfilter.i

# target to preprocess a source file
src/bloomfilter.cpp.i:
	$(MAKE) -f CMakeFiles/mrsh_sd.dir/build.make CMakeFiles/mrsh_sd.dir/src/bloomfilter.cpp.i
.PHONY : src/bloomfilter.cpp.i

src/bloomfilter.s: src/bloomfilter.cpp.s

.PHONY : src/bloomfilter.s

# target to generate assembly for a file
src/bloomfilter.cpp.s:
	$(MAKE) -f CMakeFiles/mrsh_sd.dir/build.make CMakeFiles/mrsh_sd.dir/src/bloomfilter.cpp.s
.PHONY : src/bloomfilter.cpp.s

src/hashing.o: src/hashing.cpp.o

.PHONY : src/hashing.o

# target to build an object file
src/hashing.cpp.o:
	$(MAKE) -f CMakeFiles/mrsh_sd.dir/build.make CMakeFiles/mrsh_sd.dir/src/hashing.cpp.o
.PHONY : src/hashing.cpp.o

src/hashing.i: src/hashing.cpp.i

.PHONY : src/hashing.i

# target to preprocess a source file
src/hashing.cpp.i:
	$(MAKE) -f CMakeFiles/mrsh_sd.dir/build.make CMakeFiles/mrsh_sd.dir/src/hashing.cpp.i
.PHONY : src/hashing.cpp.i

src/hashing.s: src/hashing.cpp.s

.PHONY : src/hashing.s

# target to generate assembly for a file
src/hashing.cpp.s:
	$(MAKE) -f CMakeFiles/mrsh_sd.dir/build.make CMakeFiles/mrsh_sd.dir/src/hashing.cpp.s
.PHONY : src/hashing.cpp.s

src/helper.o: src/helper.cpp.o

.PHONY : src/helper.o

# target to build an object file
src/helper.cpp.o:
	$(MAKE) -f CMakeFiles/mrsh_sd.dir/build.make CMakeFiles/mrsh_sd.dir/src/helper.cpp.o
.PHONY : src/helper.cpp.o

src/helper.i: src/helper.cpp.i

.PHONY : src/helper.i

# target to preprocess a source file
src/helper.cpp.i:
	$(MAKE) -f CMakeFiles/mrsh_sd.dir/build.make CMakeFiles/mrsh_sd.dir/src/helper.cpp.i
.PHONY : src/helper.cpp.i

src/helper.s: src/helper.cpp.s

.PHONY : src/helper.s

# target to generate assembly for a file
src/helper.cpp.s:
	$(MAKE) -f CMakeFiles/mrsh_sd.dir/build.make CMakeFiles/mrsh_sd.dir/src/helper.cpp.s
.PHONY : src/helper.cpp.s

src/main.o: src/main.cpp.o

.PHONY : src/main.o

# target to build an object file
src/main.cpp.o:
	$(MAKE) -f CMakeFiles/mrsh_sd.dir/build.make CMakeFiles/mrsh_sd.dir/src/main.cpp.o
.PHONY : src/main.cpp.o

src/main.i: src/main.cpp.i

.PHONY : src/main.i

# target to preprocess a source file
src/main.cpp.i:
	$(MAKE) -f CMakeFiles/mrsh_sd.dir/build.make CMakeFiles/mrsh_sd.dir/src/main.cpp.i
.PHONY : src/main.cpp.i

src/main.s: src/main.cpp.s

.PHONY : src/main.s

# target to generate assembly for a file
src/main.cpp.s:
	$(MAKE) -f CMakeFiles/mrsh_sd.dir/build.make CMakeFiles/mrsh_sd.dir/src/main.cpp.s
.PHONY : src/main.cpp.s

src/sdhash.o: src/sdhash.cpp.o

.PHONY : src/sdhash.o

# target to build an object file
src/sdhash.cpp.o:
	$(MAKE) -f CMakeFiles/mrsh_sd.dir/build.make CMakeFiles/mrsh_sd.dir/src/sdhash.cpp.o
.PHONY : src/sdhash.cpp.o

src/sdhash.i: src/sdhash.cpp.i

.PHONY : src/sdhash.i

# target to preprocess a source file
src/sdhash.cpp.i:
	$(MAKE) -f CMakeFiles/mrsh_sd.dir/build.make CMakeFiles/mrsh_sd.dir/src/sdhash.cpp.i
.PHONY : src/sdhash.cpp.i

src/sdhash.s: src/sdhash.cpp.s

.PHONY : src/sdhash.s

# target to generate assembly for a file
src/sdhash.cpp.s:
	$(MAKE) -f CMakeFiles/mrsh_sd.dir/build.make CMakeFiles/mrsh_sd.dir/src/sdhash.cpp.s
.PHONY : src/sdhash.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... edit_cache"
	@echo "... mrsh_sd"
	@echo "... src/bloomfilter.o"
	@echo "... src/bloomfilter.i"
	@echo "... src/bloomfilter.s"
	@echo "... src/hashing.o"
	@echo "... src/hashing.i"
	@echo "... src/hashing.s"
	@echo "... src/helper.o"
	@echo "... src/helper.i"
	@echo "... src/helper.s"
	@echo "... src/main.o"
	@echo "... src/main.i"
	@echo "... src/main.s"
	@echo "... src/sdhash.o"
	@echo "... src/sdhash.i"
	@echo "... src/sdhash.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

