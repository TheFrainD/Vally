cmake_minimum_required (VERSION 3.12)
project ("Vally")

set(CMAKE_CXX_STANDARD 17)

set(DEPS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/deps")

include_directories(
	"${DEPS_DIR}/spdlog/include"
	${CMAKE_CURRENT_SOURCE_DIR}/src)

file(GLOB SRC 
	${CMAKE_CURRENT_SOURCE_DIR}/src/core/*.cpp)

add_executable(Vally
	${SRC}
	${CMAKE_CURRENT_SOURCE_DIR}/src/Main.cpp)

find_package(OpenGL REQUIRED)

# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(${DEPS_DIR}/glfw EXCLUDE_FROM_ALL)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)

# glad
add_subdirectory(${DEPS_DIR}/glad)
target_link_libraries(${PROJECT_NAME} PRIVATE glad)

# spdlog
add_subdirectory(${DEPS_DIR}/spdlog)
target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog)