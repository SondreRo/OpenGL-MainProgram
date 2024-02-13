#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include "glad/glad.h"
#include "glm/gtc/type_ptr.hpp"
#include "glm/glm.hpp"
#include "GLFW/glfw3.h"

Camera::Camera()
{
    viewMemoryLocation = NULL;
}

Camera::Camera(unsigned inShaderProgram, AppManager* inAppManager)
{
    viewMemoryLocation = glGetUniformLocation(inShaderProgram, "view");
    projectionlLocation = glGetUniformLocation(inShaderProgram, "projection");

    appManager = inAppManager;
}

void Camera::AddShaderProgramPath(unsigned inShaderProgram)
{
    viewMemoryLocation = glGetUniformLocation(inShaderProgram, "view");
    projectionlLocation = glGetUniformLocation(inShaderProgram, "projection");
}

void Camera::AddAppManager(AppManager* inAppManager)
{
    appManager = inAppManager;
}

void Camera::tick(float DeltaTime)
{
    unsigned int SCR_WIDTH;
    unsigned int SCR_HEIGHT;
    appManager->GetScreenSize(&SCR_WIDTH, &SCR_HEIGHT);
    
    glm::mat4 projection = glm::perspective(glm::radians(Zoom), static_cast<float>(SCR_WIDTH)/static_cast<float>(SCR_HEIGHT), 0.01f, 1000.0f);

    glUniformMatrix4fv(projectionlLocation, 1, GL_FALSE, glm::value_ptr(projection));
    
    glm::mat4 view = glm::lookAt(WorldLocation, WorldLocation + cameraFront, cameraUp);
    glUniformMatrix4fv(viewMemoryLocation, 1, GL_FALSE, glm::value_ptr(view));
}

void Camera::AddMovement(glm::vec3 Direction, float Speed)
{
    WorldLocation += Speed * Direction * cameraSpeed * appManager->GetDeltaTime();
}

void Camera::AddRotation(float mouseX, float mouseY)
{
    if (firstMouse)
    {
        lastX = mouseX;
        lastY = mouseY;
        firstMouse = false;
    }
    float xoffset = mouseX - lastX;
    float yoffset = lastY - mouseY;
    lastX = mouseX;
    lastY = mouseY;
    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;
    yaw += xoffset;
    pitch += yoffset;
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);
    cameraRight = glm::normalize(glm::cross(glm::vec3(0.0f,1.0f,0.0f), cameraFront));

}

void Camera::HandleInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) // Forward
    {
        AddMovement(GetForwardVector(), 1);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) // Backward
    {
        AddMovement(-GetForwardVector(), 1);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) // Left
    {
        AddMovement(GetRightVector(), 1);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) // Right
    {
        AddMovement(-GetRightVector(),1);
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) // Up
    {
        AddMovement(GetUpVector(),1);
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) // Down
    {
        AddMovement(-GetUpVector(),1);
    }




    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        Zoom -= 10 * appManager->GetDeltaTime();
        if (Zoom < 1.0f)
            Zoom = 1.0f;
        if (Zoom > 90.0f)
            Zoom = 90.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        Zoom += 10 * appManager->GetDeltaTime();
        if (Zoom < 1.0f)
            Zoom = 1.0f;
        if (Zoom > 90.0f)
            Zoom = 90.0f;
    }
}

glm::vec3 Camera::GetForwardVector()
{

    return cameraFront;
}

glm::vec3 Camera::GetRightVector()
{
    return cameraRight;
}

glm::vec3 Camera::GetUpVector()
{
    return cameraUp;
}

void Camera::SetLocation(glm::vec3 NewLocation)
{
    WorldLocation = NewLocation + LocalLocation;
}

glm::vec3 Camera::GetLocation()
{
    return WorldLocation;
}

void Camera::SetSpeed(float newSpeed)
{
    if (newSpeed < 0.1)
    {
        newSpeed = 0.1f;
    }
    else if (newSpeed > 100)
    {
        newSpeed = 100;
    }
    cameraSpeed = newSpeed;
}

float Camera::GetSpeed()
{
    return cameraSpeed;
}
