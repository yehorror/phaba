#include <iostream>
#include "Application/Application.hpp"

int main()
{
    try
    {
        Playground::Application application;

        bool works = true;
        while (works)
        {
            const auto event = application.PollEvent();

            if (event)
            {
                if (event->type == SDL_QUIT)
                {
                    works = false;
                }
            }
        }
    }
    catch (const std::exception& exception)
    {
        std::cerr << exception.what() << std::endl;
        return -1;
    }

    return 0;
}