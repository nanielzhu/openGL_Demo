#version 450 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 textCoord;

out vec2 v_TextCoord;
uniform mat4 u_MVP;

void main()
{  
    gl_Position = u_MVP * vec4(position, 1.0f);   
    v_TextCoord = textCoord;
}