#pragma once

#include <map>
#include <string>
#include "Shape/Shape.hpp"

namespace Playground
{
    class Storage
    {
    public:
        Shape& GetShape(std::string shapeName);

    private:
        std::map<std::string, Playground::Shape> m_shapes;
    };
}
