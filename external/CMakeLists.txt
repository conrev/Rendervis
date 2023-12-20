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
