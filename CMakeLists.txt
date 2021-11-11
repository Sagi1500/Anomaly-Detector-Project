cmake_minimum_required(VERSION 3.20)

project(sagishoval)

set(CMAKE_CXX_STANDARD 14)

set(Header anomaly_detection_util.h, timeseries.h, SimpleAnomalyDetector.h, AnomalyDetector.h)

add_executable(sagishoval ${PROJECT_SOURCE_DIR} / mainTrain.cpp anomaly_detection_util.cpp timeseries.cpp SimpleAnomalyDetector.cpp)
