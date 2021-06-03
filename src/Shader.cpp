#include "Shader.h"
#include <fstream>
#include <string>
#include <sstream>
#include <GL/Glew.h>
#include <iostream>

Shader::Shader(const std::string vertexfile, const std::string fragmentfile)
                    :mVertexFile(vertexfile),mFragmentFile(fragmentfile)
{

    std::string vertexsource = ParseShader(mVertexFile);
    std::string fragmentsource = ParseShader(mFragmentFile);
    mRenderID = CreateShader(vertexsource, fragmentsource);
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
    std::string atype = "PROGRAM";
    if(type == GL_VERTEX_SHADER)
        atype = "VERTEX";
    if(type == GL_FRAGMENT_SHADER)
        atype = "FRAGMENT";

    checkCompileErrors(id, atype);
    return id;
}

void Shader::checkCompileErrors(unsigned int shader, std::string type)
{
    GLint success;
    GLchar infoLog[1024];
     if(type != "PROGRAM")
    {
         glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    else
    {
         glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if(!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}


std::string Shader::ParseShader(const std::string& file)
{
    std::ifstream stream(file,std::ifstream::in);
    if(!stream.is_open())
        std::cout<<"error to open file\n";
    std::stringstream vStream;
    // read file's buffer contents into streams
    vStream << stream.rdbuf();	
    // close file handlers
    stream.close();
    return vStream.str();
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

void Shader::SetUniformMat4fv(const std::string& name, const glm::mat4& value)
{
    int location = GetUniformlocation(name);
    glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);
}

int Shader::GetUniformlocation(const std::string& colorname)
{
    if(locationCache.find(colorname) != locationCache.end())
        return locationCache[colorname];
    
    int location = glGetUniformLocation(mRenderID, colorname.c_str());
    if(location == -1)
    {
        std::cout <<"Uniform Location for "<<colorname<<"  doesn't exist\n";
    }
    locationCache[colorname] = location;
    return location;
}

void Shader::SetUniformVec3(const std::string& name, float v1, float v2, float v3)
{
    int location = GetUniformlocation(name);
    glUniform3f(location, v1,v2,v3);
}

void Shader::SetUniformVec3(const std::string& name, const glm::vec3 value)
{
    int location = GetUniformlocation(name);
    glUniform3fv(location, 1, &value[0]); 
}

void Shader::SetUniform1f(const std::string& name, const float value)
{
    int location = GetUniformlocation(name);
    glUniform1f(location, value); 
}