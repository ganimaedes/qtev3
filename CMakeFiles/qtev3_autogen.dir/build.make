# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

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
CMAKE_COMMAND = /media/ubuntu-gnome/_home/home2/0Desktop/1090b/4/cmake/bin/cmake

# The command to remove a file.
RM = /media/ubuntu-gnome/_home/home2/0Desktop/1090b/4/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ubuntu-gnome/qtev3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ubuntu-gnome/qtev3

# Utility rule file for qtev3_autogen.

# Include the progress variables for this target.
include CMakeFiles/qtev3_autogen.dir/progress.make

CMakeFiles/qtev3_autogen:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/ubuntu-gnome/qtev3/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC for target qtev3"
	/media/ubuntu-gnome/_home/home2/0Desktop/1090b/4/cmake/bin/cmake -E cmake_autogen /home/ubuntu-gnome/qtev3/CMakeFiles/qtev3_autogen.dir/AutogenInfo.cmake ""

qtev3_autogen: CMakeFiles/qtev3_autogen
qtev3_autogen: CMakeFiles/qtev3_autogen.dir/build.make

.PHONY : qtev3_autogen

# Rule to build all files generated by this target.
CMakeFiles/qtev3_autogen.dir/build: qtev3_autogen

.PHONY : CMakeFiles/qtev3_autogen.dir/build

CMakeFiles/qtev3_autogen.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/qtev3_autogen.dir/cmake_clean.cmake
.PHONY : CMakeFiles/qtev3_autogen.dir/clean

CMakeFiles/qtev3_autogen.dir/depend:
	cd /home/ubuntu-gnome/qtev3 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ubuntu-gnome/qtev3 /home/ubuntu-gnome/qtev3 /home/ubuntu-gnome/qtev3 /home/ubuntu-gnome/qtev3 /home/ubuntu-gnome/qtev3/CMakeFiles/qtev3_autogen.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/qtev3_autogen.dir/depend
