cmake_minimum_required(VERSION 3.0.0)
project(pamsi_1 VERSION 0.1.0)

include(CTest)
enable_testing()

add_library(pamsi_1 pamsi_1.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
