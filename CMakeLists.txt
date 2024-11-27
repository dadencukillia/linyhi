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

option(FEATURE_INFOPLACEHOLDERS "Add placeholders for system information" ON)
configure_file(./build_flags.in.hpp ./generated/headers/build_flags.hpp)

project(linyhi LANGUAGES CXX VERSION 0.1.3)

add_executable(${PROJECT_NAME} ./src/main.cpp)
target_link_options(${PROJECT_NAME} PRIVATE -static)

add_subdirectory(./src/thirdparty/base64)
add_subdirectory(./src/thirdparty/hwinfo)

target_link_libraries(${PROJECT_NAME} PRIVATE
	base64 lfreist-hwinfo::hwinfo
)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_BINARY_DIR}/generated/headers)

if (CMAKE_BUILD_TYPE STREQUAL "Release")
	target_compile_options(${PROJECT_NAME} PRIVATE -Os -flto -s -Wl,-s -Wl,--gc-sections)
endif()

# TESTS
include(CTest)
enable_testing()

file(GLOB TEST_FILES ./test/*.cpp)
foreach(test ${TEST_FILES})
	get_filename_component(test_suffix ${test} NAME_WLE)

	add_executable(test_${test_suffix} ${test})
	target_include_directories(test_${test_suffix} PRIVATE ./src)

	add_test(test_${test_suffix} test_${test_suffix})
endforeach()
