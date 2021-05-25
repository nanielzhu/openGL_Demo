#pragma once
#include <string>
#include <unordered_map>
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

class Shader
{
private:
    unsigned int mRenderID;
    const std::string mVertexFile;
    const std::string mFragmentFile;
    std::unordered_map<std::string, int> locationCache;

public:
    Shader(const std::string vertexfile, const std::string fragmentfile);
    ~Shader();
    void Bind() const;
    void Unbind() const;
    void SetUniform1i(const std::string& name, int values);
    void SetUniform4f(const std::string& name, float v1, float v2, float v3, float v4);
    void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);
    void SetUniformMat4fv(const std::string& name, const glm::mat4& value);
    void SetUniformVec3(const std::string& name, float v1, float v2, float v3);
    void SetUniformVec3(const std::string& name, const glm::vec3 value);
    void SetUniformVec3(const std::string& name, const float value);

private:
    unsigned int CompileShader(unsigned int type, const std::string& source);
    void checkCompileErrors(unsigned int shader, std::string type);
    std::string ParseShader(const std::string& file);
    unsigned int CreateShader(const std::string& vertexshader, const std::string& fragmentshader);
    int GetUniformlocation(const std::string&);
};
