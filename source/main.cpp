#include "graphics/SpriteRenderer.h"
#include "util/BitmapLoader.h"
#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <time.h>

#define WINDOW_INITIAL_W    800
#define WINDOW_INITIAL_H    480

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
    // glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    auto window = glfwCreateWindow(WINDOW_INITIAL_W, WINDOW_INITIAL_H, "Galaxy Arcade", nullptr, nullptr);
    if (!window) {
        std::cerr << "Error: cannot create window!" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

#if !defined(DEBUG)
    glfwSwapInterval(1);    // Enable v-sync
#endif

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
    GLCALL(glViewport(0, 0, WINDOW_INITIAL_W, WINDOW_INITIAL_H));

    std::shared_ptr<SpriteRenderer> spriteRenderer;

    try
    {
        spriteRenderer = std::shared_ptr<SpriteRenderer>(new SpriteRenderer());
        spriteRenderer->resize(WINDOW_INITIAL_W, WINDOW_INITIAL_H);
    }
    catch (const std::runtime_error &ex)
    {
        std::cerr << "Runtime error: " << ex.what() << std::endl;
        std::cin.get();
        glfwDestroyWindow(window);
        glfwTerminate();
        return -2;
    }

    glfwSetWindowUserPointer(window, spriteRenderer.get());
    glfwSetWindowSizeCallback(window, [](GLFWwindow *window, int32_t w, int32_t h) -> void {
        auto renderer = static_cast<SpriteRenderer *>(glfwGetWindowUserPointer(window));
        if (renderer != nullptr) {
            GLCALL(glViewport(0, 0, static_cast<GLsizei>(w), static_cast<GLsizei>(h)));
            renderer->resize(static_cast<uint32_t>(w), static_cast<uint32_t>(h));
        }
    });

    // Load resources...
    auto playerBitmap            = BitmapLoader::load("assets/player.png");
    auto playerTextureImage      = std::shared_ptr<Texture2D>(new Texture2D(playerBitmap, TextureFilter::LINEAR));
    auto playerTransformation    = Transformation(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 90.0f), glm::vec3(0.16f, 0.16f, 0.0f));
    auto player                  = std::shared_ptr<Sprite>(new Sprite(playerTransformation, playerTextureImage));

#ifdef DEBUG
    double   time   = glfwGetTime();
    uint32_t frames = 0;
#endif

    while (!glfwWindowShouldClose(window))
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, GL_TRUE);
        }

        spriteRenderer->invalidate(0.4f, 0.6f, 0.8f, 1.0f);
        spriteRenderer->initiate();
        spriteRenderer->render(player.get());
        spriteRenderer->submit();

        glfwSwapBuffers(window);
        glfwPollEvents();

#ifdef DEBUG
        ++frames;
        if (glfwGetTime() - time >= 1.0)
        {
            std::cout << "FPS: " << frames << std::endl;
            frames  = 0;
            time    = glfwGetTime();
        }
#endif
    }

    glfwMakeContextCurrent(nullptr);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
