cmake_minimum_required(VERSION 2.8) 

project(cuma) 

set (cuma_VERSION 2.4.3) 
set (cuma_VERSION_MAJOR 2) 
set (cuma_VERSION_MINOR 4) 
set (cuma_VERSION_PATCH 3) 
find_package(CUDA REQUIRED)

find_library (JPEG_LIB  NAMES jpeg PATHS /usr/lib /usr/local/lib /opt/local/lib/)

message(STATUS "${JPEG_LIB}")
set(CPP_SRC_LIST
 src/IO/JpegIO.cpp
)

include_directories(src)
cuda_add_library(cuma SHARED ${CPP_SRC_LIST})
target_link_libraries(cuma ${JPEG_LIB})
include_directories(/usr/include /usr/local/include /opt/local/include)

add_subdirectory(example)





