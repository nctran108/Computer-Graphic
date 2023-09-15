cmake_minimum_required(VERSION 3.5)
PROJECT(project1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)

include_directories($ENV{GLEW_INCLUDE_DIRS})
include_directories($ENV{GLFW_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

link_directories(${OpenGL_LIBRARY_DIRS})
link_directories($ENV{GLEW_LIBRARY_DIRS})
link_directories($ENV{GLFW_LIBRARY_DIRS})

FILE(GLOB_RECURSE SRC_FILES src/*.c*)

add_executable(${PROJECT_NAME} ${SRC_FILES})

target_link_libraries(${PROJECT_NAME}
                    opengl32
                    glew32
                    glfw3dll
)