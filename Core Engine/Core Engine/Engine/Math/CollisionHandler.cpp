#include "CollisionHandler.h"
#include "../Core/Engine.h"

std::unique_ptr<CollisionHandler> CollisionHandler::collisionInstance = nullptr;



std::vector<GameObject*> CollisionHandler::colliders = std::vector<GameObject*>();
 std::vector<GameObject*> CollisionHandler::previousCollisions = std::vector<GameObject*>();

CollisionHandler::CollisionHandler()
{

}


CollisionHandler::~CollisionHandler()
{
	if (colliders.size() > 0) {
		for (auto g : colliders) {
			g = nullptr;
		}
		colliders.clear();
		colliders.shrink_to_fit();
	}
}

CollisionHandler * CollisionHandler::GetInstance()
{
	if (collisionInstance.get() == nullptr) {
		collisionInstance.reset(new CollisionHandler);
	}
	return collisionInstance.get();
}

void CollisionHandler::Initialize(float worldSize_)
{
	previousCollisions.clear();
	previousCollisions.shrink_to_fit();

//	colliders.clear();
	//colliders.shrink_to_fit();
	
	scenePartition = new OctSpacialPartition(worldSize_);
}

void CollisionHandler::AddObject(GameObject * go_)
{
	scenePartition->AddObject(go_);
	//colliders.push_back(go_);
}

void CollisionHandler::Update(glm::vec2 mousePosition_, int buttonType_)
{



	Ray ray = CollisionDetection::ScreenToWorldRay(mousePosition_, Engine::GetInstance()->GetScreenSize());
	GameObject* obj = scenePartition->GetCollision(ray);
	

	

	if (obj) {
		obj->SetHit(true, buttonType_);
	}

	for (auto c : previousCollisions) {
		if (obj != c && c != nullptr) {
			c->SetHit(false, buttonType_);
			c = nullptr;
		}
	}
	previousCollisions.clear();

	if (obj) {
		previousCollisions.push_back(obj);
	}



}
