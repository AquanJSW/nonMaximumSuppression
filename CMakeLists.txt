cmake_minimum_required(VERSION 3.19)
project(nonMaximumSuppression)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV REQUIRED)

if (NOT ${OpenCV_FOUND})
    message(FATAL_ERROR "OpenCV not found.")
endif()

include_directories(${OpenCV_INCLUDE_DIRS})
link_libraries(${OpenCV_LIBS})

add_subdirectory(src)