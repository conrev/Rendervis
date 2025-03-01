cmake_minimum_required( VERSION 3.19 )

project(Rendervis)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(external)
add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} 
PRIVATE
      ${CMAKE_CURRENT_SOURCE_DIR}/main.cc 
      ${CMAKE_CURRENT_SOURCE_DIR}/src/core/Application.cc
      ${CMAKE_CURRENT_SOURCE_DIR}/src/core/Camera.cc
      ${CMAKE_CURRENT_SOURCE_DIR}/src/core/Scene.cc
      ${CMAKE_CURRENT_SOURCE_DIR}/src/renderer/Shader.cc
      ${CMAKE_CURRENT_SOURCE_DIR}/src/renderer/Entity.cc
      ${CMAKE_CURRENT_SOURCE_DIR}/src/renderer/Mesh.cc
)

# copy shaders to build

#add_custom_command(
 #        TARGET ${PROJECT_NAME} POST_BUILD
 #        COMMAND ${CMAKE_COMMAND} -E copy_directory              
 #            ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources
 #        COMMENT "Copying resources" VERBATIM
 #        )

add_custom_target(copy_resource ALL 
			COMMAND ${CMAKE_COMMAND} -E copy_directory              
                ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources
            COMMENT "Copying resources")

target_link_libraries(${PROJECT_NAME} PUBLIC glad stb_image glm::glm imgui tinyobjloader SDL2::SDL2main SDL2::SDL2-static)

target_include_directories(${PROJECT_NAME}
PRIVATE  
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
