#include "Game.h"
#include "Shapes.h"
#include "MeteorCollisionHandler.h"

#include <ctime>	//For seeding the random number generator for meteor positions

//REMEMBER ME 
// Box2D uses different units to GL
// Assuming a "bird" is about a metre high in open GL and we want them to be about 25 pixels?
// AKA every box2D meter has to be converted to by multiplying by 25

Game::Game(GLFWwindow * Window)
{
	m_Window = Window;

	srand(time(NULL));	//Something something seed planting.
}

Game::~Game()
{
}

Scene * Game::MainMenu()
{
	Camera* GameCamera = new Camera(600.0f, glm::vec3(-150.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), m_Window);
	Scene* MainMenu = new Scene(GameCamera, this, 3, 2);
	//Background
	MainMenu->AddGameAgent(new GameAgent(ProgramManager["Ortho"], "Assets/Textures/BackgroundSky2.jpg", BackgroundVertices, Indices,
		glm::vec3(1537, 384, -0.1), 0, GameCamera));

	return MainMenu;
}

Scene * Game::GameOver()
{
	Camera* GameCamera = new Camera(600.0f, glm::vec3(-150.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), m_Window);
	Scene* GameOver = new Scene(GameCamera, this, 3, 2);
	//Background
	//GameOver->AddGameAgent(new GameAgent(ProgramManager["Ortho"], "Assets/Textures/BackgroundSky2.jpg", BackgroundVertices, Indices,
	//	glm::vec3(1537, 384, -0.1), 0, GameCamera));

	return GameOver;
}


Scene * Game::LevelOne()
{
	//This method of creation is* horrific and should be handled in the constructor. Note for next time. 

	//Level One
	Camera* GameCamera = new Camera(600.0f, glm::vec3(-150.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), m_Window);
	Scene* LevelOne = new Scene(GameCamera, this, 3, 2);
	LevelOne->GetWorld()->SetContactListener(new MeteorCollisionHandler());

	// Define the ground
	b2BodyDef mainPlatformBodyDef;
	mainPlatformBodyDef.position.Set(20.8f, 20.0f); //*25			//Doesn't affect the way the object looks.
	mainPlatformBodyDef.type = b2_staticBody;
	b2Body* mainPlatformBody = LevelOne->GetWorld()->CreateBody(&mainPlatformBodyDef);
	GameAgent* mainPlatformAgent = new GameAgent(ProgramManager["Ortho"], "Assets/Textures/wall.jpg", mainPlatformVertices, Indices,
		glm::vec3(520, 500, 0), 0, GameCamera, mainPlatformBody, 0);	//DOES affect objects position, but y is oposite
	//Shape the physics body
	b2PolygonShape mainPlatformBox;
	mainPlatformBox.SetAsBox(15.36f, 1.0f);		//Doesnt affect the way the object looks. I have no idea if this is right.
	b2FixtureDef mainPlatformFixture;
	mainPlatformFixture.shape = &mainPlatformBox;
	mainPlatformFixture.userData = mainPlatformBody;
	mainPlatformFixture.friction = 0.0f;
	mainPlatformBody->CreateFixture(&mainPlatformFixture);


	// Define the left starting platform.
	b2BodyDef leftPlatformBodyDef;
	leftPlatformBodyDef.position.Set(-3.2f, 16.0f); //*25			//Doesn't affect the way the object looks.
	leftPlatformBodyDef.type = b2_staticBody;
	b2Body* leftPlatformBody = LevelOne->GetWorld()->CreateBody(&leftPlatformBodyDef);
	GameAgent* leftPlatformAgent = new GameAgent(ProgramManager["Ortho"], "Assets/Textures/wall.jpg", startPlatformVertices, Indices,
		glm::vec3(-80, 400, 0), 0, GameCamera, leftPlatformBody, 0);	//DOES affect objects position, but y is oposite
																		//Shape the physics body
	b2PolygonShape leftPlatformBox;
	leftPlatformBox.SetAsBox(3.08f, 0.2f);		//Doesnt affect the way the object looks. I have no idea if this is right.
	b2FixtureDef leftPlatformFixture;
	leftPlatformFixture.shape = &leftPlatformBox;
	leftPlatformFixture.userData = leftPlatformBody;
	leftPlatformBody->CreateFixture(&leftPlatformFixture);


	// Define the right starting platform.
	b2BodyDef rightPlatformBodyDef;
	rightPlatformBodyDef.position.Set(45.6f, 16.0f); //*25			//Doesn't affect the way the object looks.
	rightPlatformBodyDef.type = b2_staticBody;
	b2Body* rightPlatformBody = LevelOne->GetWorld()->CreateBody(&rightPlatformBodyDef);
	GameAgent* rightPlatformAgent = new GameAgent(ProgramManager["Ortho"], "Assets/Textures/wall.jpg", startPlatformVertices, Indices,
		glm::vec3(1140, 400, 0), 0, GameCamera, rightPlatformBody, 0);	//DOES affect objects position, but y is oposite
																		//Shape the physics body
	b2PolygonShape rightPlatformBox;
	rightPlatformBox.SetAsBox(3.08f, 0.2f);		//Doesnt affect the way the object looks. I have no idea if this is right.
	b2FixtureDef rightPlatformFixture;
	rightPlatformFixture.shape = &rightPlatformBox;
	rightPlatformFixture.userData = rightPlatformBody;
	rightPlatformBody->CreateFixture(&rightPlatformFixture);

	//Define the Box
	b2BodyDef playerZeroBodyDef;
	playerZeroBodyDef.type = b2_dynamicBody;
	playerZeroBodyDef.position.Set(9.0f, 20.0f);	//Cannot set this to negative numbers D:
	playerZeroBodyDef.fixedRotation = true;

	b2Body* playerZeroBody = LevelOne->GetWorld()->CreateBody(&playerZeroBodyDef);

	b2BodyDef playerOneBodyDef;
	playerOneBodyDef.type = b2_dynamicBody;
	playerOneBodyDef.position.Set(33.0f, 20.0f);	//Cannot set this to negative numbers D:
	playerOneBodyDef.fixedRotation = true;
	b2Body* playerOneBody = LevelOne->GetWorld()->CreateBody(&playerOneBodyDef);
	
	Player* pPlayer = new Player(ProgramManager["Ortho"], "Assets/Textures/awesomeface.png", SmallSquareVertices, Indices,
		glm::vec3(0.0, 0.0, 0.0), 0, GameCamera, playerZeroBody /*,1 for collision (Shootables)*/, 1);

	Player* bPlayer = new Player(ProgramManager["Ortho"], "Assets/Textures/hexagon.png", SmallSquareVertices, Indices,
		glm::vec3(0.0, 0.0, 0.0), 0, GameCamera, playerOneBody, 2);


	//Define Shape
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(1.0f, 1.0f);
	//Add Fixture
	b2FixtureDef fixtureDefBox;
	fixtureDefBox.shape = &dynamicBox;
	// Set the box density to be non-zero, so it will be dynamic.
	fixtureDefBox.density = 5.0f;

	b2CircleShape Circle;
	Circle.m_radius = 1.0f;
	b2FixtureDef fixtureDefCircle;
	fixtureDefCircle.shape = &Circle;
	fixtureDefCircle.density = 10.0f;

	float32 angle = 0.0f;
	float32 delta = b2_pi / 3.0f;
	b2Vec2 vertices[6];
	for (int32 i = 0; i < 6; ++i)
	{
		vertices[i].Set(1.0f * cosf(angle), 1.0f * sinf(angle));
		angle += delta;
	}

	b2PolygonShape shape;
	shape.Set(vertices, 6);

	b2FixtureDef fixtureDefTriangle;
	fixtureDefTriangle.shape = &shape;
	fixtureDefTriangle.density = 5.0f;

	//Add fixture to the body

	fixtureDefBox.userData = pPlayer;
	playerZeroBody->CreateFixture(&fixtureDefBox);
	fixtureDefBox.userData = bPlayer;
	playerOneBody->CreateFixture(&fixtureDefBox);

	//Background
	LevelOne->AddGameAgent(new GameAgent(ProgramManager["Ortho"], "Assets/Textures/BackgroundSky2.jpg", BackgroundVertices, Indices, 
		glm::vec3(1537, 384, -0.1), 0, GameCamera));

	////Platforms
	LevelOne->AddGameAgent(mainPlatformAgent);
	LevelOne->AddGameAgent(leftPlatformAgent);
	LevelOne->AddGameAgent(rightPlatformAgent);

	////Player Characters
	LevelOne->AddPlayer(pPlayer);
	LevelOne->AddPlayer(bPlayer); 
	//SpawnSpecialMeteor();

	return LevelOne;
}

void Game::Initialise()
{

	ProgramManager["Ortho"] = ProgramCreator.CreateShader("Shaders/Vertex/OrthoVertexShader.vert", "Shaders/Fragment/TextureFragmentShader.frag");

	Scenes.push_back(MainMenu());
	Scenes.push_back(LevelOne());
	Scenes.push_back(GameOver());

}

void Game::Update()
{
	//Time normalization
	GLfloat currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	if (CurrentScene == 1)
	{

		spawnNormalTimer -= deltaTime;
		if (spawnNormalTimer <= 0.0f)
		{
			SpawnNormalMeteor();
			spawnNormalTimer += 3.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 5.0f - 3.0f));  //Spawns between 3 and 5 seconds. To change change both 3s or the 5.
		}
	}	

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//Setting Clear color
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	//Clearing the window to the set clear color
	glClear(GL_COLOR_BUFFER_BIT);

	Scenes[CurrentScene]->Update();

	//Check if there is a special meteor, if not
	//SpawnSpecialMeteor();
}

void Game::AddScene(Scene* Adding)
{
	Scenes.push_back(Adding);
}

Scene* Game::GetCurrentScene()
{
	return Scenes[CurrentScene];
}

void Game::NextScene()
{

	if (!(CurrentScene == (int) Scenes.size() - 1)) {
		CurrentScene += 1;
	}

}

void Game::GoToScene(int Scene)
{

	if (Scene > 0 && Scene < (int) Scenes.size()) {

		CurrentScene = Scene;
	}
}

void Game::HandleClick(glm::vec2 mousePos)
{
		GetCurrentScene()->HandleClick(mousePos);
}

void Game::HandleRelease()
{
	GetCurrentScene()->HandleRelease();
}

void Game::HandleMove(glm::vec2 mousePos)
{
	GetCurrentScene()->HandleMove(mousePos);
}

void Game::HandleKeyInput(int _key)
{
	int k = _key;
	if (CurrentScene == 0 || CurrentScene == 2)
	{
		GetCurrentScene()->HandleMenuKeyInput(_key);
	}
	if (CurrentScene == 1)
	{
		GetCurrentScene()->HandleKeyInput(_key);
	}
	
}



void Game::SpawnNormalMeteor()
{
	Scene* currentScene = GetCurrentScene();

	float normx = 6.5f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 30.0f - 6.5f));

	//Define the Box
	b2BodyDef meteorBodyDef;
	meteorBodyDef.type = b2_dynamicBody;
	meteorBodyDef.position.Set(normx, 0.0f);

	b2Body* meteorBody = currentScene->GetWorld()->CreateBody(&meteorBodyDef);

	Meteor* meteor = new Meteor(ProgramManager["Ortho"], "Assets/Textures/BombBall.png", SmallSquareVertices, Indices,
		glm::vec3(0.0, 0.0, 0.0), 0, currentScene->GetCamera(), meteorBody /*,1 for collision (Shootables)*/);

	b2CircleShape Circle;
	Circle.m_radius = 1.0f;

	b2FixtureDef fixtureDefCircle;
	fixtureDefCircle.shape = &Circle;
	fixtureDefCircle.density = 10.0f;

	fixtureDefCircle.userData = meteor;
	meteorBody->CreateFixture(&fixtureDefCircle);

	//Change to meteor
	currentScene->AddMeteor(meteor);
}

void Game::SpawnSpecialMeteor()
{
	Scene* currentScene = GetCurrentScene();

	float specialx = 6.5f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 30.0f - 6.5f));

	if (CurrentScene == 1)
	{
		//Define the Box
		b2BodyDef meteorBodyDef;
		meteorBodyDef.type = b2_dynamicBody;
		meteorBodyDef.position.Set(specialx, 0.0f);

		b2Body* meteorBody = currentScene->GetWorld()->CreateBody(&meteorBodyDef);

		SpecialMeteor* specialmeteor = new SpecialMeteor(ProgramManager["Ortho"], "Assets/Textures/robot.png", SmallSquareVertices, Indices,
			glm::vec3(0.0, 0.0, 0.0), 0, currentScene->GetCamera(), meteorBody /*,1 for collision (Shootables)*/);

		b2CircleShape Circle;
		Circle.m_radius = 1.0f;

		b2FixtureDef fixtureDefCircle;
		fixtureDefCircle.shape = &Circle;
		fixtureDefCircle.density = 10.0f;

		fixtureDefCircle.userData = specialmeteor;
		meteorBody->CreateFixture(&fixtureDefCircle);

		//Change to meteor
		currentScene->AddSpecialMeteor(specialmeteor);
	}
}

