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
#include "Glutil.h"
#include "Camera.h"
#include "Mvp.h"

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
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    glfwSwapInterval(10);
    // glew: load all OpenGL function pointers
    // ---------------------------------------
    if (glewInit() != GLEW_OK)
    {
            std::cout << "Failed to initialize GLEW" << std::endl;
            return -1;
    }
     
    float position[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    /*
    float position[] = {
            200.0f,200.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, //0
            500.0f,200.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, //1
            500.0f,400.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, //2
            200.0f,400.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  //3
    };
    */
   /*
   float position[] = {
            -0.5f,-0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, //0
             0.5f,-0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, //1
             0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, //2
            -0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  //3
    };
    */
    unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
    };

    glEnable(GL_DEPTH_TEST); 
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);   

    VertexArray va;
    VertexBuffer vb(position, sizeof(position));
    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(2);
    va.addBuffer(vb, layout);
    IndexBuffer ib(indices, 6);

    Shader shader("src/shader/Basic.shader");
    shader.Bind();

    Texture texture("src/res/container.jpg", 0);
    shader.SetUniform1i("u_Texture",0);

    Texture text1("src/res/awesomeface.png", 1);
    shader.SetUniform1i("u_Texture1",1);
    
    va.Unbind();
    vb.Unbind();
    ib.Unbind();
    shader.Unbind();
    Render render;
    
    bool arrayDraw = false;
  
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        render.Clear();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        texture.Bind(0);
        text1.Bind(1);
        camera.processKeyControl(window);
        camera.ProcessMouseMovement(xOffset, yOffset, true);
        camera.setZoom(mFov);
        glm::mat4 view= camera.GetViewMatrix(); 
        //setViewwithCamera(view);
        //setViewwithcontrol(view, camera.getPosition(), camera.getFront(), camera.getUp());
        Mvp mvp;
        glm::mat4 proj = mvp.ToProjwithcontrol(camera.getZoom());

        for(unsigned int i = 0; i < 10; i++)
        {
            // calculate the model matrix for each object and pass it to shader before drawing
            
            Mvp mvp;
            glm::mat4 model=mvp.ToModelwithloc(i);
            glm::mat4 trans = proj * view * model;
            shader.SetUniformMat4fv("u_MVP", trans);
            arrayDraw = true;
            render.Draw(va, ib, shader, arrayDraw);
        }
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    // glfw: terminate, clearing all previously allocated GLFWresources.
    //---------------------------------------------------------------
    glfwTerminate();
    return 0;
}
