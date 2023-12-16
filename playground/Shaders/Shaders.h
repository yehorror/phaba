#pragma once

#include <string_view>

constexpr std::string_view FRAGMENT_SHADER = R"shader(
    #version 430 core
    
    out vec3 color;
    in vec3 fragmentColor;
    
    void main()
    {
        color = fragmentColor;
    }
)shader";

constexpr std::string_view VERTEX_SHADER = R"shader(
    #version 430 core
    
    layout(location = 0) in vec3 vertexPos;
    layout(location = 1) in vec3 vertexColor;

    layout (std140, binding = 2) uniform Matrices
    {
        //mat4 transform;
        float scale;
    };
    
    out vec3 fragmentColor;
    
    void main()
    {
        gl_Position.xyz = 0.5 * vertexPos;
        gl_Position.w = 1.0;
    
        fragmentColor = vertexColor;
    }
)shader";