#include "core/Renderer.h"
#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <time.h>

/**
 * Application entry point.
 */
int main(int, const char **)
{
    // Randomize timer...
    ::srand(static_cast<uint32_t>(::time(nullptr)));

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

#ifdef OS_WIN32
    if (glxwInit() != 0)
    {
        std::cerr << "Error: cannot init glxw!" << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
    }
#endif

    // Setup OpenGL
    GLCALL(glDisable(GL_DEPTH_TEST));                           // Disable depth test (no need for 2D)
    GLCALL(glEnable(GL_BLEND));                                 // Enable blending (transparency/alpha channel)
    GLCALL(glEnable(GL_CULL_FACE));                             // Enable face culling (to draw objects from one side)
    GLCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    GLCALL(glCullFace(GL_FRONT));
    GLCALL(glViewport(0, 0, 480, 800));

#ifdef DEBUG
    std::cout << "OpenGL: " << (const char *)glGetString(GL_VERSION) << std::endl;
#endif

    while (!glfwWindowShouldClose(window))
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, GL_TRUE);
        }

        GLCALL(glClearColor(0.4f, 0.6f, 0.8f, 1.0f));
        GLCALL(glClear(GL_COLOR_BUFFER_BIT));

        // Render section...

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwMakeContextCurrent(nullptr);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
