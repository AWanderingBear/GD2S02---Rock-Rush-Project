#include "Camera.h"

//GLFW Includes
#include <glfw3.h>
#include <iostream>

Camera::Camera(float cameraSpeed, glm::vec3 cameraPos, glm::vec3 cameraFront, glm::vec3 up, GLFWwindow* pWindow)
{
	m_Speed = cameraSpeed;

	m_Position = cameraPos;
	//m_Target = cameraTarget;
	m_Front = cameraFront;

	m_CameraRight = glm::normalize(glm::cross(up, m_Front));;
	m_CameraUp = glm::cross(m_Front, m_CameraRight);
	m_pWindow = pWindow;

	glfwGetFramebufferSize(m_pWindow, &screenWidth, &screenHeight); //Calculate every frame in case of window resizing
	//m_Projection = glm::perspective(45.0f, (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 100.0f);

	m_Projection = glm::ortho(0.0f, (GLfloat)screenWidth, (GLfloat)screenHeight, 0.0f, -1.0f, 1.0f);
}

Camera::~Camera()
{
}

void Camera::Update()
{
	//Time normalization
	GLfloat currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	m_View = glm::lookAt(m_Position, m_Position + m_Front, m_CameraUp);
}

void Camera::UpdateProjection() {

	glfwGetFramebufferSize(m_pWindow, &screenWidth, &screenHeight); //Calculate every frame in case of window resizing
	m_Projection = glm::ortho(0.0f, (GLfloat)screenWidth, 0.0f, (GLfloat)screenHeight, 0.1f, 100.0f);
}

void Camera::SetSpeed(float cameraSpeed)
{
	m_Speed = cameraSpeed;
}

void Camera::Movement(int key)
{

	GLfloat NormalizedSpeed = m_Speed * deltaTime;

	if (key == GLFW_KEY_A && m_Position.x > -150.0f)
		m_Position += NormalizedSpeed * m_CameraRight ;
	if (key == GLFW_KEY_D)
		m_Position -= NormalizedSpeed * m_CameraRight;

}

glm::vec2 Camera::ScreenToBox2D(glm::vec2 mousepos)
{

	return glm::vec2((mousepos.x + m_Position.x)/25.0, mousepos.y/25.0);
}

glm::mat4 Camera::GetView(){

	return m_View;
}

glm::mat4 Camera::GetProjection()
{
	return m_Projection;
}