#shader vertex
#version 450 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec3 textColor;
layout(location = 2) in vec2 textCoord;

out vec2 v_TextCoord;
out vec3 v_TextColor;
uniform mat4 u_MVP;

void main()
{  
    gl_Position = u_MVP * vec4(position, 0.0f, 1.0f);   
    v_TextColor = textColor;
    v_TextCoord = textCoord;
};

#shader fragment
#version 450 core

layout(location = 0) out vec4 color;
in vec2 v_TextCoord;
in vec3 v_TextColor;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

void main() 
{
    color = texture(u_Texture, v_TextCoord) * vec4(v_TextColor, 1.0f);
};
