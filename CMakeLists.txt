cmake_minimum_required(VERSION 3.20)

project(sagishoval)

set(CMAKE_CXX_STANDARD 14)



set(Header anomaly_detection_util.h, timeseries.h, SimpleAnomalyDetector.h, AnomalyDetector.h, minCircle.h,
        HybridAnomalyDetector.h, commands.h, CLI.h Server.h)

add_executable(sagishoval ${PROJECT_SOURCE_DIR} / MainTrain.cpp anomaly_detection_util.cpp
        timeseries.cpp SimpleAnomalyDetector.cpp minCircle.cpp HybridAnomalyDetector.cpp
        CLI.cpp Server.cpp)

find_package(Threads REQUIRED)

target_link_libraries(sagishoval
        ${CMAKE_THREAD_LIBS_INIT}
        )