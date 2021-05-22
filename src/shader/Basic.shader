#shader vertex
#version 450 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 textCoord;

out vec2 v_TextCoord;
uniform mat4 u_MVP;

void main()
{  
    gl_Position = u_MVP * vec4(position, 1.0f);   
    v_TextCoord = textCoord;
};

#shader fragment
#version 450 core

layout(location = 0) out vec4 color;
in vec2 v_TextCoord;

uniform sampler2D u_Texture;
uniform sampler2D u_Texture1;

void main() 
{
    color = mix(texture(u_Texture, v_TextCoord), texture(u_Texture1, vec2(1.0f-v_TextCoord.x,v_TextCoord.y)), 0.2);
};
