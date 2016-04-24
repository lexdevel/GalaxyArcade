#include <iostream>
#include <assert.h>

#include <OpenGL/OpenGL.h>
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

#ifdef DEBUG
    std::cout << "OpenGL: " << (const char *)glGetString(GL_VERSION) << std::endl;
#endif

    SpriteRenderer *spriteRenderer = SpriteRenderer::create();

    Image *image = Image::load("assets/player.png");
    assert(image);

    Texture2D *texture = GraphicsFactory::createTexture2D(image);

    Sprite *sprite = new Sprite(texture);
    sprite->transformation().position.x = 128.0f;
    sprite->transformation().position.y = 800.0f - 128.0f;
    sprite->transformation().scale.x = 32.0f;
    sprite->transformation().scale.y = 32.0f;

    // float elapsed = 0.0f;
    float fpsCounter = 0.0f;
    uint32_t fps = 0;

    while (!glfwWindowShouldClose(window))
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE)) {
            glfwSetWindowShouldClose(window, GL_TRUE);
        }

        //                   elaped(1 = 1sec)   * 100 (1/10 sec) * speed
        const float speed = GameTime::elapsed() * 100.0f * 4.0f;

        if (glfwGetKey(window, GLFW_KEY_LEFT)) {
            sprite->transformation().position.x -= speed;
        }

        if (glfwGetKey(window, GLFW_KEY_RIGHT)) {
            sprite->transformation().position.x += speed;
        }

        const Rect &spriteBounds = sprite->calculateBounds();
        if (spriteBounds.x < 0.0f) {
            sprite->transformation().position.x = 32.0f;
        }
        if (spriteBounds.x + spriteBounds.w + sprite->transformation().scale.x > 480.0f) {
            sprite->transformation().position.x = 480.0f - sprite->transformation().scale.x;
        }

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        spriteRenderer->render(sprite);

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

    delete spriteRenderer;

    glfwMakeContextCurrent(nullptr);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
