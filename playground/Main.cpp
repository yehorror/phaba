#include <iostream>
#include "Application/Application.hpp"
#include "Renderer/Renderer.hpp"
#include "Renderer/Shape/Shape.hpp"
#include "Renderer/Colors/Colors.hpp"
#include "Loader/Loader.hpp"
#include "Scene/Scene.hpp"

int main()
{
    float angle = 0.5f;

    try
    {
        Playground::Application application;
        Playground::Renderer renderer;

        Playground::Scene scene(renderer);

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

            scene.Render();

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