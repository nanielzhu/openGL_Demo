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
    Shader shader("src/shader/Basic.shader");
 
    float x = 0.5f, y = 0.1f, z = 0.2f;
    shader.SetUniform4f("u_Color", x, y, z, 1.0f);
    float increment = 0.05f;
    std::srand(std::time(nullptr));
    int factor = rand()%10;
    Render render;
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        render.Clear();
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
        shader.ChangeColor4f(x, y, z, 1.0f);
        render.Draw(va,ib,shader);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    // glfw: terminate, clearing all previously allocated GLFWresources.
    //---------------------------------------------------------------
    glfwTerminate();
    return 0;
}
