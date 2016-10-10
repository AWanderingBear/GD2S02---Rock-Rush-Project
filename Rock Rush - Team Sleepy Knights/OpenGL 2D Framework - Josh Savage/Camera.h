#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glfw3.h>

#include "Util.h"

class Camera
{
public:
	Camera(float cameraSpeed, glm::vec3 cameraPos, glm::vec3 cameraTarget, glm::vec3 up, GLFWwindow* pWindow);
	~Camera();

	void Update();

	glm::mat4 GetView();
	glm::mat4 GetProjection();

	void UpdateProjection(); // Projection only update on window resize so we'll do this manually if the window is resized
	void SetSpeed(float cameraSpeed);

	void Movement(int key);

	glm::vec2 ScreenToBox2D(glm::vec2 mousepos);

	float getDeltaTime();

private:

	glm::vec3 m_Position;
	
	glm::vec3 m_Target;
	glm::vec3 m_Front;

	glm::vec3 m_CameraUp;
	glm::vec3 m_CameraRight;

	glm::mat4 m_View;
	glm::mat4 m_Projection;

	GLFWwindow* m_pWindow;
	int screenHeight;
	int screenWidth;

	float m_Speed;

	GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
	GLfloat lastFrame = 0.0f;  	// Time of last frame
};

