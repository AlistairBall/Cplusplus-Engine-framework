#ifndef GAME1_H
#define GAME1_H

#include "..\Engine\Core\Engine.h"
#include <glm\gtx\string_cast.hpp>


class Game1 : public GameInterface
{
public:
	Game1();
	 virtual ~Game1();
	 virtual bool Initialize();
	 virtual void Update(const float deltaTime_);
	 virtual void Render();
private:
	Model * model;
	GameObject* object1;
	
};

#endif // !GAME1_H

