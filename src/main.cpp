#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include "render.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"

struct ShaderSource {
    std::string vertexsource;
    std::string fragmentsource;
};

static ShaderSource ParseShader(const std::string& filepath)
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
static unsigned int CompileShader(unsigned int type, const std::string& source) 
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

static unsigned int CreateShader(const std::string& vertexshader, const std::string& fragmentshader)
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

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main()
{
        GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(2);
        // glad: load all OpenGL function pointers
        // ---------------------------------------
    if (glewInit() != GLEW_OK)
    {
            std::cout << "Failed to initialize GLEW" << std::endl;
            return -1;
    }
     // render loop
    // -----------
    float position[] = {
            -0.5f,-0.5f, //0
             0.5f,-0.5f, //1
             0.5f, 0.5f, //2
            -0.5f, 0.5f  //3
    };

    unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
    };
    VertexArray va;
    VertexBuffer vb(position, sizeof(position));
    VertexBufferLayout layout;
    layout.Push<float>(2);
    va.addBuffer(vb, layout);
    IndexBuffer ib(indices, 6* sizeof(unsigned int));

    ShaderSource source = ParseShader("src/shader/Basic.shader");
    unsigned int shader = CreateShader(source.vertexsource,source.fragmentsource);
    glUseProgram(shader);
    glCall(int location = glGetUniformLocation(shader, "u_Color"));
    ASSERT( location != -1);
//    glCall(glUniform4f(location, 0.2f, 0.3f, 0.8f, 1.0f));
    float x = 0.5f, y = 0.1f, z = 0.2f;
    float increment = 0.05f;
    std::srand(std::time(nullptr));
    int factor = rand()%10;
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        //glClearColor(0.0f, 1.f, 0.0f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
         if (x > 1.0f || y > 1.0f || z > 1.0f )
            increment = -0.05f;
        if( x < 0.0f || y < 0.0f || z < 0.0f )
            increment = 0.05f;

        x += factor * increment;
        std::srand(std::time(nullptr));
        factor = rand()%10;
        y += factor * increment;
        std::srand(std::time(nullptr));
        factor = rand()%10;
        z += factor * increment;
        glCall(glUniform4f(location, x, y, z, 1.0f));
        glCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
        // glfw: terminate, clearing all previously allocated GLFWresources.
        //---------------------------------------------------------------
    glfwTerminate();
    return 0;
}
