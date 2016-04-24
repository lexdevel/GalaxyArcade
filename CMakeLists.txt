cmake_minimum_required(VERSION 3.5)
project(GalaxyArcade)

set(SOURCE)
set(LIBS)

if (CMAKE_BUILD_TYPE STREQUAL Debug)
    add_definitions(-DDEBUG)
    add_definitions(-O0)
else()
    add_definitions(-O4)
endif()

add_definitions(-std=c++11)

include_directories(vendor/stb/include)
include_directories(vendor/glfw/include)
set(LIBS ${LIBS} -lglfw3)

if (UNIX AND APPLE)
    add_definitions(-DOS_APPLE)
    link_directories(vendor/glfw/lib/macos)

    set(LIBS ${LIBS} "-framework OpenGL")
    set(LIBS ${LIBS} "-framework Cocoa")
    set(LIBS ${LIBS} "-framework Carbon")
    set(LIBS ${LIBS} "-framework CoreVideo")
    set(LIBS ${LIBS} "-framework IOKit")
endif()

set(SOURCE ${SOURCE} source/util/FileReader.cpp)
set(SOURCE ${SOURCE} source/util/Image.cpp)

set(SOURCE ${SOURCE} source/core/Attachable.cpp)
set(SOURCE ${SOURCE} source/core/GraphicsObject.cpp)

set(SOURCE ${SOURCE} source/math/Vector2f.cpp)
set(SOURCE ${SOURCE} source/math/Matrix.cpp)
set(SOURCE ${SOURCE} source/math/Transformation.cpp)

set(SOURCE ${SOURCE} source/graphics/ShaderProgram.cpp)
set(SOURCE ${SOURCE} source/graphics/Texture2D.cpp)
set(SOURCE ${SOURCE} source/graphics/Buffer.cpp)
set(SOURCE ${SOURCE} source/graphics/GraphicsFactory.cpp)
set(SOURCE ${SOURCE} source/graphics/SpriteRenderer.cpp)

set(SOURCE ${SOURCE} source/main.cpp)
add_executable(${PROJECT_NAME} ${SOURCE})
target_link_libraries(${PROJECT_NAME} ${LIBS})

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})
