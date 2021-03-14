cmake_minimum_required(VERSION 3.12)
project(hakka_game)

set(CMAKE_CXX_STANDARD 14)

include_directories(${CMAKE_SOURCE_DIR}/incl)
file(GLOB SRC src/*.cpp)

#todo it in other way
add_subdirectory(hakka)
link_directories(${CMAKE_BINARY_DIR}/third-party/glad-build/lib)

set(LIBS hakka glad)

add_executable(${PROJECT_NAME} ${SRC})
target_link_libraries(${PROJECT_NAME} ${LIBS})