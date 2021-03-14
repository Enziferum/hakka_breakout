cmake_minimum_required(VERSION 3.12)
project(hakka)

if(MSVC)
    add_definitions(/MP)
endif()

option(BUILD_GLAD "Build glad library" ON)
option(BUILD_STB_IMAGE "Build stb_image library" ON)

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory)
	and run CMake from there. You may need to remove CMakeCache.txt.")
endif()

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

find_package(glfw3 3.3 REQUIRED)
message(STATUS "Found GLFW3 in ${GLFW3_INCLUDE_DIRS}")

set(CMAKE_CXX_STANDARD 14)

if (BUILD_GLAD)
    message(STATUS "+-Add glad module dependency")
    include(cmake/External_glad.cmake)
    message(STATUS "| glad include dirs: ${GLAD_INCLUDE_DIRS}")
    message(STATUS "| glad libraries: ${GLAD_LIBRARIES}")
else()
    message("don't have find package ")
endif ()
include_directories(${GLAD_INCLUDE_DIRS})

if (BUILD_STB_IMAGE)
    message(STATUS "+-Add stb_image module dependency")
    include(cmake/External_stb_image.cmake)
    message(STATUS "| stb_image include dirs: ${STB_IMAGE_INCLUDE_DIRS}")
    message(STATUS "| stb_image libraries: ${STB_IMAGE_LIBRARIES}")
else()
    message("don't have find package ")
endif ()
include_directories(${STB_IMAGE_INCLUDE_DIRS})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/incl)
file(GLOB SRC src/*.cpp)

if(WIN32)
    set(LIBS opengl32)
endif()

add_library(${PROJECT_NAME} ${SRC})

if(BUILD_GLAD)
    add_dependencies(${PROJECT_NAME} glad_ext)
endif()

if(BUILD_STB_IMAGE)
    add_dependencies(${PROJECT_NAME} stb_image_ext)
endif()

set(LIBS ${LIBS} glfw)

target_link_libraries(${PROJECT_NAME} ${LIBS})
target_include_directories(${PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/incl)