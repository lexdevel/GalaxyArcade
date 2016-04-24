#include <iostream>
#include <assert.h>

#include <OpenGL/OpenGL.h>
#include <GLFW/glfw3.h>

#include "graphics/SpriteRenderer.h"

/**
 * Application entry point.
 */
int main(int, const char **)
{
    if (glfwInit() != GL_TRUE)
    {
        std::cerr << "Error: cannot init glfw!" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow *window = glfwCreateWindow(480, 800, "Galaxy Arcade", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glViewport(0, 0, 480, 800);

#ifdef DEBUG
    std::cout << "OpenGL: " << (const char *)glGetString(GL_VERSION) << std::endl;
#endif

    SpriteRenderer *spriteRenderer = SpriteRenderer::create();

    Transformation transformation;
    transformation.position = Vector2f(128.0f, 256.0f);
    transformation.scale = Vector2f(64.0f, 64.0f);

    Image *image = Image::load("assets/player.png");
    assert(image);

    Texture2D *texture = GraphicsFactory::createTexture2D(image);

    while (!glfwWindowShouldClose(window))
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE)) {
            glfwSetWindowShouldClose(window, GL_TRUE);
        }

        if (glfwGetKey(window, GLFW_KEY_LEFT)) {
            transformation.position.x -= 2.0f;
        }

        if (glfwGetKey(window, GLFW_KEY_RIGHT)) {
            transformation.position.x += 2.0f;
        }

        glClearColor(0.4f, 0.6f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        spriteRenderer->render(transformation, texture);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    delete spriteRenderer;

    glfwMakeContextCurrent(nullptr);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
