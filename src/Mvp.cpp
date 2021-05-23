#include "Mvp.h"
#include "Render.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm/gtc/matrix_transform.hpp"

void Mvp::setViewwithMovingCam()
{
        // camera/view transformation
        const float radius = 10.0f;
        float camX = sin(glfwGetTime()) * radius;
        float camZ = cos(glfwGetTime()) * radius;
        mMvp = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0)); 
}

void Mvp::setViewwithcontrol(glm::vec3 aPos, glm::vec3 aFront, glm::vec3 aUp)
{
        mMvp = glm::lookAt(aPos, aPos + aFront, aUp);
}

void Mvp::setViewReverse()
{
        mMvp = glm::translate(mMvp, glm::vec3(0.0f, 0.0f, -3.0f)); 
}
void Mvp::setProj()
{
        mMvp = glm::perspective(glm::radians(45.0f), (float)(SCR_WIDTH/SCR_HEIGHT), 0.1f, 100.0f);
}
void Mvp::setProjwithcontrol(float angle)
{

        mMvp = glm::perspective(glm::radians(angle), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

}
void Mvp::setModelwithloc(unsigned int i)
{
        mMvp = glm::translate(mMvp, cubePositions[i]);
        float angle = 20.0f * i;
        mMvp = glm::rotate(mMvp, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
}
void Mvp::setModelwithrotate()
{
        mMvp = glm::rotate(mMvp, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
}