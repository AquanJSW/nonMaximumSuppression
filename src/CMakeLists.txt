add_subdirectory(test)

add_library(nms_1d nms_1d.cpp)
target_include_directories(nms_1d
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
add_library(nms_1d_fast nms_1d_fast.cpp)
target_include_directories(nms_1d_fast
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
add_library(nms nms.cpp)