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
    glfwSwapInterval(10);
        // glad: load all OpenGL function pointers
        // ---------------------------------------
    if (glewInit() != GLEW_OK)
    {
            std::cout << "Failed to initialize GLEW" << std::endl;
            return -1;
    }
     

    /*
    float position[] = {
            200.0f,200.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, //0
            500.0f,200.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, //1
            500.0f,400.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, //2
            200.0f,400.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  //3
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
    //shader.SetUniform4f("u_Color", 0.3f, 0.8f, 0.1f, 1.0f);

    Texture texture("src/res/container.jpg", 0);
    shader.SetUniform1i("u_Texture",0);

    Texture text1("src/res/awesomeface.png", 1);
    shader.SetUniform1i("u_Texture1",1);
    
    va.Unbind();
    vb.Unbind();
    ib.Unbind();
    shader.Unbind();
    Render render;
    
    /*
    float x = 0.0f, z = 0.0f;
    float y = 1000.0f, w = 760.0f;
    */

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        render.Clear();
    
        texture.Bind(0);
        text1.Bind(1);

        /*
        glm::mat4 proj=glm::ortho(x, y, z, w, -1.0f, 1.0f);
        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::translate(trans, glm::vec3(0.1f, -0.1f, 0.0f));
        trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        */
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f)); 
        glm::mat4 view = glm::mat4(1.0f);
        // note that we're translating the scene in the reverse direction of where we want to move
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f)); 
        glm::mat4 proj;
        proj = glm::perspective(glm::radians(45.0f), (float)(SCR_WIDTH/SCR_HEIGHT), 0.1f, 100.0f);
        glm::mat4 trans = proj * view * model;

        shader.SetUniformMat4fv("u_MVP", trans);
        
        render.Draw(va,ib,shader);
      
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    // glfw: terminate, clearing all previously allocated GLFWresources.
    //---------------------------------------------------------------
    glfwTerminate();
    return 0;
}
