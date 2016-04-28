#include "util/GameTime.h"
#include "graphics/SpriteRenderer.h"
#include "graphics/SpriteAnimation.h"

#include <math.h>
#include <GLFW/glfw3.h>

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
    // glfwSwapInterval(1);

#ifdef OS_WIN32
    if (glxwInit() != 0)
    {
        std::cerr << "Error: cannot init glxw!" << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
    }
#endif

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

    const float playerSpeed = 8.0f;

    float fpsCounter = 0.0f;
    uint32_t fps = 0;

    const float upsFreq = 1.0f / 100.0f;
    float upsCounter = 0.0f;
    uint32_t ups = 0;

    while (!glfwWindowShouldClose(window))
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, GL_TRUE);
        }

        float elapsed = GameTime::elapsed();

        upsCounter += elapsed;
        if (upsCounter >= upsFreq)
        {
            // Update...

            float delta = upsCounter;
            // ToDo: Update is still not smooth enough

            spriteAnimation.update(delta);

            if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
                player->transformation().position.x -= playerSpeed * delta * 100.0f;
            }
            if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
                player->transformation().position.x += playerSpeed * delta * 100.0f;
            }

            ups++;
            upsCounter = 0.0f;
        }

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        spriteRenderer->initiate();

        spriteRenderer->render(player.get());
        spriteRenderer->render(spriteAnimation.getCurrentSpriteRegion());

        spriteRenderer->submit();

#ifdef DEBUG

        fpsCounter += GameTime::elapsed();
        fps++;
        if (fpsCounter >= 1.0f)
        {
            std::cout << "FPS: " << fps << ", UPS: " << ups << std::endl;
            fpsCounter = 0.0f;
            upsCounter = 0.0f;
            fps = 0;
            ups = 0;
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
