# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

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
CMAKE_SOURCE_DIR = /home/henry/yo

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/henry/yo/build

# Utility rule file for curl-generate-curl-config.1.

# Include any custom commands dependencies for this target.
include _deps/curl-build/docs/CMakeFiles/curl-generate-curl-config.1.dir/compiler_depend.make

# Include the progress variables for this target.
include _deps/curl-build/docs/CMakeFiles/curl-generate-curl-config.1.dir/progress.make

_deps/curl-build/docs/CMakeFiles/curl-generate-curl-config.1: _deps/curl-build/docs/curl-config.1

_deps/curl-build/docs/curl-config.1: _deps/curl-src/docs/curl-config.md
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/henry/yo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating curl-config.1"
	cd /home/henry/yo/build/_deps/curl-src/docs && /sbin/perl /home/henry/yo/build/_deps/curl-src/scripts/cd2nroff curl-config.md > /home/henry/yo/build/_deps/curl-build/docs/curl-config.1

curl-generate-curl-config.1: _deps/curl-build/docs/CMakeFiles/curl-generate-curl-config.1
curl-generate-curl-config.1: _deps/curl-build/docs/curl-config.1
curl-generate-curl-config.1: _deps/curl-build/docs/CMakeFiles/curl-generate-curl-config.1.dir/build.make
.PHONY : curl-generate-curl-config.1

# Rule to build all files generated by this target.
_deps/curl-build/docs/CMakeFiles/curl-generate-curl-config.1.dir/build: curl-generate-curl-config.1
.PHONY : _deps/curl-build/docs/CMakeFiles/curl-generate-curl-config.1.dir/build

_deps/curl-build/docs/CMakeFiles/curl-generate-curl-config.1.dir/clean:
	cd /home/henry/yo/build/_deps/curl-build/docs && $(CMAKE_COMMAND) -P CMakeFiles/curl-generate-curl-config.1.dir/cmake_clean.cmake
.PHONY : _deps/curl-build/docs/CMakeFiles/curl-generate-curl-config.1.dir/clean

_deps/curl-build/docs/CMakeFiles/curl-generate-curl-config.1.dir/depend:
	cd /home/henry/yo/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/henry/yo /home/henry/yo/build/_deps/curl-src/docs /home/henry/yo/build /home/henry/yo/build/_deps/curl-build/docs /home/henry/yo/build/_deps/curl-build/docs/CMakeFiles/curl-generate-curl-config.1.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : _deps/curl-build/docs/CMakeFiles/curl-generate-curl-config.1.dir/depend

