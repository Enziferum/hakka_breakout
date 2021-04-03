cmake_minimum_required(VERSION 3.12)
project(robot2D_game)

set(CMAKE_CXX_STANDARD 14)


option(GAME_MODE "Build game for playing" OFF)

#need for audio only just now
find_package(SFML 2.5 COMPONENTS audio REQUIRED)

#window backend to
find_package(glfw3 3.3 REQUIRED)
find_package(robot2D REQUIRED)
find_package(robot2D_ext REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/incl)
file(GLOB_RECURSE SRC src/*.cpp)


set(LIBS robot2D sfml-audio)
#add_compile_options(-Wall -Wextra -pedantic -Werror)
add_executable(${PROJECT_NAME} ${SRC})
target_link_libraries(${PROJECT_NAME} ${LIBS})

if(GAME_MODE)
    #todo copy resources libs and etc
    if(WIN32)
        #link options to remove console
        add_link_options(-mwindows)
    endif()
endif()