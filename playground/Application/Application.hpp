#pragma once

#define SDL_MAIN_HANDLED 

#include <optional>

#include <SDL2/SDL.h>
#include <GL/glew.h>

namespace Playground 
{
    class Application
    {
    public:
        Application();

        std::optional<SDL_Event> PollEvent();

    private:
        SDL_Window* m_windowHandle;
        SDL_GLContext m_glContext;
    };
}