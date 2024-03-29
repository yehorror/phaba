#include <iostream>
#include <chrono>
#include "Application/Application.hpp"
#include "Renderer/Renderer.hpp"
#include "Renderer/Colors/Colors.hpp"
#include "GenericScene/GenericScene.hpp"
#include "Scenes/Demo1/Demo1.hpp"

int main()
{
    try
    {
        Playground::Application application;
        Playground::Renderer renderer;

        std::unique_ptr<Playground::GenericScene> scene = std::make_unique<Playground::Demo1>();

        float scale = 0.1;

        auto previousTimePoint = std::chrono::system_clock::now();

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

            auto currentTimePoint = std::chrono::system_clock::now();

            const auto millisecondsPassed = 
                std::chrono::duration_cast<std::chrono::milliseconds>(currentTimePoint - previousTimePoint).count();

            previousTimePoint = currentTimePoint;

            float deltaTime = millisecondsPassed / 1'000.f;

            scene->Step(deltaTime);
            scene->Render(renderer);

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