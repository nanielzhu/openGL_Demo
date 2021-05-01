#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>

#define ASSERT(func) if(!(func)) __debugbreak();
#define glCall(func) glClearError();\
                    func;\
                    ASSERT(glCheckError(#func, __FILE__,__LINE__))

using namespace std;

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
struct ShaderSource {
    string vertexsource;
    string fragmentsource;
};

static void glClearError()
{
    while(glGetError() != GL_NO_ERROR );
};

static bool glCheckError(const char* func, const char* file, int line)
{
    while(GLenum error = glGetError())
    {
        cout << "openGL meet error:"<<error<<"in function:"<<func<<"; and file :"<<file<<";line::"<<line<<endl;
        return false;
    }
    return true;
};

static ShaderSource ParseShader(const string& filepath)
{
    ifstream stream(filepath,ifstream::in);
    if(!stream.is_open())
        cout<<"error to open file"<<endl;
    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };
    string line;
    stringstream  ss[2];
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line))
    {
        if(line.find("#shader") != string::npos)
        {

            if(line.find("vertex") != string::npos)
            {
                type = ShaderType::VERTEX;
            } else if(line.find("fragment") != string::npos)
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
static unsigned int CompileShader(unsigned int type, const string& source) 
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
        cout << "Failed to compile " <<
        (type == GL_VERTEX_SHADER? "Vertex":"Fragment")<<" Shader"<<endl;
        cout<<message<<endl;
        glDeleteShader(id);
        return 0;
    }
    return id;
}

static unsigned int CreateShader(const string& vertexshader, const string& fragmentshader)
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
int main()
{
        GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(2);
        // glad: load all OpenGL function pointers
        // ---------------------------------------
    if (glewInit() != GLEW_OK)
    {
            std::cout << "Failed to initialize GLAD" << std::endl;
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


    unsigned int Buffer;
    glGenBuffers(1,&Buffer);
    glBindBuffer(GL_ARRAY_BUFFER, Buffer);
    glBufferData(GL_ARRAY_BUFFER,6*2*sizeof(float),position, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), 0);

    unsigned int ibo;
    glGenBuffers(1,&ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

    ShaderSource source = ParseShader("src/shader/Basic.shader");
    unsigned int shader = CreateShader(source.vertexsource,source.fragmentsource);
    glUseProgram(shader);
    glCall(int location = glGetUniformLocation(shader, "u_Color"));
    ASSERT( location != -1);
//    glCall(glUniform4f(location, 0.2f, 0.3f, 0.8f, 1.0f));
    float x = 0.5f, y = 0.1f, z = 0.2f;
    float increment = 0.01f;
    std::srand(std::time(nullptr));
    int factor = rand()%10;
    while (!glfwWindowShouldClose(window))
    {
        //glClearColor(0.0f, 1.f, 0.0f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
 //      glDrawArrays(GL_TRIANGLES, 0, 3);
         if (x >= 1.0f || y > 1.0f || z > 1.0f )
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
