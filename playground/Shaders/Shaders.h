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
    
    layout(location = 0) in vec3 vertexPosition_modelspace;
    layout(location = 1) in vec3 vertexColor;
    
    out vec3 fragmentColor;
    
    layout (std140) uniform ExampleBlock
    {
        float value;
        vec3  vector;
        mat4  matrix;
        float values[3];
        bool  boolean;
        int   integer;
    };  
    
    void main()
    {
        gl_Position.xyz = vertexPosition_modelspace;
        gl_Position.w = 1.0;
    
        fragmentColor = vertexColor;
    }
)shader";