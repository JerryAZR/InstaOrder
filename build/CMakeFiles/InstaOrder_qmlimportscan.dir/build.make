# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.27.2/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.27.2/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/tacitradiance/Documents/InstaOrder

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/tacitradiance/Documents/InstaOrder/build

# Utility rule file for InstaOrder_qmlimportscan.

# Include any custom commands dependencies for this target.
include CMakeFiles/InstaOrder_qmlimportscan.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/InstaOrder_qmlimportscan.dir/progress.make

CMakeFiles/InstaOrder_qmlimportscan: .qt_plugins/Qt6_QmlPlugins_Imports_InstaOrder.cmake

.qt_plugins/Qt6_QmlPlugins_Imports_InstaOrder.cmake: /Users/tacitradiance/Qt/6.5.2/macos/libexec/qmlimportscanner
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/Users/tacitradiance/Documents/InstaOrder/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Running qmlimportscanner for InstaOrder"
	cd /Users/tacitradiance/Documents/InstaOrder && /Users/tacitradiance/Qt/6.5.2/macos/libexec/qmlimportscanner @/Users/tacitradiance/Documents/InstaOrder/build/.qt_plugins/Qt6_QmlPlugins_Imports_InstaOrder.rsp

InstaOrder_qmlimportscan: .qt_plugins/Qt6_QmlPlugins_Imports_InstaOrder.cmake
InstaOrder_qmlimportscan: CMakeFiles/InstaOrder_qmlimportscan
InstaOrder_qmlimportscan: CMakeFiles/InstaOrder_qmlimportscan.dir/build.make
.PHONY : InstaOrder_qmlimportscan

# Rule to build all files generated by this target.
CMakeFiles/InstaOrder_qmlimportscan.dir/build: InstaOrder_qmlimportscan
.PHONY : CMakeFiles/InstaOrder_qmlimportscan.dir/build

CMakeFiles/InstaOrder_qmlimportscan.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/InstaOrder_qmlimportscan.dir/cmake_clean.cmake
.PHONY : CMakeFiles/InstaOrder_qmlimportscan.dir/clean

CMakeFiles/InstaOrder_qmlimportscan.dir/depend:
	cd /Users/tacitradiance/Documents/InstaOrder/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/tacitradiance/Documents/InstaOrder /Users/tacitradiance/Documents/InstaOrder /Users/tacitradiance/Documents/InstaOrder/build /Users/tacitradiance/Documents/InstaOrder/build /Users/tacitradiance/Documents/InstaOrder/build/CMakeFiles/InstaOrder_qmlimportscan.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/InstaOrder_qmlimportscan.dir/depend

