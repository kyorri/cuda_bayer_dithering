cmake_minimum_required (VERSION 3.8)

project(cuda_bayer_dithering)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(includes)

find_package(CUDA REQUIRED)

file(GLOB HEADER_FILES includes/*.h)
file(GLOB CUDA_SOURCE_FILES src/*.cu)
file(GLOB CPP_SOURCE_FILES src/*.cpp)

cuda_add_executable(exec ${CPP_SOURCE_FILES} ${CUDA_SOURCE_FILES} ${HEADER_FILES})
