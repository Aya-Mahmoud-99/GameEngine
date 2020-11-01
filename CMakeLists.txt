cmake_minimum_required(VERSION 3.0.0)
project(TEST_PROGRAM VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_USE_HYBRID_HPG ON CACHE BOOL "" FORCE)
add_subdirectory(vendor/glfw)

set(GLAD_SOURCE vendor/glad/src/gl.c)

set(VENDOR_SOURCES ${GLAD_SOURCE})

include_directories(
        vendor/glfw/include
        vendor/glad/include
)

add_executable(EMPTY_WINDOW main.cpp ${VENDOR_SOURCES})
target_link_libraries(EMPTY_WINDOW glfw)