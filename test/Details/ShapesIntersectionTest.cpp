#include <gtest/gtest.h>
#include <Buffer/Buffer.hpp>
#include <Shader/Shader.hpp>
#include <Program/Program.hpp>

namespace
{
    constexpr std::string_view testShaderCode = R"(
        #version 430 core

        layout (local_size_x = 1, local_size_y = 1, local_size_z = 1) in;

        layout(std430, binding = 0) buffer Input
        {

        };

        layout(std430, binding = 1) buffer Output
        {
            bool isPointInsideOfPolygon;
        };

        bool IsPointInsideOfAShape(vec2 point, uint shapeIndex)
        {
            return false;
        }
        
        void main()
        {

        }
    )";

}

TEST(ShapesIntersectionTest, PointIsInsideOfASquare_ReturnsTrue)
{
    // TODO 
}