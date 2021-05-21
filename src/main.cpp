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
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

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
    glfwSwapInterval(20);
        // glad: load all OpenGL function pointers
        // ---------------------------------------
    if (glewInit() != GLEW_OK)
    {
            std::cout << "Failed to initialize GLEW" << std::endl;
            return -1;
    }
     // render loop

    /*
    float position[] = {
            500.0f,200.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, //0
            700.0f,200.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, //1
            700.0f,400.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, //2
            500.0f,400.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  //3
    };
    */

   float position[] = {
            -0.5f,-0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, //0
             0.5f,-0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, //1
             0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, //2
            -0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  //3
    };
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
    layout.Push<float>(3);
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
    /*
    float x = 0.0f, z = 0.0f;
    float y = 1000.0f, w = 760.0f;
    float increment = 100.0f;
    */
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        render.Clear();

        shader.SetUniform4f("u_Color",0.3f, 0.8f, 0.1f, 1.0f);
        /*
        glm::mat4 proj=glm::ortho(x, y, z, w, -1.0f, 1.0f);
        /*
        glm::mat4 view =glm::translate(glm::mat4(1.0f), glm::vec3(-increment,0,0));
        glm::mat4 model = glm::translate(glm::mat4(1.0f),glm::vec3(increment,increment,0));
        glm::mat4 mvp = proj * view * model;
        
    
        shader.SetUniformMat4f("u_MVP", proj);
        */
        render.Draw(va,ib,shader);
        /*
        float timevalue = glfwGetTimerValue();
        float increment = 100.0 * (glm::sin(timevalue));
        if (( y > 1270.0f || w > 750.0f)&&(increment > 0.0))
            increment = -increment;
        if(( y < 50.0f || w < 50.0f) &&(increment < 0.0))
            increment = -increment;
        y += increment;
        w += increment;
        
        glm::mat4 proj=glm::ortho(x, y, z, w, -1.0f, 1.0f);
        shader.SetUniformMat4f("u_MVP", proj);
        */
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    // glfw: terminate, clearing all previously allocated GLFWresources.
    //---------------------------------------------------------------
    glfwTerminate();
    return 0;
}
