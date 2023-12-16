cmake_minimum_required( VERSION 3.19 )

project(Rendervis)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(external)
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} glad SDL2::SDL2main SDL2::SDL2-static )
