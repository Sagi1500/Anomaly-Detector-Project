# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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
CMAKE_COMMAND = /home/sagi/clion-2021.2.3/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/sagi/clion-2021.2.3/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/sagi/CLionProjects/sagishoval

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sagi/CLionProjects/sagishoval/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/sagishoval.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/sagishoval.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/sagishoval.dir/flags.make

CMakeFiles/sagishoval.dir/MainTrain.cpp.o: CMakeFiles/sagishoval.dir/flags.make
CMakeFiles/sagishoval.dir/MainTrain.cpp.o: ../MainTrain.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sagi/CLionProjects/sagishoval/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/sagishoval.dir/MainTrain.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sagishoval.dir/MainTrain.cpp.o -c /home/sagi/CLionProjects/sagishoval/MainTrain.cpp

CMakeFiles/sagishoval.dir/MainTrain.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sagishoval.dir/MainTrain.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sagi/CLionProjects/sagishoval/MainTrain.cpp > CMakeFiles/sagishoval.dir/MainTrain.cpp.i

CMakeFiles/sagishoval.dir/MainTrain.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sagishoval.dir/MainTrain.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sagi/CLionProjects/sagishoval/MainTrain.cpp -o CMakeFiles/sagishoval.dir/MainTrain.cpp.s

CMakeFiles/sagishoval.dir/anomaly_detection_util.cpp.o: CMakeFiles/sagishoval.dir/flags.make
CMakeFiles/sagishoval.dir/anomaly_detection_util.cpp.o: ../anomaly_detection_util.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sagi/CLionProjects/sagishoval/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/sagishoval.dir/anomaly_detection_util.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sagishoval.dir/anomaly_detection_util.cpp.o -c /home/sagi/CLionProjects/sagishoval/anomaly_detection_util.cpp

CMakeFiles/sagishoval.dir/anomaly_detection_util.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sagishoval.dir/anomaly_detection_util.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sagi/CLionProjects/sagishoval/anomaly_detection_util.cpp > CMakeFiles/sagishoval.dir/anomaly_detection_util.cpp.i

CMakeFiles/sagishoval.dir/anomaly_detection_util.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sagishoval.dir/anomaly_detection_util.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sagi/CLionProjects/sagishoval/anomaly_detection_util.cpp -o CMakeFiles/sagishoval.dir/anomaly_detection_util.cpp.s

CMakeFiles/sagishoval.dir/timeseries.cpp.o: CMakeFiles/sagishoval.dir/flags.make
CMakeFiles/sagishoval.dir/timeseries.cpp.o: ../timeseries.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sagi/CLionProjects/sagishoval/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/sagishoval.dir/timeseries.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sagishoval.dir/timeseries.cpp.o -c /home/sagi/CLionProjects/sagishoval/timeseries.cpp

CMakeFiles/sagishoval.dir/timeseries.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sagishoval.dir/timeseries.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sagi/CLionProjects/sagishoval/timeseries.cpp > CMakeFiles/sagishoval.dir/timeseries.cpp.i

CMakeFiles/sagishoval.dir/timeseries.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sagishoval.dir/timeseries.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sagi/CLionProjects/sagishoval/timeseries.cpp -o CMakeFiles/sagishoval.dir/timeseries.cpp.s

CMakeFiles/sagishoval.dir/SimpleAnomalyDetector.cpp.o: CMakeFiles/sagishoval.dir/flags.make
CMakeFiles/sagishoval.dir/SimpleAnomalyDetector.cpp.o: ../SimpleAnomalyDetector.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sagi/CLionProjects/sagishoval/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/sagishoval.dir/SimpleAnomalyDetector.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sagishoval.dir/SimpleAnomalyDetector.cpp.o -c /home/sagi/CLionProjects/sagishoval/SimpleAnomalyDetector.cpp

CMakeFiles/sagishoval.dir/SimpleAnomalyDetector.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sagishoval.dir/SimpleAnomalyDetector.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sagi/CLionProjects/sagishoval/SimpleAnomalyDetector.cpp > CMakeFiles/sagishoval.dir/SimpleAnomalyDetector.cpp.i

CMakeFiles/sagishoval.dir/SimpleAnomalyDetector.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sagishoval.dir/SimpleAnomalyDetector.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sagi/CLionProjects/sagishoval/SimpleAnomalyDetector.cpp -o CMakeFiles/sagishoval.dir/SimpleAnomalyDetector.cpp.s

CMakeFiles/sagishoval.dir/minCircle.cpp.o: CMakeFiles/sagishoval.dir/flags.make
CMakeFiles/sagishoval.dir/minCircle.cpp.o: ../minCircle.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sagi/CLionProjects/sagishoval/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/sagishoval.dir/minCircle.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sagishoval.dir/minCircle.cpp.o -c /home/sagi/CLionProjects/sagishoval/minCircle.cpp

CMakeFiles/sagishoval.dir/minCircle.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sagishoval.dir/minCircle.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sagi/CLionProjects/sagishoval/minCircle.cpp > CMakeFiles/sagishoval.dir/minCircle.cpp.i

CMakeFiles/sagishoval.dir/minCircle.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sagishoval.dir/minCircle.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sagi/CLionProjects/sagishoval/minCircle.cpp -o CMakeFiles/sagishoval.dir/minCircle.cpp.s

CMakeFiles/sagishoval.dir/HybridAnomalyDetector.cpp.o: CMakeFiles/sagishoval.dir/flags.make
CMakeFiles/sagishoval.dir/HybridAnomalyDetector.cpp.o: ../HybridAnomalyDetector.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sagi/CLionProjects/sagishoval/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/sagishoval.dir/HybridAnomalyDetector.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sagishoval.dir/HybridAnomalyDetector.cpp.o -c /home/sagi/CLionProjects/sagishoval/HybridAnomalyDetector.cpp

CMakeFiles/sagishoval.dir/HybridAnomalyDetector.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sagishoval.dir/HybridAnomalyDetector.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sagi/CLionProjects/sagishoval/HybridAnomalyDetector.cpp > CMakeFiles/sagishoval.dir/HybridAnomalyDetector.cpp.i

CMakeFiles/sagishoval.dir/HybridAnomalyDetector.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sagishoval.dir/HybridAnomalyDetector.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sagi/CLionProjects/sagishoval/HybridAnomalyDetector.cpp -o CMakeFiles/sagishoval.dir/HybridAnomalyDetector.cpp.s

CMakeFiles/sagishoval.dir/CLI.cpp.o: CMakeFiles/sagishoval.dir/flags.make
CMakeFiles/sagishoval.dir/CLI.cpp.o: ../CLI.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sagi/CLionProjects/sagishoval/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/sagishoval.dir/CLI.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sagishoval.dir/CLI.cpp.o -c /home/sagi/CLionProjects/sagishoval/CLI.cpp

CMakeFiles/sagishoval.dir/CLI.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sagishoval.dir/CLI.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sagi/CLionProjects/sagishoval/CLI.cpp > CMakeFiles/sagishoval.dir/CLI.cpp.i

CMakeFiles/sagishoval.dir/CLI.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sagishoval.dir/CLI.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sagi/CLionProjects/sagishoval/CLI.cpp -o CMakeFiles/sagishoval.dir/CLI.cpp.s

CMakeFiles/sagishoval.dir/Server.cpp.o: CMakeFiles/sagishoval.dir/flags.make
CMakeFiles/sagishoval.dir/Server.cpp.o: ../Server.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sagi/CLionProjects/sagishoval/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/sagishoval.dir/Server.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sagishoval.dir/Server.cpp.o -c /home/sagi/CLionProjects/sagishoval/Server.cpp

CMakeFiles/sagishoval.dir/Server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sagishoval.dir/Server.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sagi/CLionProjects/sagishoval/Server.cpp > CMakeFiles/sagishoval.dir/Server.cpp.i

CMakeFiles/sagishoval.dir/Server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sagishoval.dir/Server.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sagi/CLionProjects/sagishoval/Server.cpp -o CMakeFiles/sagishoval.dir/Server.cpp.s

# Object files for target sagishoval
sagishoval_OBJECTS = \
"CMakeFiles/sagishoval.dir/MainTrain.cpp.o" \
"CMakeFiles/sagishoval.dir/anomaly_detection_util.cpp.o" \
"CMakeFiles/sagishoval.dir/timeseries.cpp.o" \
"CMakeFiles/sagishoval.dir/SimpleAnomalyDetector.cpp.o" \
"CMakeFiles/sagishoval.dir/minCircle.cpp.o" \
"CMakeFiles/sagishoval.dir/HybridAnomalyDetector.cpp.o" \
"CMakeFiles/sagishoval.dir/CLI.cpp.o" \
"CMakeFiles/sagishoval.dir/Server.cpp.o"

# External object files for target sagishoval
sagishoval_EXTERNAL_OBJECTS =

sagishoval: CMakeFiles/sagishoval.dir/MainTrain.cpp.o
sagishoval: CMakeFiles/sagishoval.dir/anomaly_detection_util.cpp.o
sagishoval: CMakeFiles/sagishoval.dir/timeseries.cpp.o
sagishoval: CMakeFiles/sagishoval.dir/SimpleAnomalyDetector.cpp.o
sagishoval: CMakeFiles/sagishoval.dir/minCircle.cpp.o
sagishoval: CMakeFiles/sagishoval.dir/HybridAnomalyDetector.cpp.o
sagishoval: CMakeFiles/sagishoval.dir/CLI.cpp.o
sagishoval: CMakeFiles/sagishoval.dir/Server.cpp.o
sagishoval: CMakeFiles/sagishoval.dir/build.make
sagishoval: CMakeFiles/sagishoval.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/sagi/CLionProjects/sagishoval/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking CXX executable sagishoval"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sagishoval.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/sagishoval.dir/build: sagishoval
.PHONY : CMakeFiles/sagishoval.dir/build

CMakeFiles/sagishoval.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/sagishoval.dir/cmake_clean.cmake
.PHONY : CMakeFiles/sagishoval.dir/clean

CMakeFiles/sagishoval.dir/depend:
	cd /home/sagi/CLionProjects/sagishoval/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sagi/CLionProjects/sagishoval /home/sagi/CLionProjects/sagishoval /home/sagi/CLionProjects/sagishoval/cmake-build-debug /home/sagi/CLionProjects/sagishoval/cmake-build-debug /home/sagi/CLionProjects/sagishoval/cmake-build-debug/CMakeFiles/sagishoval.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/sagishoval.dir/depend

