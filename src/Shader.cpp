#include "Shader.h"
#include <fstream>
#include <string>
#include <sstream>
#include <GL/Glew.h>
#include <iostream>

Shader::Shader(const std::string filePath):filePath(filePath),mRenderID(0)
{

    ShaderSource source = ParseShader("src/shader/Basic.shader");
    mRenderID = CreateShader(source.vertexsource,source.fragmentsource);
    glUseProgram(mRenderID);
}

Shader::~Shader()
{
    glDeleteProgram(mRenderID);
}

void Shader::Bind() const
{
    glUseProgram(mRenderID);
}

void Shader::Unbind() const
{
    glUseProgram(0);
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source) 
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);
    int result;
    glGetShaderiv(id,GL_COMPILE_STATUS, &result);
    if( result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id,length,&length, message);
        std::cout << "Failed to compile " <<
        (type == GL_VERTEX_SHADER? "Vertex":"Fragment")<<" Shader"<<std::endl;
        std::cout<<message<<std::endl;
        glDeleteShader(id);
        return 0;
    }
    return id;
}


ShaderSource Shader::ParseShader(const std::string& filepath)
{
    std::ifstream stream(filepath,std::ifstream::in);
    if(!stream.is_open())
        std::cout<<"error to open file\n";
    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };
    std::string line;
    std::stringstream  ss[2];
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line))
    {
        if(line.find("#shader") != std::string::npos)
        {

            if(line.find("vertex") != std::string::npos)
            {
                type = ShaderType::VERTEX;
            } else if(line.find("fragment") != std::string::npos)
            {
                type = ShaderType::FRAGMENT;
            }
        } else
        {
            ss[int(type)] <<line <<'\n';
        }
    }
    return {ss[0].str(), ss[1].str() };
}

unsigned int Shader::CreateShader(const std::string& vertexshader, const std::string& fragmentshader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER,vertexshader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER,fragmentshader);
    glAttachShader(program,vs);
    glAttachShader(program,fs);
    glLinkProgram(program);
    glValidateProgram(program);
    glDeleteShader(vs);
    glDeleteShader(fs);
    return program;
}

void Shader::SetUniform1i(const std::string& name, int values)
{
    int location = GetUniformlocation(name);
    glUniform1i(location, values);
}

void Shader::SetUniform4f(const std::string& name, float v1, float v2, float v3, float v4)
{
    int location = GetUniformlocation(name);
    glUniform4f(location, v1, v2, v3, v4);
}

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
    int location = GetUniformlocation(name);
    glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
}

int Shader::GetUniformlocation(const std::string& colorname)
{
    if(locationCache.find(colorname) != locationCache.end())
        return locationCache[colorname];
    
    int location = glGetUniformLocation(mRenderID, colorname.c_str());
    if(location == -1)
    {
        std::cout <<"Uniform Location for "<<colorname<<"doesn't exist\n";
    }
    locationCache[colorname] = location;
    return location;
}