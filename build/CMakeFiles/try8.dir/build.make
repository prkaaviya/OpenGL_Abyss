# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.31

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
CMAKE_COMMAND = /opt/homebrew/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/prkaaviya/CLionProjects/try8

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/prkaaviya/CLionProjects/try8/build

# Include any dependencies generated for this target.
include CMakeFiles/try8.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/try8.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/try8.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/try8.dir/flags.make

CMakeFiles/try8.dir/codegen:
.PHONY : CMakeFiles/try8.dir/codegen

CMakeFiles/try8.dir/main.cpp.o: CMakeFiles/try8.dir/flags.make
CMakeFiles/try8.dir/main.cpp.o: /Users/prkaaviya/CLionProjects/try8/main.cpp
CMakeFiles/try8.dir/main.cpp.o: CMakeFiles/try8.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/prkaaviya/CLionProjects/try8/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/try8.dir/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/try8.dir/main.cpp.o -MF CMakeFiles/try8.dir/main.cpp.o.d -o CMakeFiles/try8.dir/main.cpp.o -c /Users/prkaaviya/CLionProjects/try8/main.cpp

CMakeFiles/try8.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/try8.dir/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/prkaaviya/CLionProjects/try8/main.cpp > CMakeFiles/try8.dir/main.cpp.i

CMakeFiles/try8.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/try8.dir/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/prkaaviya/CLionProjects/try8/main.cpp -o CMakeFiles/try8.dir/main.cpp.s

CMakeFiles/try8.dir/Mesh.cpp.o: CMakeFiles/try8.dir/flags.make
CMakeFiles/try8.dir/Mesh.cpp.o: /Users/prkaaviya/CLionProjects/try8/Mesh.cpp
CMakeFiles/try8.dir/Mesh.cpp.o: CMakeFiles/try8.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/prkaaviya/CLionProjects/try8/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/try8.dir/Mesh.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/try8.dir/Mesh.cpp.o -MF CMakeFiles/try8.dir/Mesh.cpp.o.d -o CMakeFiles/try8.dir/Mesh.cpp.o -c /Users/prkaaviya/CLionProjects/try8/Mesh.cpp

CMakeFiles/try8.dir/Mesh.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/try8.dir/Mesh.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/prkaaviya/CLionProjects/try8/Mesh.cpp > CMakeFiles/try8.dir/Mesh.cpp.i

CMakeFiles/try8.dir/Mesh.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/try8.dir/Mesh.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/prkaaviya/CLionProjects/try8/Mesh.cpp -o CMakeFiles/try8.dir/Mesh.cpp.s

CMakeFiles/try8.dir/Window.cpp.o: CMakeFiles/try8.dir/flags.make
CMakeFiles/try8.dir/Window.cpp.o: /Users/prkaaviya/CLionProjects/try8/Window.cpp
CMakeFiles/try8.dir/Window.cpp.o: CMakeFiles/try8.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/prkaaviya/CLionProjects/try8/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/try8.dir/Window.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/try8.dir/Window.cpp.o -MF CMakeFiles/try8.dir/Window.cpp.o.d -o CMakeFiles/try8.dir/Window.cpp.o -c /Users/prkaaviya/CLionProjects/try8/Window.cpp

CMakeFiles/try8.dir/Window.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/try8.dir/Window.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/prkaaviya/CLionProjects/try8/Window.cpp > CMakeFiles/try8.dir/Window.cpp.i

CMakeFiles/try8.dir/Window.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/try8.dir/Window.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/prkaaviya/CLionProjects/try8/Window.cpp -o CMakeFiles/try8.dir/Window.cpp.s

CMakeFiles/try8.dir/Shader.cpp.o: CMakeFiles/try8.dir/flags.make
CMakeFiles/try8.dir/Shader.cpp.o: /Users/prkaaviya/CLionProjects/try8/Shader.cpp
CMakeFiles/try8.dir/Shader.cpp.o: CMakeFiles/try8.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/prkaaviya/CLionProjects/try8/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/try8.dir/Shader.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/try8.dir/Shader.cpp.o -MF CMakeFiles/try8.dir/Shader.cpp.o.d -o CMakeFiles/try8.dir/Shader.cpp.o -c /Users/prkaaviya/CLionProjects/try8/Shader.cpp

CMakeFiles/try8.dir/Shader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/try8.dir/Shader.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/prkaaviya/CLionProjects/try8/Shader.cpp > CMakeFiles/try8.dir/Shader.cpp.i

CMakeFiles/try8.dir/Shader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/try8.dir/Shader.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/prkaaviya/CLionProjects/try8/Shader.cpp -o CMakeFiles/try8.dir/Shader.cpp.s

# Object files for target try8
try8_OBJECTS = \
"CMakeFiles/try8.dir/main.cpp.o" \
"CMakeFiles/try8.dir/Mesh.cpp.o" \
"CMakeFiles/try8.dir/Window.cpp.o" \
"CMakeFiles/try8.dir/Shader.cpp.o"

# External object files for target try8
try8_EXTERNAL_OBJECTS =

try8: CMakeFiles/try8.dir/main.cpp.o
try8: CMakeFiles/try8.dir/Mesh.cpp.o
try8: CMakeFiles/try8.dir/Window.cpp.o
try8: CMakeFiles/try8.dir/Shader.cpp.o
try8: CMakeFiles/try8.dir/build.make
try8: libglad.a
try8: /Users/prkaaviya/CLionProjects/try8/Dependencies/lib/GL/libGLEW.dylib
try8: /opt/homebrew/lib/libassimp.5.4.3.dylib
try8: /opt/homebrew/lib/libglfw.3.4.dylib
try8: /opt/homebrew/lib/libglm.dylib
try8: /Library/Developer/CommandLineTools/SDKs/MacOSX15.sdk/usr/lib/libz.tbd
try8: CMakeFiles/try8.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/prkaaviya/CLionProjects/try8/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable try8"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/try8.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/try8.dir/build: try8
.PHONY : CMakeFiles/try8.dir/build

CMakeFiles/try8.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/try8.dir/cmake_clean.cmake
.PHONY : CMakeFiles/try8.dir/clean

CMakeFiles/try8.dir/depend:
	cd /Users/prkaaviya/CLionProjects/try8/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/prkaaviya/CLionProjects/try8 /Users/prkaaviya/CLionProjects/try8 /Users/prkaaviya/CLionProjects/try8/build /Users/prkaaviya/CLionProjects/try8/build /Users/prkaaviya/CLionProjects/try8/build/CMakeFiles/try8.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/try8.dir/depend
