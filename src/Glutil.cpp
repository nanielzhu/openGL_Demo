#include "Glutil.h"
#include "glm/glm.hpp"
#include <iostream>
#include "Render.h"


bool firstMouse = true;
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
float mFov   =  45.0f;
float xOffset = 0;
float yOffset = 0;

void glClearError()
{
    while(glGetError() != GL_NO_ERROR );
}


bool glCheckError(const char* func, const char* file, int line)
{
    while(GLenum error = glGetError())
    {
        std::cout << "openGL meet error:"<<error<<"in function:"<<func<<"; and file :"<<file<<";line::"<<line<<std::endl;
        return false;
    }
    return true;
}


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
    mFov -= (float)yoffset;
    if (mFov < 1.0f)
        mFov = 1.0f;
    if (mFov > 45.0f)
        mFov = 45.0f;
}
