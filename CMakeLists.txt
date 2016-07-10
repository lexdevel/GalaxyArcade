cmake_minimum_required(VERSION 3.0)
project(GalaxyArcade)

set(SOURCE)
set(LIBS)

if (CMAKE_BUILD_TYPE STREQUAL Debug)
    add_definitions(-DDEBUG)
    add_definitions(-O0)
else()
    add_definitions(-O3)
    add_definitions(-D__NO_INLINE__) # Fix "_hypot" issue with math.h/cmath and -O3 optimization level
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

if (WIN32 AND MINGW)
    add_definitions(-DOS_WIN32)
    link_directories(vendor/glfw/lib/win32)

    include_directories(vendor/glxw/include)
    link_directories(vendor/glxw/lib/win32)

    set(LIBS ${LIBS} glxw)
    set(LIBS ${LIBS} opengl32)
    set(LIBS ${LIBS} glu32)
    set(LIBS ${LIBS} gdi32)
endif()

set(SOURCE ${SOURCE} source/util/GameTime.cpp)
set(SOURCE ${SOURCE} source/util/Image.cpp)

set(SOURCE ${SOURCE} source/math/Vector2f.cpp)
set(SOURCE ${SOURCE} source/math/Matrix.cpp)
set(SOURCE ${SOURCE} source/math/Transformation.cpp)
set(SOURCE ${SOURCE} source/math/Rect.cpp)

set(SOURCE ${SOURCE} source/platform/core/Attachable.cpp)
set(SOURCE ${SOURCE} source/platform/core/PlatformEntity.cpp)
set(SOURCE ${SOURCE} source/platform/Buffer.cpp)
set(SOURCE ${SOURCE} source/platform/VertexBuffer.cpp)
set(SOURCE ${SOURCE} source/platform/ElementArray.cpp)
set(SOURCE ${SOURCE} source/platform/Texture2D.cpp)
set(SOURCE ${SOURCE} source/platform/ShaderProgram.cpp)

set(SOURCE ${SOURCE} source/core/Renderable.cpp)
set(SOURCE ${SOURCE} source/core/Renderer.cpp)

set(SOURCE ${SOURCE} source/main.cpp)

add_executable(${PROJECT_NAME} ${SOURCE})
target_link_libraries(${PROJECT_NAME} ${LIBS})

file(COPY assets/ DESTINATION ${CMAKE_BINARY_DIR}/assets)
