cmake_minimum_required(VERSION 3.10)
project(CST352Assign2_Robey)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add include directory
include_directories(${PROJECT_SOURCE_DIR}/include)

# Main executable
add_executable(memory_pool_demo src/main.cpp)
