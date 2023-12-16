#define SDL_MAIN_HANDLED 

#include <iostream>
#include <SDL2/SDL.h>
#include <GL/glew.h>

int main()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cerr << "Failed to init SDL: " << SDL_GetError() << std::endl;
        return -1;
    }

    std::cout << "SDL initialized" << std::endl;

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    auto windowHandle = 
        SDL_CreateWindow("Whatevs", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);

    if (!windowHandle)
    {
        std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
        return -1;
    }

    const auto glContext = SDL_GL_CreateContext(windowHandle);

    const GLenum glewInitResult = glewInit();
    if (glewInitResult != GLEW_OK)
    {
        std::cerr << "Failed to init GLEW: " << glewGetErrorString(glewInitResult) << std::endl;
        return -1;
    }

    bool works = true;

    SDL_Event event{};
    while (works)
    {
        if (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                std::cout << "Exiting..." << std::endl;
                works = false;
            }
        }
    }
    return 0;
}