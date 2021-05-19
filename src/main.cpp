#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <ctime>
#include "Render.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "Texture.h"

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
    glfwSwapInterval(10);
        // glad: load all OpenGL function pointers
        // ---------------------------------------
    if (glewInit() != GLEW_OK)
    {
            std::cout << "Failed to initialize GLEW" << std::endl;
            return -1;
    }
     // render loop

    float position[] = {
            -0.7f,-0.9f, 0.0f, 0.0f, //0
             0.7f,-0.9f, 1.0f, 0.0f, //1
             0.7f, 0.9f, 1.0f, 1.0f, //2
            -0.7f, 0.9f, 0.0f, 1.0f  //3
    };
    /*
    float position[] = {
            -0.5f,-0.5f, //0
             0.5f,-0.5f, //1
             0.5f, 0.5f, //2
            -0.5f, 0.5f  //3
    };
    */
    unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
    };
//    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
//    glEnable(GL_BLEND);
    VertexArray va;
    VertexBuffer vb(position, sizeof(position));
    VertexBufferLayout layout;
    layout.Push<float>(2);
    layout.Push<float>(2);
    va.addBuffer(vb, layout);
    IndexBuffer ib(indices, 6);

    Shader shader("src/shader/Basic.shader");
    shader.Bind();
    shader.SetUniform4f("u_Color", 0.3f, 0.8f, 0.1f, 1.0f);

    Texture texture("src/res/yuqi.jpg");
    texture.Bind(0);
    shader.SetUniform1i("u_Texture",0);

    va.Unbind();
    vb.Unbind();
    ib.Unbind();
    shader.Unbind();
    Render render;
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        render.Clear();
     //   shader.Bind();
        
        shader.SetUniform4f("u_Color",0.3f, 0.8f, 0.1f, 1.0f);
        
        render.Draw(va,ib,shader);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    // glfw: terminate, clearing all previously allocated GLFWresources.
    //---------------------------------------------------------------
    glfwTerminate();
    return 0;
}
