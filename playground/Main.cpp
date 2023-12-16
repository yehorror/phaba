#include <iostream>
#include "Application/Application.hpp"
#include "Renderer/Renderer.hpp"
#include "Renderer/Shape/Shape.hpp"
#include "Renderer/Colors/Colors.hpp"

int main()
{
    float angle = 0.5f;

    try
    {
        Playground::Application application;
        Playground::Renderer renderer;

        static const Playground::Color s_whiteBox[] = {
            Playground::kWhite, Playground::kWhite, Playground::kWhite, Playground::kWhite
        };

        static const Playground::Color s_redBox[] = {
            Playground::kRed, Playground::kRed, Playground::kRed, Playground::kRed
        };

        auto whiteColors = Playground::Colors(std::span<const Playground::Color>(s_whiteBox));
        auto redColors = Playground::Colors(std::span<const Playground::Color>(s_redBox));

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

        float scale = 0.5;

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
                if (event->type == SDL_KEYDOWN)
                {
                    switch (event->key.keysym.sym)
                    {
                    case 'w':
                        scale += 0.1f;
                        break;
                    case 's':
                        scale -= 0.1f;
                        break;
                    }
                    
                    renderer.SetScale(scale);
                }
            }

            // OpenGL starts here

            angle += 0.001f;

            renderer.Draw(box, whiteColors, angle, {0.5f, 0.5f});
            renderer.Draw(box, redColors, -angle, {-0.5f, -0.5f});

            // OpenGL ends here

            SDL_Delay(16);
        }
    }
    catch (const std::exception& exception)
    {
        std::cerr << exception.what() << std::endl;
        return -1;
    }

    return 0;
}