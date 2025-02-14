# Setup GLAD
 
set(GLAD_PATH ${CMAKE_SOURCE_DIR}/external/glad)
add_library(glad ${GLAD_PATH}/src/glad.c)
target_include_directories(glad PUBLIC ${GLAD_PATH}/include/)

# Setup SDL

add_subdirectory(SDL)

# Setup stb_image

set(STB_PATH ${CMAKE_SOURCE_DIR}/external/stb_image)
add_library(stb_image ${STB_PATH}/stb_image.cpp)
target_include_directories(stb_image PUBLIC ${STB_PATH}/include/)

# setup GLM

add_subdirectory(glm)

# setup IMGUI

set(IMGUI_PATH ${CMAKE_SOURCE_DIR}/external/imgui)

add_library(imgui 
    ${IMGUI_PATH}/imgui.cpp
    ${IMGUI_PATH}/imgui_demo.cpp
    ${IMGUI_PATH}/imgui_tables.cpp
    ${IMGUI_PATH}/imgui_draw.cpp
    ${IMGUI_PATH}/imgui_widgets.cpp
    ${IMGUI_PATH}/backends/imgui_impl_sdl2.cpp
    ${IMGUI_PATH}/backends/imgui_impl_opengl3.cpp
    )

target_include_directories(imgui PUBLIC ${IMGUI_PATH} ${IMGUI_PATH}/backends/)
target_link_libraries(imgui PUBLIC SDL2::SDL2)