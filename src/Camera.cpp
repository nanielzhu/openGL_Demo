#include "Camera.h"

// timing

static float lastFrame = 0.0f;

// constructor with vectors
Camera::Camera(glm::vec3 position, glm::vec3  up, float yaw, float pitch) 
        :mPosition(position),mFront(glm::vec3(0.0f, 0.0f, -1.0f)),mWorldUp(up), mYaw(yaw), mPitch(pitch), 
        mMovementSpeed(SPEED), mMouseSensitivity(SENSITIVITY), mZoom(ZOOM)
{
    updateCameraVectors();
}

// constructor with vectors
Camera::Camera(glm::vec3 position) 
        :mPosition(position),mFront(glm::vec3(0.0f, 0.0f, -1.0f)),mWorldUp(glm::vec3(0.0f, 1.0f, 0.0f)), mYaw(YAW), mPitch(PITCH), 
        mMovementSpeed(SPEED), mMouseSensitivity(SENSITIVITY), mZoom(ZOOM)
{
    updateCameraVectors();
}

// constructor with scalar values
Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) 
        : mFront(glm::vec3(0.0f, 0.0f, -1.0f)),mYaw(yaw), mPitch(pitch),
         mMovementSpeed(SPEED), mMouseSensitivity(SENSITIVITY), mZoom(ZOOM)
{
    mPosition = glm::vec3(posX, posY, posZ);
    mWorldUp = glm::vec3(upX, upY, upZ);
    updateCameraVectors();
}

// returns the view matrix calculated using Euler Angles and the LookAt Matrix
glm::mat4 Camera::GetViewMatrix() const
{
    return glm::lookAt(mPosition, mPosition + mFront, mUp);
}

// processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
void Camera::ProcessKeyboard(Movement direction, float deltaTime)
{
    float velocity = mMovementSpeed * deltaTime;
    if (direction == Camera::FORWARD)
        mPosition += mFront * velocity;
    if (direction == Camera::BACKWARD)
        mPosition -= mFront * velocity;
    if (direction == Camera::LEFT)
        mPosition -= mRight * velocity;
    if (direction == Camera::RIGHT)
        mPosition += mRight * velocity;
}

// processes input received from a mouse input system. Expects the offset value in both the x and y direction.
void Camera::ProcessMouseMovement(float& xoffset, float& yoffset, GLboolean constrain)
{
    xoffset *= mMouseSensitivity;
    yoffset *= mMouseSensitivity;

    mYaw   += xoffset;
    mPitch += yoffset;

    // make sure that when mPitch is out of bounds, screen doesn't get flipped
    if (constrain)
    {
        if (mPitch > 89.0f)
            mPitch = 89.0f;
        if (mPitch < -89.0f)
            mPitch = -89.0f;
    }
    // update mFront, Right and Up Vectors using the updated Euler angles
    updateCameraMove();
}


void Camera::ProcessScrollMovement(float pos)
{
     mZoom = pos;
}

void Camera::updateCameraVectors()
{
        // calculate the new mFront vector
        glm::vec3 front;
        front.x = cos(glm::radians(mYaw)) * cos(glm::radians(mPitch));
        front.y = sin(glm::radians(mPitch));
        front.z = sin(glm::radians(mYaw)) * cos(glm::radians(mPitch));
        mFront = glm::normalize(front);

        // also re-calculate the Right and Up vector
        mRight = glm::normalize(glm::cross(mFront, mWorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        mUp    = glm::normalize(glm::cross(mRight, mFront));
}


void Camera::updateCameraMove()
{
        // calculate the new mFront vector
        glm::vec3 front;
        front.x = cos(glm::radians(mYaw)) * cos(glm::radians(mPitch));
        front.y = sin(glm::radians(mPitch));
        front.z = sin(glm::radians(mYaw)) * cos(glm::radians(mPitch));
        mFront = glm::normalize(front);
}


void Camera::ProcessKeyControl(GLFWwindow *window)
{
    float currentFrame = glfwGetTime();
    float deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    float cameraSpeed = mMovementSpeed * deltaTime; 
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        mPosition +=  mFront * cameraSpeed;
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        mPosition -=  mFront * cameraSpeed;
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        mPosition -= mRight * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        mPosition += mRight * cameraSpeed;
}

