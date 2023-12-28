#include <iostream>
#include "Application/Application.hpp"
#include "Renderer/Renderer.hpp"
#include "Renderer/Colors/Colors.hpp"
#include "Loader/Loader.hpp"
#include "GenericScene/GenericScene.hpp"

int main()
{
    try
    {
        Playground::Application application;
        Playground::Renderer renderer;

        Playground::Loader loader;

        Playground::GenericScene scene = loader.LoadScene("Misc/scenes/level1");

        float scale = 0.1;

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
                }
            }

            renderer.SetScale(scale);

            scene.Render(renderer);

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