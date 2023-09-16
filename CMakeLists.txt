cmake_minimum_required(VERSION 3.10)

project(ROBDD_Generation)

set(CMAKE_CXX_STANDARD 17)

set(APP_NAME robdd)
set(SRC_DIR src)
set(INCLUDE_DIR include())

add_executable(${APP_NAME} ${SRC_DIR}/BDDManager.cpp
  ${SRC_DIR}/PLAParser.cpp
  ${SRC_DIR}/main.cpp)
target_include_directories(${APP_NAME} PRIVATE ${INCLUDE_DIR})