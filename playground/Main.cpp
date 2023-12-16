#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "Application/Application.hpp"
#include "Renderer/Renderer.hpp"

int main()
{
    float scale = 0.5f;

    try
    {
        Playground::Application application;

        // OpenGL starts here
        Playground::Renderer renderer;
        // OpenGL ends here

        bool works = true;
        while (works)
        {
            const auto event = application.PollEvent();

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            if (event)
            {
                if (event->type == SDL_QUIT)
                {
                    works = false;
                }
            }

            // OpenGL starts here

            scale += 0.0001f;

            renderer.Draw();

            // OpenGL ends here

            SDL_Delay(33);
        }
    }
    catch (const std::exception& exception)
    {
        std::cerr << exception.what() << std::endl;
        return -1;
    }

    return 0;
}