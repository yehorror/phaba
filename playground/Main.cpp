#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "Application/Application.hpp"
#include "Renderer/Renderer.hpp"
#include "Renderer/Shape/Shape.hpp"

int main()
{
    float scale = 0.5f;

    try
    {
        Playground::Application application;

        // OpenGL starts here
        Playground::Renderer renderer;
        // OpenGL ends here

        static const glm::vec2 s_vertices[] = {
            {-1.0f,  1.0f},
            { 1.0f,  1.0f},
            { 1.0f, -1.0f},
            {-1.0f, -1.0f}
        };

        auto box = Playground::Shape(
            std::span<const glm::vec2>(
                std::begin(s_vertices), std::end(s_vertices)
            ));

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

            scale += 0.001f;

            renderer.Draw(box, scale, {0.5f, 0.5f});
            renderer.Draw(box, -scale, {-0.5f, -0.5f});

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