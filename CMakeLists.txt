cmake_minimum_required (VERSION 3.12)
project ("Vally")

set(CMAKE_CXX_STANDARD 20)

set(DEPS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/deps")

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/src)

find_package(OpenGL REQUIRED)

file(GLOB SRC 
	${CMAKE_CURRENT_SOURCE_DIR}/src/Core/*.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Event/*.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/GUI/*.cpp)

add_executable(Vally
	${SRC}
	${CMAKE_CURRENT_SOURCE_DIR}/src/Main.cpp)

add_subdirectory(deps)

target_link_libraries(${PROJECT_NAME} imgui glfw glad glm spdlog::spdlog)