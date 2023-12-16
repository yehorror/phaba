#include <stdexcept>

#include "Application.hpp"

namespace Playground 
{
    Application::Application()
    {
        if (SDL_Init(SDL_INIT_VIDEO) != 0)
        {
            throw std::runtime_error("Failed to init SDL: " + std::string(SDL_GetError()));
        }

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

        m_windowHandle =
            SDL_CreateWindow("Whatevs", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);

        if (!m_windowHandle)
        {
            throw std::runtime_error("Failed to create window: " + std::string(SDL_GetError()));
        }

        m_glContext = SDL_GL_CreateContext(m_windowHandle);

        const GLenum glewInitResult = glewInit();
        if (glewInitResult != GLEW_OK)
        {
            throw std::runtime_error(
                "Failed to init GLEW: " + std::string(reinterpret_cast<const char*>(glewGetErrorString(glewInitResult)))
            );
        }
    }

    std::optional<SDL_Event> Application::PollEvent()
    {
        SDL_Event event{};
        if (SDL_PollEvent(&event))
        {
            return event;
        }
        return std::nullopt;
    }
}