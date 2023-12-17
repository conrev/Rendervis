# Setup GLAD
 
set(GLAD_PATH ${CMAKE_SOURCE_DIR}/external/glad)
add_library(glad ${GLAD_PATH}/src/glad.c)
target_include_directories(glad PUBLIC ${GLAD_PATH}/include/)

# Setup SDL

add_subdirectory(SDL)

