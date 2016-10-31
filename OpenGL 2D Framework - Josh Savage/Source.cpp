//NOTES TO JOSH:
/*
Special Meteors and normal meteors are the exact same thing, 
but normal meteors have type 3 and special are type 4. You shouldnt be able to pick up more than one
meteor at a time. Both have spawn functions in the Game class, hopefully this should get you started 
on being able to do stuff with them.
*/

//Include windows first if needed because the SDK is dumb
#ifdef _WIN32
#include <Windows.h>
#endif // !_WIN32
#include <iostream>
#include <vector>
#include <map>

//GLEW Includes
#define GLEW_STATIC
#include <glew.h>

//GLFW Includes
#include <glfw3.h>

//Local Includes
#include "ShaderLoader.h"
#include "Game.h"
#include "Player.h"

//Global Variables
std::map<std::string, GLuint> ProgramManager;

Game* Test;


GLFWwindow* _pWindow;

bool keys[1024];

//Checks to see if these keys are held; in our game we only ever want to tap these,
//So we'll disallow these keys to be sent through until they have been released.
bool upReleased;
bool downReleased;
bool uReleased;
bool jReleased;

double mousex = 0, mousey = 0;

//Input Handling
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (key == GLFW_KEY_F1 && action == GLFW_PRESS) {

		Test = new Game(_pWindow);
		Test->Initialise();
	}

	if (action == GLFW_PRESS)
		keys[key] = true;
	else if (action == GLFW_RELEASE)
		keys[key] = false;
}

//Mouse Button Handling
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {

	if (button == GLFW_MOUSE_BUTTON_1 && action == GLFW_PRESS) {

		Test->HandleClick(glm::vec2(mousex, mousey));
	}
	if (button == GLFW_MOUSE_BUTTON_1 && action == GLFW_RELEASE) {

		Test->HandleRelease();
	}
}

//Cursor position tracking
void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos) {

	mousex = xpos;
	mousey = ypos;

	Test->HandleMove(glm::vec2(xpos, ypos));
}

void VertexInit() {

	Test = new Game(_pWindow);
	Test->Initialise();
}

//Keyboard Input handling
void HandleInput() {

	Camera* CurrentCamera = Test->GetCurrentScene()->GetCamera();

	if (keys[GLFW_KEY_W] && upReleased)
	{
		Test->HandleKeyInput(GLFW_KEY_W);
		upReleased = false;
	}
	else if (!keys[GLFW_KEY_W])
	{
		upReleased = true;
	}

	if (keys[GLFW_KEY_S] && downReleased)
	{
		Test->HandleKeyInput(GLFW_KEY_S);
		downReleased = false;
	}
	else if (!keys[GLFW_KEY_S])
	{
		downReleased = true;
	}

	if (keys[GLFW_KEY_A])
		Test->HandleKeyInput(GLFW_KEY_A);
	if (keys[GLFW_KEY_D])
		Test->HandleKeyInput(GLFW_KEY_D);

	if (keys[GLFW_KEY_I] && uReleased)
	{
		Test->HandleKeyInput(GLFW_KEY_I);
		uReleased = false;
	}
	else if (!keys[GLFW_KEY_I])
	{
		uReleased = true;
	}

	if (keys[GLFW_KEY_K] && jReleased)
	{
		Test->HandleKeyInput(GLFW_KEY_K);
		jReleased = false;
	}
	else if (!keys[GLFW_KEY_K])
	{
		jReleased = true;
	}
	if (keys[GLFW_KEY_J])
		Test->HandleKeyInput(GLFW_KEY_J);
	if (keys[GLFW_KEY_L])
		Test->HandleKeyInput(GLFW_KEY_L);

	if (keys[GLFW_KEY_ENTER])
		Test->HandleKeyInput(GLFW_KEY_ENTER);

}

//Updates
void UpdateMain() {

	HandleInput();
	Test->Update();
}


//Program Entry Point
int main() 
{
	//+++ Window Creation +++
	//Window Initialisation for GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Sets OpenGL version num as 3.0
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // Sets second part of version num making it 3.3

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //Sets the window to use OpenGL
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE); //Makes the window not resizable

	//Window Creation for GLFW 
	_pWindow = glfwCreateWindow(1366, 762, "3D Framework", nullptr, nullptr);
	//Width, Height, Name, ?, ?

	//If the window isn't created properly then throw some errors
	if (_pWindow == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	//Set window to be the current window
	glfwMakeContextCurrent(_pWindow);


	//+++ GLEW Setup +++
	glewExperimental = GL_TRUE; //Setting GLEW to use extended functionality
	if (glewInit() != GLEW_OK) { // Error handling in case we can't initialise GLEW

		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}


	//+++ OpenGL Setup +++
	int _iWidth, _iHeight;
	glfwGetFramebufferSize(_pWindow, &_iWidth, &_iHeight); //Getting Window Size to pass to GL viewport

	glViewport(0, 0, _iWidth, _iHeight); //Setting up the viewport dimensions
	// This is used to convert Screen points to World points and Vice Versa
	glEnable(GL_DEPTH_TEST);

	//+++ Input Setup +++
	glfwSetKeyCallback(_pWindow, key_callback);
	glfwSetCursorPosCallback(_pWindow, cursor_pos_callback);
//	glfwSetMouseButtonCallback(_pWindow, mouse_button_callback);	//WE NEED TO ENABLE THIS FOR MOUSE CLICKS. It was a cheat way to make objects not selectable.

	VertexInit();

	//Wireframe flag for debug and testing
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//+++ Main Loop +++
	while (!glfwWindowShouldClose(_pWindow)) {

		//Check for any events and handle them
		glfwPollEvents();

		//Update Elements and Render
		UpdateMain();

		//Display the rendered buffer to the window
		glfwSwapBuffers(_pWindow);
	}

	//+++ Clean Up +++
	glfwTerminate();

	delete Test;

	return 0;
}