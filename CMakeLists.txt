cmake_minimum_required(VERSION 3.5.0)

set(CMAKE_CXX_STANDARD 17)

set(HWINFO_STATIC true)
set(HWINFO_OS OFF)
set(HWINFO_MAINBOARD OFF)
set(HWINFO_CPU ON)
set(HWINFO_DISK OFF)
set(HWINFO_RAM ON)
set(HWINFO_GPU ON)
set(HWINFO_GPU_OPENCL OFF)
set(HWINFO_GPU_BATTERY ON)

project(linyhi LANGUAGES CXX VERSION 0.1.0)

add_executable(${PROJECT_NAME} ./src/main.cpp)
target_link_options(${PROJECT_NAME} PRIVATE -static)

add_subdirectory(./src/thirdparty/base64)
add_subdirectory(./src/thirdparty/hwinfo)

target_link_libraries(${PROJECT_NAME} PRIVATE
	base64 lfreist-hwinfo::hwinfo
)
