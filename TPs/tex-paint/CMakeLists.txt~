cmake_minimum_required(VERSION 3.10)
project(main)

set(CMAKE_CXX_STANDARD 17)
file(GLOB SOURCE_FILES src/*.cpp)
file(GLOB UTILS_SOURCES common/utils/*.cpp)
file(GLOB IMGUI_SOURCES common/third/imgui/*.cpp)

add_compile_definitions(GLFW_INCLUDE_NONE)

set(SOURCES
  ${SOURCE_FILES}
  ${UTILS_SOURCES}
  ${IMGUI_SOURCES}
  common/third/glad/glad.c
  common/third/stb/stb_image.c
  common/third/imgui/backends/imgui_impl_glfw.cpp
  common/third/imgui/backends/imgui_impl_opengl3.cpp
)

# Create executable
add_executable(main ${SOURCES})

# Add include directories
target_include_directories(main PRIVATE
    common/third/glad
    common/third/imgui
    common/third/stb
    common/utils
)



# Link system libraries
target_link_libraries(main glfw glm dl)
