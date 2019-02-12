#include "Core/Engine.h"
#include "../Game/Game1.h"


int main(int argc, char*argv[]) {

	//Version 1
	/*
	if (!Engine::GetInstance()->Initialize("GAME301 Engine", 800, 600)) {
		std::cout << "Engine failed to initialize" << std::endl;
	Engine::GetInstance()->Shutdown();
		return 0;	
	}
*/

	//Version 2
	Engine::GetInstance()->SetGameInterface(new Game1());
	Engine::GetInstance()->Initialize("GAME301 Engine", 800, 600);
	Engine::GetInstance()->Run();
	
	return 0;
}