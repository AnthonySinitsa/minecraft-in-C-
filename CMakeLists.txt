# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(MinecraftInCpp VERSION 1.0)

# Specify the required C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add an executable
add_executable(MinecraftInCpp src/main.cpp src/Renderer/Renderer.cpp src/Shader/Shader.cpp src/Camera/Camera.cpp)

# Add the include directories for OpenGL, GLEW, and GLFW
# Adjust these paths to where your headers are located
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories("/usr/include/GL")
include_directories("/usr/include/GLEW")
include_directories("src/Renderer")

# Manually specify the libraries for OpenGL, GLEW, and GLFW
# Adjust these paths to where your libraries are located
target_link_libraries(MinecraftInCpp "/usr/lib/x86_64-linux-gnu/libGL.so")
target_link_libraries(MinecraftInCpp "/usr/lib/x86_64-linux-gnu/libGLEW.so")

# Include and link GLFW
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
include_directories(${GLFW_INCLUDE_DIRS})
target_link_libraries(MinecraftInCpp ${GLFW_LIBRARIES})
