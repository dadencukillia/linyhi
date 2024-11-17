cmake_minimum_required(VERSION 3.5.0)

set(CMAKE_CXX_STANDARD 17)

project(linyhi LANGUAGES CXX VERSION 0.1.0)

add_executable(${PROJECT_NAME} ./src/main.cpp)
target_link_options(${PROJECT_NAME} PRIVATE -static)

add_subdirectory(./src/thirdparty/base64)

target_link_libraries(${PROJECT_NAME} PRIVATE
	base64
)
