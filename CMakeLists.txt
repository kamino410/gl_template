cmake_minimum_required(VERSION 3.1)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(tinyobjloader REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

link_directories(${TINYOBJLOADER_LIBRARY_DIRS})
link_directories("C:/lib/glew-2.1.0/lib/Release/x64")

add_executable(main main.cpp gl_program_wrapper.cpp scene.cpp)

target_include_directories(main PUBLIC ${TINYOBJLOADER_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIR})
target_include_directories(main PUBLIC "C:/lib/glew-2.1.0/include")
target_include_directories(main PUBLIC ${GLM_INCLUDE_DIRS})
target_link_libraries(main tinyobjloader glew32 glew32s glfw opengl32)

# copy glsl files
file(COPY shader/test.vert shader/test.frag model/test.obj DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# you have to copy C:/lib/glew-2.1.0/bin/Release/x64/* to target dir
