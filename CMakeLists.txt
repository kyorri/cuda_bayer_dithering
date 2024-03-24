cmake_minimum_required(VERSION 3.0)
project(cuda_bayer_dithering)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(includes)

file(GLOB HEADER_FILES includes/*.h)

file(GLOB SOURCE_FILES src/*.cpp)

add_executable(exec.out ${SOURCE_FILES} ${HEADER_FILES})
