cmake_minimum_required(VERSION 3.22.1)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ./bin)

project(project3)

set(OpenGL_GL_PREFERENCE LEGACY)

find_package(assimp REQUIRED)
include_directories(${assimp_INCLUDE_DIR})
find_package(OpenGL REQUIRED)
find_package(glfw3  REQUIRED)
find_package(GLEW   REQUIRED)
find_package(glm    REQUIRED)

set(IMGUI_PATH ${CMAKE_SOURCE_DIR}/submodules/imgui-master)

message("GL include dir: ${OPENGL_INCLUDE_DIR}")
message("GL link libraries: ${OPENGL_gl_LIBRARY}")

add_custom_target(copy-files ALL
COMMAND ${CMAKE_COMMAND} -E copy_directory
${CMAKE_SOURCE_DIR}/src/resources
${CMAKE_BINARY_DIR}/bin/resources
)


file(GLOB_RECURSE SOURCES ./src/*.cpp)

add_executable(out ${SOURCES})


target_link_libraries(out ${OPENGL_gl_LIBRARY} GLEW glfw assimp)