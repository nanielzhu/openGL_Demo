#pragma once
#include <string>
#include <unordered_map>
#include "glm/glm.hpp"

struct ShaderSource {
    std::string vertexsource;
    std::string fragmentsource;
};


class Shader
{
private:
    unsigned int mRenderID;
    const std::string filePath;
    std::unordered_map<std::string, int> locationCache;

public:
    Shader(const std::string filePath);
    ~Shader();
    void Bind() const;
    void Unbind() const;
    void SetUniform1i(const std::string& name, int values);
    void SetUniform4f(const std::string& name, float v1, float v2, float v3, float v4);
    void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);

private:
    unsigned int CompileShader(unsigned int type, const std::string& source);
    ShaderSource ParseShader(const std::string& filepath);
    unsigned int CreateShader(const std::string& vertexshader, const std::string& fragmentshader);
    int GetUniformlocation(const std::string&);
};
