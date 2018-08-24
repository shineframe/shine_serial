PROJECT(shine_serial_examples)

CMAKE_MINIMUM_REQUIRED(VERSION 2.4)

INCLUDE_DIRECTORIES(
  ${PROJECT_SOURCE_DIR}
)

IF(NOT WIN32)
 SET(CMAKE_CXX_FLAGS "-std=c++11 -Wall -o3")
ENDIF()

ADD_EXECUTABLE(serial_model examples/serial_model.cpp)


