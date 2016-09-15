#include "graphics/SpriteRenderer.h"
#include "util/BitmapLoader.h"
#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <time.h>

/**
 * @brief Application entry point.
 * @param argc Command-line arguments length
 * @param argv Command-line arguments
 */
int main(int argc, const char **argv)
{
    (void) argc;    // Avoid unused parameter warning - argc
    (void) argv;    // Avoid unused parameter warning - argv

    ::srand(static_cast<unsigned>(::time(nullptr))); // Randomize timer...

    if (glfwInit() != GL_TRUE) {
        std::cerr << "Error: cannot init glfw!" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    auto window = glfwCreateWindow(800, 480, "Galaxy Arcade", nullptr, nullptr);
    if (!window) {
        std::cerr << "Error: cannot create window!" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    // glfwSwapInterval(1);

#ifdef OS_WIN32
    if (glxwInit() != 0) {
        std::cerr << "Error: cannot init glxw!" << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }
#endif

    // Setup OpenGL
    GLCALL(glDisable(GL_DEPTH_TEST));                           // Disable depth test (no need for 2D)
    GLCALL(glEnable(GL_BLEND));                                 // Enable blending (transparency/alpha channel)
    GLCALL(glEnable(GL_CULL_FACE));                             // Enable face culling (to draw objects from one side)
    GLCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    GLCALL(glCullFace(GL_FRONT));
    GLCALL(glViewport(0, 0, 800, 480));

    std::shared_ptr<SpriteRenderer> spriteRenderer;

    try
    {
        spriteRenderer = std::shared_ptr<SpriteRenderer>(new SpriteRenderer());
        spriteRenderer->resize(800, 480);
    }
    catch (const std::runtime_error &ex)
    {
        std::cerr << "Runtime error: " << ex.what() << std::endl;
        std::cin.get();
        glfwDestroyWindow(window);
        glfwTerminate();
        return -2;
    }

    // Load resources...
    std::shared_ptr<Bitmap>     playerBitmap            = BitmapLoader::load("assets/player.png");
    std::shared_ptr<Texture2D>  playerTextureImage      = std::shared_ptr<Texture2D>(new Texture2D(playerBitmap, TextureFilter::LINEAR));
    Transformation              playerTransformation    = Transformation(Vector2f(0.0f, 0.0f), Vector2f(0.16f, 0.16f));
    std::shared_ptr<Sprite>     player                  = std::shared_ptr<Sprite>(new Sprite(playerTransformation, playerTextureImage));

#ifdef DEBUG
    double   time   = glfwGetTime();
    uint32_t fps    = 0;
#endif

    while (!glfwWindowShouldClose(window))
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, GL_TRUE);
        }

        GLCALL(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
        GLCALL(glClear(GL_COLOR_BUFFER_BIT));

        // Render section...
        spriteRenderer->initiate();
        spriteRenderer->render(player.get());
        spriteRenderer->submit();

        glfwSwapBuffers(window);
        glfwPollEvents();

#ifdef DEBUG
        fps++;
        if (glfwGetTime() - time >= 1.0)
        {
            std::cout << "FPS: " << fps << std::endl;
            fps  = 0;
            time = glfwGetTime();
        }
#endif
    }

    glfwMakeContextCurrent(nullptr);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
