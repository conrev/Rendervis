cmake_minimum_required( VERSION 3.19 )

project(Rendervis)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(external)
add_executable(${PROJECT_NAME} main.cpp)

# copy shaders to build

add_custom_command(
         TARGET ${PROJECT_NAME} POST_BUILD
         COMMAND ${CMAKE_COMMAND} -E copy_directory              
             ${CMAKE_SOURCE_DIR}/shaders $<TARGET_FILE_DIR:${PROJECT_NAME}>/shaders
         COMMENT "Copying shaders" VERBATIM
         )

target_link_libraries(${PROJECT_NAME} glad SDL2::SDL2main SDL2::SDL2-static stb_image glm::glm)

