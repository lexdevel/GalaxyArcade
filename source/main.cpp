#include <iostream>
#include <math.h>
#include <GLFW/glfw3.h>

#include "util/GameTime.h"
#include "graphics/SpriteRenderer.h"
#include "graphics/SpriteAnimation.h"

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
            new Sprite(Transformation(Vector2f(0.0f, -128.0f), Vector2f(32.0f, 32.0f)),
                       GraphicsFactory::createTexture2D(imagePlayer.get())
            )
    );

    std::shared_ptr<Texture2D> blowTexture = std::shared_ptr<Texture2D>(GraphicsFactory::createTexture2D(imageBlow.get()));
    SpriteAnimation spriteAnimation = SpriteAnimation(1.0f / 60.0f);

    for (unsigned int y = 0; y < 4; y++) {
        for (unsigned int x = 0; x < 5; x++) {
            spriteAnimation.push(new SpriteRegion(5, 4, x, y,
                                                  Transformation(Vector2f(0.0f, 32.0f), Vector2f(64.0f, 64.0f)),
                                                  blowTexture.get()));
        }
    }

    std::unique_ptr<SpriteRenderer> spriteRenderer = std::unique_ptr<SpriteRenderer>(new SpriteRenderer);
    spriteRenderer->create();

#ifdef DEBUG
    std::cout << "OpenGL: " << (const char *)glGetString(GL_VERSION) << std::endl;
#endif

    const float playerSpeed = 2.0f;

    float fpsCounter = 0.0f;
    uint32_t fps = 0;

    while (!glfwWindowShouldClose(window))
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, GL_TRUE);
        }

        float elapsed = GameTime::elapsed();
        spriteAnimation.update(elapsed);

        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
            player->transformation().position.x -= ::ceilf(playerSpeed * (100.0f * elapsed));
        }
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
            player->transformation().position.x += ::ceilf(playerSpeed * (100.0f * elapsed));
        }

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        spriteRenderer->initiate();
        spriteRenderer->render(player.get());
        spriteRenderer->submit();

        spriteRenderer->initiate();
        spriteRenderer->render(spriteAnimation.getCurrentSpriteRegion());
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
