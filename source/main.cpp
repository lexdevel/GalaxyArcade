#include "graphics/SpriteRenderer.h"
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

    GLCALL(glDisable(GL_DEPTH_TEST));
    GLCALL(glEnable(GL_BLEND));
    GLCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    GLCALL(glViewport(0, 0, 480, 800));

    std::shared_ptr<Image>      imagePlayer     = std::shared_ptr<Image>(Image::load("assets/player.png"));
    std::shared_ptr<Texture2D>  playerTexture   = std::shared_ptr<Texture2D>(GraphicsFactory::createTexture2D(imagePlayer.get()));
    std::unique_ptr<Sprite>     player          = std::unique_ptr<Sprite>(new Sprite(Transformation(Vector2f(0.0f, 0.0f), Vector2f(0.12, 0.12f)), playerTexture));

    std::unique_ptr<SpriteRenderer> spriteRenderer = std::unique_ptr<SpriteRenderer>(new SpriteRenderer());
    spriteRenderer->create();
    spriteRenderer->resize(480, 800);

#ifdef DEBUG
    std::cout << "OpenGL: " << (const char *)glGetString(GL_VERSION) << std::endl;
#endif

    while (!glfwWindowShouldClose(window))
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, GL_TRUE);
        }

        GLCALL(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
        GLCALL(glClear(GL_COLOR_BUFFER_BIT));

        spriteRenderer->initiate();
        spriteRenderer->render(player.get());
        spriteRenderer->submit();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwMakeContextCurrent(nullptr);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
