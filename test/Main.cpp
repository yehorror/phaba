#define SDL_MAIN_HANDLED 

#include <gtest/gtest.h>
#include <SDL2/SDL.h>
#include <GL/glew.h>

int main(int argc, char** argv)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        throw std::runtime_error("Failed to init SDL: " + std::string(SDL_GetError()));
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    const auto windowHandle = SDL_CreateWindow(
        "Whatevs",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800,
        600,
        SDL_WINDOW_OPENGL | SDL_WINDOW_HIDDEN);

    if (!windowHandle)
    {
        return -1;
    }

    auto glContext = SDL_GL_CreateContext(windowHandle);

    const GLenum glewInitResult = glewInit();
    if (glewInitResult != GLEW_OK)
    {
        return -1;
    }

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}