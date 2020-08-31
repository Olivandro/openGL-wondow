cmake_minimum_required(VERSION 3.10)
project (GLFW-Window-Test VERSION 1.0)
find_library(GLFW_INCLUDE_LIB libglfw3.a ${CMAKE_SOURCE_DIR}/GLFW/src)
find_library(GLEW_INCLUDE_LIB libGLEW.a ${CMAKE_SOURCE_DIR}/glew-2.1.0/lib)

if(UNIX AND NOT APPLE)
find_package(OpenGL REQUIRED)
endif()


set(CMAKE_C_STANDARD 11)

if(APPLE)
set(CMAKE_C_FLAGS "-framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo")    
endif()

if(UNIX AND NOT APPLE)
SET(CMAKE_C_FLAGS "-lm -pthread")
endif()



 
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build)


file(GLOB SOURCES "main.c")

set(GLFW_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/GLFW/include)
set(GL_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/glew-2.1.0/include)



include_directories(${GLFW_INCLUDE_DIR} ${GL_INCLUDE_DIR})



add_executable(window ${SOURCES})

if(UNIX AND NOT APPLE)
target_link_libraries(window PRIVATE ${CMAKE_DL_LIBS}) 
target_link_libraries(window PRIVATE OpenGL::GL)   
endif()

target_link_libraries(window PRIVATE ${GLFW_INCLUDE_LIB})
target_link_libraries(window PRIVATE ${GLEW_INCLUDE_LIB})
