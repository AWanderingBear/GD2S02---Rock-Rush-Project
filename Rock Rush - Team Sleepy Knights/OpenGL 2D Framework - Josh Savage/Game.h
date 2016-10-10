#pragma once
//Global Includes
#include <vector>
#include <map>

//Local Includes
#include "Scene.h"
#include "ShaderLoader.h"
#include "Player.h"

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
	void HandleKeyInput();

//	std::vector<TextLabel> vecLabels;

private:

	Scene* LevelOne();
	Scene* LevelTwo();

	int CurrentScene = 0;

	std::vector<Scene*> Scenes;
	std::map<std::string, GLuint> ProgramManager;
	ShaderLoader ProgramCreator;
	GLFWwindow* m_Window;
};

