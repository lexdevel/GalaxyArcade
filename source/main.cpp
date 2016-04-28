#include "util/GameTime.h"
#include "graphics/SpriteRenderer.h"
#include "graphics/SpriteAnimation.h"
#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <time.h>

/**
 * Application entry point.
 */
int main(int, const char **)
{
    // Randomize timer...
    srand(static_cast<unsigned int>(time(nullptr)));

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

    // Load images
    std::shared_ptr<Image> imagePlayer          = std::shared_ptr<Image>(Image::load("assets/player.png"));
    std::shared_ptr<Image> imageBlow            = std::shared_ptr<Image>(Image::load("assets/blow.png"));
    std::shared_ptr<Image> imageAsteroid        = std::shared_ptr<Image>(Image::load("assets/asteroid.png"));

    // Generate textures
    std::shared_ptr<Texture2D> playerTexture    = std::shared_ptr<Texture2D>(GraphicsFactory::createTexture2D(imagePlayer.get()));
    std::shared_ptr<Texture2D> blowTexture      = std::shared_ptr<Texture2D>(GraphicsFactory::createTexture2D(imageBlow.get()));
    std::shared_ptr<Texture2D> asteroidTexture  = std::shared_ptr<Texture2D>(GraphicsFactory::createTexture2D(imageAsteroid.get()));

    // Create sprites
    std::unique_ptr<Sprite> player;
    std::unique_ptr<SpriteAnimation> asteroid;
    std::unique_ptr<SpriteAnimation> blow;

    player.reset(new Sprite(Transformation(Vector2f(0.0f, -256.0f), Vector2f(32.0f, 32.0f)), playerTexture.get()));
    asteroid.reset(new SpriteAnimation(1.0f / 30.0f, PlaybackMode::LOOP));
    blow.reset(new SpriteAnimation(1.0f / 48.0f, PlaybackMode::ONCE));

    float aX = static_cast<float>(rand() % 240 - 240);
    float aY = 480.0f;

    for (uint32_t y = 0; y < 4; y++) {
        for (uint32_t x = 0; x < 5; x++) {
            if (x == 4 && y == 3) { continue; }
            asteroid->push(new SpriteRegion(5, 4, x, y, Transformation(Vector2f(aX, aY), Vector2f(24.0f, 24.0f)), asteroidTexture.get()));
            blow->push(new SpriteRegion(5, 4, x, y, Transformation(Vector2f(0.0f, 0.0f), Vector2f(64.0f, 64.0f)), blowTexture.get()));
        }
    }

    asteroid->setAnimationState(AnimationState::PLAYING);
    blow->setAnimationState(AnimationState::STOPPED);

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

    bool dead = false;

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

            asteroid->update(delta);
            blow->update(delta);

            if (!dead)
            {
                Transformation asteroidTransformation = asteroid->transformation();
                asteroidTransformation.position.y -= 4.0f * delta * 100.0f;

                Rect asteroidBounds = asteroid->getCurrentSpriteRegion()->calculateBounds();
                Rect playerBounds = player->calculateBounds();

                if (asteroidBounds.isOverlapped(playerBounds))
                {
                    Transformation blowTransformation = player->transformation();
                    blowTransformation.scale = Vector2f(64.0f, 64.0f);

                    blow->setTransformation(blowTransformation);
                    blow->setAnimationState(AnimationState::PLAYING);
                    asteroidTransformation.position.y = -480.0f;

                    dead = true;
                }

                if (asteroidTransformation.position.y < -480.0f)
                {
                    asteroidTransformation.position.x = static_cast<float>(rand() % 240 - 240);
                    asteroidTransformation.position.y = 480.0f;
                }

                asteroid->setTransformation(asteroidTransformation);
            }

            if (blow->animationState() == AnimationState::STOPPED) {
                dead = false;
            }

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

        if (!dead) {
            spriteRenderer->render(player.get());
            spriteRenderer->render(asteroid->getCurrentSpriteRegion());
        } else {
            if (blow->animationState() == AnimationState::PLAYING) {
                spriteRenderer->render(blow->getCurrentSpriteRegion());
            }
        }

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
