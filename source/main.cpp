#include <iostream>
#include <GLFW/glfw3.h>

#include "util/GameTime.h"
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

    std::shared_ptr<Image> imagePlayer = std::shared_ptr<Image>(Image::load("assets/player.png"));
    std::shared_ptr<Image> imageBlow = std::shared_ptr<Image>(Image::load("assets/blow.png"));

    std::unique_ptr<Sprite> player = std::unique_ptr<Sprite>(
            new Sprite(Transformation(Vector2f(0.0f, 0.0f), Vector2f(32.0f, 32.0f)),
                       GraphicsFactory::createTexture2D(imagePlayer.get())
            )
    );
    std::unique_ptr<SpriteRegion> blow = std::unique_ptr<SpriteRegion>(
            new SpriteRegion(0, 0, 4, 4,
                             Transformation(),
                             GraphicsFactory::createTexture2D(imageBlow.get())
            )
    );

    std::unique_ptr<SpriteRenderer> spriteRenderer = std::unique_ptr<SpriteRenderer>(new SpriteRenderer);
    spriteRenderer->create();

#ifdef DEBUG
    std::cout << "OpenGL: " << (const char *)glGetString(GL_VERSION) << std::endl;
#endif

    float fpsCounter = 0.0f;
    uint32_t fps = 0;

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        spriteRenderer->initiate();
        spriteRenderer->render(player.get());
        spriteRenderer->submit();

#ifdef DEBUG

        fpsCounter += GameTime::elapsed();
        fps++;
        if (fpsCounter >= 1.0f)
        {
            std::cout << "FPS: " << fps << std::endl;
            fpsCounter = 0.0f;
            fps = 0;
        }

#endif

        GameTime::reset();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwMakeContextCurrent(nullptr);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
