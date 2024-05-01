cmake_minimum_required(VERSION 3.8)
project(cuda_bayer_dithering LANGUAGES CXX CUDA)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(CUDA REQUIRED)

file(GLOB_RECURSE CPP_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE CUDA_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cu)

add_executable(${CMAKE_PROJECT_NAME} ${CPP_SOURCE_FILES} ${CUDA_SOURCE_FILES})

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/includes/dithering
    ${CMAKE_CURRENT_SOURCE_DIR}/includes/utils
    ${CMAKE_CURRENT_SOURCE_DIR}/includes/utils/bitmap
)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE ${CUDA_LIBRARIES})
