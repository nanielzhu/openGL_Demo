#version 450 core

out vec4 FragColor;
struct Light {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Light light; 

void main()
{
    vec3 lightColor = light.ambient + light.diffuse +light.specular;
    FragColor = vec4(lightColor,1.0f);
}