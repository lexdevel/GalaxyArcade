#include <iostream>
#include <assert.h>

#include <OpenGL/OpenGL.h>
#include <GLFW/glfw3.h>

#include "util/GameTime.h"
#include "graphics/SpriteRenderer.h"
#include "graphics/TileRenderer.h"

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



    // Blow implementation
    Image *blowImage = Image::load("assets/blow.png");
    TileRenderer *tileRenderer = new TileRenderer(4, 4, GraphicsFactory::createTexture2D(blowImage));
    tileRenderer->create();

    Transformation blowTransformation;
    blowTransformation.position.x = 128.0f;
    blowTransformation.position.y = 128.0f;
    blowTransformation.scale.x = 64.0f;
    blowTransformation.scale.y = 64.0f;

    Tile *blowTile = new Tile(Vector2f(0.0f, 0.0f));
    const float blowTick = 1.0f / 60.0f;
    float blowCounter = 0.0f;

    // float elapsed = 0.0f;
    float fpsCounter = 0.0f;
    uint32_t fps = 0;

    while (!glfwWindowShouldClose(window))
    {
        blowCounter += GameTime::elapsed();
        if (blowCounter > blowTick)
        {
            blowTile->texindex().x = blowTile->texindex().x + 1.0f;

            if (blowTile->texindex().x > 4.0f) {
                blowTile->texindex().x = 0.0f;
                blowTile->texindex().y = blowTile->texindex().y + 1.0f;
            }
            if (blowTile->texindex().y > 4.0f) {
                blowTile->texindex().x = 0.0f;
                blowTile->texindex().y = 0.0f;
            }

            blowCounter = 0.0f;
        }

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

        tileRenderer->render(blowTransformation, blowTile);

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
