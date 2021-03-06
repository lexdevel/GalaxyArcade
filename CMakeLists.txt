cmake_minimum_required(VERSION 3.0)
project(GalaxyArcade)

set(SOURCE)
set(LIBS)

add_definitions(-std=c++11)
add_definitions(-D_USE_MATH_DEFINES)    # Use math definitions (M_PI, etc...)
add_definitions(-Wall -Wextra -Werror)  # Display all warnings, mark warnings as error

if (CMAKE_BUILD_TYPE STREQUAL Debug)
    add_definitions(-DDEBUG)
    add_definitions(-O0)
else()
    add_definitions(-O3)
    add_definitions(-D__NO_INLINE__) # Fix "_hypot" issue with math.h/cmath and -O3 optimization level
endif()

add_definitions(-DSTB_IMAGE_IMPLEMENTATION) # Define for STB Image

include_directories(vendor/includes)
set(LIBS ${LIBS} -lglfw3)

if (UNIX AND APPLE)
    add_definitions(-DOS_APPLE)
    link_directories(vendor/libs/macos)

    set(LIBS ${LIBS} "-framework OpenGL")
    set(LIBS ${LIBS} "-framework Cocoa")
    set(LIBS ${LIBS} "-framework Carbon")
    set(LIBS ${LIBS} "-framework CoreVideo")
    set(LIBS ${LIBS} "-framework IOKit")
endif()

if (WIN32 AND MINGW)
    add_definitions(-DOS_WIN32)
    link_directories(vendor/libs/win32)

    set(LIBS ${LIBS} glxw)
    set(LIBS ${LIBS} opengl32)
    set(LIBS ${LIBS} glu32)
    set(LIBS ${LIBS} gdi32)
endif()

set(SOURCE ${SOURCE} source/math/Vec2.cpp)
set(SOURCE ${SOURCE} source/math/Matrix.cpp)
set(SOURCE ${SOURCE} source/math/Transformation.cpp)

set(SOURCE ${SOURCE} source/platform/core/PlatformEntity.cpp)
set(SOURCE ${SOURCE} source/platform/Buffer.cpp)
set(SOURCE ${SOURCE} source/platform/VertexBuffer.cpp)
set(SOURCE ${SOURCE} source/platform/ElementArray.cpp)
set(SOURCE ${SOURCE} source/platform/Texture2D.cpp)
set(SOURCE ${SOURCE} source/platform/ShaderProgram.cpp)

set(SOURCE ${SOURCE} source/util/GameTime.cpp)
set(SOURCE ${SOURCE} source/util/Resource.cpp)
set(SOURCE ${SOURCE} source/util/Bitmap.cpp)

set(SOURCE ${SOURCE} source/core/Renderable.cpp)
set(SOURCE ${SOURCE} source/core/Renderer.cpp)

set(SOURCE ${SOURCE} source/graphics/SpriteBuffer.cpp)
set(SOURCE ${SOURCE} source/graphics/Sprite.cpp)
set(SOURCE ${SOURCE} source/graphics/SpriteRenderer.cpp)

set(SOURCE ${SOURCE} source/main.cpp)

add_executable(${PROJECT_NAME} ${SOURCE})
target_link_libraries(${PROJECT_NAME} ${LIBS})

file(COPY assets/ DESTINATION ${CMAKE_BINARY_DIR}/assets)
