#include "Glutil.h"
#include "glm/glm.hpp"
#include "Render.h"


glm::vec3 cubePositions[] = {
    glm::vec3( 0.0f,  0.0f,  0.0f), 
    glm::vec3( 2.0f,  5.0f, -15.0f), 
    glm::vec3(-1.5f, -2.2f, -2.5f),  
    glm::vec3(-3.8f, -2.0f, -12.3f),  
    glm::vec3( 2.4f, -0.4f, -3.5f),  
    glm::vec3(-1.7f,  3.0f, -7.5f),  
    glm::vec3( 1.3f, -2.0f, -2.5f),  
    glm::vec3( 1.5f,  2.0f, -2.5f), 
    glm::vec3( 1.5f,  0.2f, -1.5f), 
    glm::vec3(-1.3f,  1.0f, -1.5f)  
};

bool firstMouse = true;
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
float fov   =  45.0f;
float xOffset = SCR_WIDTH / 2.0f;
float yOffset = SCR_HEIGHT / 2.0f;


// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{   
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    xOffset = xpos - lastX;
    yOffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
    lastX = xpos;
    lastY = ypos;
}


// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    fov -= (float)yoffset;
    if (fov < 1.0f)
        fov = 1.0f;
    if (fov > 45.0f)
        fov = 45.0f;
}



void setViewwithCamera(glm::mat4& view)
{
        view = glm::mat4(1.0f);
        // camera/view transformation
        const float radius = 10.0f;
        float camX = sin(glfwGetTime()) * radius;
        float camZ = cos(glfwGetTime()) * radius;
        view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0)); 
}

void setViewwithcontrol(glm::mat4& view, glm::vec3 aPos, glm::vec3 aFront, glm::vec3 aUp)
{

        view = glm::mat4(1.0f);
        // camera/view transformation
        view = glm::lookAt(aPos, aPos + aFront, aUp);
}

void setViewReverse(glm::mat4& view)
{
    view = glm::mat4(1.0f);
    // note that we're translating the scene in the reverse direction of where we want to move
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f)); 
}

void setProj(glm::mat4& proj)
{
    proj = glm::mat4(1.0f);
    proj = glm::perspective(glm::radians(45.0f), (float)(SCR_WIDTH/SCR_HEIGHT), 0.1f, 100.0f);
}

void setProjwithcontrol(glm::mat4& proj, float angle)
{
    proj = glm::mat4(1.0f);
    proj = glm::perspective(glm::radians(angle), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
}


void setModelwithloc(glm::mat4& model, unsigned int i)
{
        model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        model = glm::translate(model, cubePositions[i]);
        float angle = 20.0f * i;
        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));

}

void setModelwithrotate(glm::mat4& model)
{
    model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
}