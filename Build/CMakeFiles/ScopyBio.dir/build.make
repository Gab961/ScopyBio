# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/etudiant/Workspace/ScopyBio

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/etudiant/Workspace/ScopyBio/Build

# Include any dependencies generated for this target.
include CMakeFiles/ScopyBio.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ScopyBio.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ScopyBio.dir/flags.make

CMakeFiles/ScopyBio.dir/main.cpp.o: CMakeFiles/ScopyBio.dir/flags.make
CMakeFiles/ScopyBio.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/etudiant/Workspace/ScopyBio/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ScopyBio.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ScopyBio.dir/main.cpp.o -c /home/etudiant/Workspace/ScopyBio/main.cpp

CMakeFiles/ScopyBio.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ScopyBio.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/etudiant/Workspace/ScopyBio/main.cpp > CMakeFiles/ScopyBio.dir/main.cpp.i

CMakeFiles/ScopyBio.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ScopyBio.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/etudiant/Workspace/ScopyBio/main.cpp -o CMakeFiles/ScopyBio.dir/main.cpp.s

CMakeFiles/ScopyBio.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/ScopyBio.dir/main.cpp.o.requires

CMakeFiles/ScopyBio.dir/main.cpp.o.provides: CMakeFiles/ScopyBio.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/ScopyBio.dir/build.make CMakeFiles/ScopyBio.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/ScopyBio.dir/main.cpp.o.provides

CMakeFiles/ScopyBio.dir/main.cpp.o.provides.build: CMakeFiles/ScopyBio.dir/main.cpp.o


CMakeFiles/ScopyBio.dir/ScopyBio_automoc.cpp.o: CMakeFiles/ScopyBio.dir/flags.make
CMakeFiles/ScopyBio.dir/ScopyBio_automoc.cpp.o: ScopyBio_automoc.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/etudiant/Workspace/ScopyBio/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/ScopyBio.dir/ScopyBio_automoc.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ScopyBio.dir/ScopyBio_automoc.cpp.o -c /home/etudiant/Workspace/ScopyBio/Build/ScopyBio_automoc.cpp

CMakeFiles/ScopyBio.dir/ScopyBio_automoc.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ScopyBio.dir/ScopyBio_automoc.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/etudiant/Workspace/ScopyBio/Build/ScopyBio_automoc.cpp > CMakeFiles/ScopyBio.dir/ScopyBio_automoc.cpp.i

CMakeFiles/ScopyBio.dir/ScopyBio_automoc.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ScopyBio.dir/ScopyBio_automoc.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/etudiant/Workspace/ScopyBio/Build/ScopyBio_automoc.cpp -o CMakeFiles/ScopyBio.dir/ScopyBio_automoc.cpp.s

CMakeFiles/ScopyBio.dir/ScopyBio_automoc.cpp.o.requires:

.PHONY : CMakeFiles/ScopyBio.dir/ScopyBio_automoc.cpp.o.requires

CMakeFiles/ScopyBio.dir/ScopyBio_automoc.cpp.o.provides: CMakeFiles/ScopyBio.dir/ScopyBio_automoc.cpp.o.requires
	$(MAKE) -f CMakeFiles/ScopyBio.dir/build.make CMakeFiles/ScopyBio.dir/ScopyBio_automoc.cpp.o.provides.build
.PHONY : CMakeFiles/ScopyBio.dir/ScopyBio_automoc.cpp.o.provides

CMakeFiles/ScopyBio.dir/ScopyBio_automoc.cpp.o.provides.build: CMakeFiles/ScopyBio.dir/ScopyBio_automoc.cpp.o


# Object files for target ScopyBio
ScopyBio_OBJECTS = \
"CMakeFiles/ScopyBio.dir/main.cpp.o" \
"CMakeFiles/ScopyBio.dir/ScopyBio_automoc.cpp.o"

# External object files for target ScopyBio
ScopyBio_EXTERNAL_OBJECTS =

bin/ScopyBio: CMakeFiles/ScopyBio.dir/main.cpp.o
bin/ScopyBio: CMakeFiles/ScopyBio.dir/ScopyBio_automoc.cpp.o
bin/ScopyBio: CMakeFiles/ScopyBio.dir/build.make
bin/ScopyBio: /home/etudiant/anaconda3/lib/libtiff.so
bin/ScopyBio: /usr/lib/x86_64-linux-gnu/libSM.so
bin/ScopyBio: /usr/lib/x86_64-linux-gnu/libICE.so
bin/ScopyBio: /usr/lib/x86_64-linux-gnu/libX11.so
bin/ScopyBio: /usr/lib/x86_64-linux-gnu/libXext.so
bin/ScopyBio: /usr/lib/x86_64-linux-gnu/libQt5Widgets.so.5.5.1
bin/ScopyBio: lib/libControler.a
bin/ScopyBio: lib/libView.a
bin/ScopyBio: lib/libModel.a
bin/ScopyBio: /usr/lib/x86_64-linux-gnu/libQt5Gui.so.5.5.1
bin/ScopyBio: /usr/lib/x86_64-linux-gnu/libQt5Core.so.5.5.1
bin/ScopyBio: CMakeFiles/ScopyBio.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/etudiant/Workspace/ScopyBio/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable bin/ScopyBio"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ScopyBio.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ScopyBio.dir/build: bin/ScopyBio

.PHONY : CMakeFiles/ScopyBio.dir/build

CMakeFiles/ScopyBio.dir/requires: CMakeFiles/ScopyBio.dir/main.cpp.o.requires
CMakeFiles/ScopyBio.dir/requires: CMakeFiles/ScopyBio.dir/ScopyBio_automoc.cpp.o.requires

.PHONY : CMakeFiles/ScopyBio.dir/requires

CMakeFiles/ScopyBio.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ScopyBio.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ScopyBio.dir/clean

CMakeFiles/ScopyBio.dir/depend:
	cd /home/etudiant/Workspace/ScopyBio/Build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/etudiant/Workspace/ScopyBio /home/etudiant/Workspace/ScopyBio /home/etudiant/Workspace/ScopyBio/Build /home/etudiant/Workspace/ScopyBio/Build /home/etudiant/Workspace/ScopyBio/Build/CMakeFiles/ScopyBio.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ScopyBio.dir/depend

