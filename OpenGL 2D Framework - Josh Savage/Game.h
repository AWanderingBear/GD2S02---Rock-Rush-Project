#pragma once
//Global Includes
#include <vector>
#include <map>


//Local Includes
#include "Scene.h"
#include "ShaderLoader.h"
#include "imgui.h"

class Game
{
public:
	Game(GLFWwindow* Window);
	~Game();

	void Initialise();

	void Update();

	void AddScene(Scene* Adding);
	Scene* GetCurrentScene();
	void NextScene();
	void GoToScene(int Scene);

	void HandleClick(glm::vec2 mousePos);
	void HandleRelease();
	void HandleMove(glm::vec2 mousePos);
	void HandleKeyInput(int _key);

	void SpawnSpecialMeteor();
	void SpawnNormalMeteor();

	void DrawScore(int P1Score, int P2Score);

private:

	GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
	GLfloat lastFrame = 0.0f;  	// Time of last frame
	float spawnNormalTimer = 0.0f;

	Scene* LevelOne();
	//Scene* LevelTwo();

	int CurrentScene = 0;

	std::vector<Scene*> Scenes;
	std::map<std::string, GLuint> ProgramManager;
	ShaderLoader ProgramCreator;
	GLFWwindow* m_Window;
};

