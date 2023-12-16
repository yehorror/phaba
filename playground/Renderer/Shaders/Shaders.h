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
    
    layout(location = 0) in vec2 vertexPos;
    layout(location = 1) in vec3 vertexColor;

    layout (std140) uniform Matrices
    {
        mat4 transform;
        vec2 offset;
    };
    
    out vec3 fragmentColor;
    
    void main()
    {
        gl_Position = transform * vec4(vertexPos, 0.f, 1.f) + vec4(offset, 0.0, 0.0);
        gl_Position.w = 1.0;
    
        fragmentColor = vertexColor;
    }
)shader";