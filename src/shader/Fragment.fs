#version 450 core

layout(location = 0) out vec4 color;
in vec2 v_TextCoord;

uniform sampler2D u_Texture;
uniform sampler2D u_Texture1;

void main() 
{
    color = mix(texture(u_Texture, v_TextCoord), texture(u_Texture1, vec2(1.0f-v_TextCoord.x,v_TextCoord.y)), 0.2);
}
