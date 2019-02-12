#include "Game1.h"



Game1::Game1()
{
}


Game1::~Game1()
{
	delete model;
	model = nullptr;

	delete object1;
	object1 = nullptr;
	
}

bool Game1::Initialize() {
	Camera::GetInstance()->SetPosition(glm::vec3(0.0f, 0.0f, 10.0f));
	Camera::GetInstance()->AddLightSource(new LightSource(glm::vec3(0.0f, 0.0f, 2.0f), 0.1f, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f)));

	CollisionHandler::GetInstance()->Initialize(100.0f);

	Model* Apple = new Model("Resources/Models/Apple.obj", "Resources/Materials/Apple.mtl", ShaderHandler::GetInstance()->GetShader("baseShader"));
	Model* Dice = new Model("Resources/Models/Dice.obj", "Resources/Materials/Dice.mtl", ShaderHandler::GetInstance()->GetShader("baseShader"));
	SceneGraph::GetInstance()->AddModel(Apple);
	SceneGraph::GetInstance()->AddModel(Dice);

	SceneGraph::GetInstance()->AddGameObject(new GameObject(Apple), "apple1");
	SceneGraph::GetInstance()->AddGameObject(new GameObject(Dice, glm::vec3(3.0f, 0.0f, 0.0f)));



	//SceneGraph::GetInstance()->GetGameObject("apple1")->SetScale(glm::vec3(1.0f));
	SceneGraph::GetInstance()->GetGameObject("apple1")->SetPosition(glm::vec3(0.0f, -1.0f, 1.0f));


	std::cout << "Object's Bounding Box: " << std::endl;
	std::cout << "Min Vert: " << glm::to_string(SceneGraph::GetInstance()->GetGameObject("apple1")->GetBoundingBox().minVert) << std::endl;
	std::cout << "Max vert: " << glm::to_string(SceneGraph::GetInstance()->GetGameObject("apple1")->GetBoundingBox().maxVert) << std::endl;

	return true;
}

void Game1::Update(const float deltaTime_) {
	SceneGraph::GetInstance()->Update(deltaTime_);
}

void Game1::Render() {
	SceneGraph::GetInstance()->Render(Camera::GetInstance());
}
