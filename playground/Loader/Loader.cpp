#include "Loader.hpp"
#include <fstream>

namespace Playground
{
    GenericScene Loader::LoadScene(std::filesystem::path path)
    {
        Playground::GenericScene scene;

        std::ifstream input(path);
        if (!input.is_open())
        {
            throw std::runtime_error("Failed to open file [" + path.string() + "]");
        }

        std::string objectName{};
        input >> objectName;

        while (objectName != "END")
        {
            Object objectToAdd = LoadObject("Misc/objects/" + objectName);

            // Read position
            input >> objectToAdd.position.x >> objectToAdd.position.y;

            // Read angle
            input >> objectToAdd.angle;

            // Type (STATIC or DYNAMIC)
            // Currently unused
            std::string type{};
            input >> type;

            scene.AddObject(objectToAdd);
            input >> objectName;
        }

        return scene;
    }

    Object Loader::LoadObject(std::filesystem::path path)
    {
        std::ifstream input(path);
        if (!input.is_open())
        {
            throw std::runtime_error("Failed to open file [" + path.string() + "]");
        }

        std::string shapeName{};
        input >> shapeName;
        // Other fields aren't interesting for now
        // But the 'Object' will represent composition of physical object and other necessary info in the future

        auto& shape = m_storage.GetShape(shapeName);

        return { shape, {0.f, 0.f}, 0.f };
    }
}
