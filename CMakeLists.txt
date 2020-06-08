cmake_minimum_required(VERSION 3.10)
project (GLFW-Window-Test VERSION 1.0)
find_library(GLFW_INCLUDE_LIB libglfw3.a ${CMAKE_SOURCE_DIR}/GLFW/lib-macos)
find_library(GLEW_INCLUDE_LIB libGLEW.a ${CMAKE_SOURCE_DIR}/GL/lib)
find_library(GLUS_INCLUDE_LIB libGLUS.a ${CMAKE_SOURCE_DIR}/GL/lib)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "-framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo")
 
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build)


file(GLOB SOURCES "*.c")

set(GLFW_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/GLFW/include)
set(GL_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/GL/include)



include_directories(${GLFW_INCLUDE_DIR} ${GL_INCLUDE_DIR})



add_executable(window ${SOURCES})
target_link_libraries(window PRIVATE ${GLFW_INCLUDE_LIB})
target_link_libraries(window PRIVATE ${GLEW_INCLUDE_LIB})
target_link_libraries(window PRIVATE ${GLUS_INCLUDE_LIB})
