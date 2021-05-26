#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
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
#include "Global.h"
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
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    glfwSwapInterval(2);
    // glew: load all OpenGL function pointers
    // ---------------------------------------
    if (glewInit() != GLEW_OK)
    {
            std::cout << "Failed to initialize GLEW" << std::endl;
            return -1;
    }

    glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

    glEnable(GL_DEPTH_TEST); 
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);   

    VertexArray cubeVAO;
    VertexBuffer vb(Vertices4Light, sizeof(Vertices4Light));
    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(3);
    cubeVAO.addBuffer(vb, layout);

    VertexArray lightVAO;
    lightVAO.addBuffer(vb,layout);

    Shader cubeshader("src/shader/Cube.vs", "src/shader/Cube.fs");
    Shader lightshader("src/shader/Light.vs", "src/shader/Light.fs");
    
    lightVAO.Unbind();
    cubeVAO.Unbind();
   
    Render render;
    Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
    
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        render.ClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        render.ClearDepth();
        
        camera.ProcessKeyControl(window);
        camera.ProcessMouseMovement(xOffset, yOffset, true);
        camera.ProcessScrollMovement(mFov);
        //Cube Shader begin
        cubeshader.Bind();

        cubeshader.SetUniformVec3("viewPos", camera.getPosition());

        cubeshader.SetUniformVec3("material.ambient", 1.0f, 0.5f, 0.31f);
        cubeshader.SetUniformVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
        cubeshader.SetUniformVec3("material.specular", 0.5f, 0.5f, 0.5f);
        cubeshader.SetUniformVec3("material.shininess", 32.0f);
        cubeshader.SetUniformVec3("light.position", lightPos);

        //setup light 
        glm::vec3 lightColor;
        lightColor.x = sin(glfwGetTime() * 2.0f);
        lightColor.y = sin(glfwGetTime() * 0.7f);
        lightColor.z = sin(glfwGetTime() * 1.3f);
        glm::vec3 diffuseColor = lightColor   * glm::vec3(0.5f); 
        glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f); 
        cubeshader.SetUniformVec3("light.ambient",  ambientColor);
        cubeshader.SetUniformVec3("light.diffuse",  diffuseColor); 
        cubeshader.SetUniformVec3("light.specular", 1.0f, 1.0f, 1.0f); 

        // view/projection transformations
        Mvp mvp;
        glm::mat4 proj =mvp.ToProjwithcontrol(camera.getZoom()); 
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 model = glm::mat4(1.0f);
        cubeshader.SetUniformMat4fv("proj",proj);
        cubeshader.SetUniformMat4fv("view",view);
        cubeshader.SetUniformMat4fv("model",model);
        //glm::mat4 cubetrans = proj * view * model;
        //cubeshader.SetUniformMat4fv("u_MVP",cubetrans);

        // render the cube
        render.Draw(cubeVAO, cubeshader);

         // also draw the lamp object
        lightshader.Bind();
        Mvp lightmvp;
        lightshader.SetUniformVec3("light.ambient",  ambientColor);
        lightshader.SetUniformVec3("light.diffuse",  diffuseColor); 
        lightshader.SetUniformVec3("light.specular", 1.0f, 1.0f, 1.0f);
        glm::mat4 lightmodel = lightmvp.ToModelwithScale(lightPos, 0.3f);
        glm::mat4 lighttrans = proj * view * lightmodel;
        lightshader.SetUniformMat4fv("u_MVP", lighttrans);

        render.Draw(lightVAO, lightshader);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    // glfw: terminate, clearing all previously allocated GLFWresources.
    //---------------------------------------------------------------
    glfwTerminate();
    return 0;
}
