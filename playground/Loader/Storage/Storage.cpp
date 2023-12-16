#include "Storage.hpp"
#include <vector>
#include <filesystem>
#include <fstream>

namespace
{
    std::vector<glm::vec2> LoadVertices(std::filesystem::path path)
    {
        std::ifstream input(path);
        if (!input.is_open())
        {
            throw std::runtime_error("Failed to open file [" + path.string() + "]");
        }

        unsigned int numVertices{};
        input >> numVertices;

        std::vector<glm::vec2> result;
        result.reserve(numVertices);

        for (unsigned int i = 0; i < numVertices; ++i)
        {
            float x{}, y{};
            input >> x >> y;

            result.push_back({x, y});
        }

        return result;
    }
}

namespace Playground
{
    Shape& Storage::GetShape(std::string shapeName)
    {
        if (m_shapes.find(shapeName) != m_shapes.cend())
        {
            return m_shapes[shapeName];
        }

        auto vertices = LoadVertices("Misc/shapes/" + shapeName);

        m_shapes.emplace(shapeName, Shape(vertices));

        return m_shapes[shapeName];
    }
}
