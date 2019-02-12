#ifndef ENGINE_H
#define ENGINE_H

#include "Timer.h"
#include "Window.h"
#include "GameInterface.h"

#include "../Rendering/3D/Triangle.h"
#include "../Rendering/3D/Square.h"
#include "../Rendering/3D/Cube.h"
#include "../Graphics/ShaderHandler.h"
#include "../Camera/Camera.h"
#include "../Graphics/TextureHandler.h"
#include "../Rendering/3D/GameObject.h"
#include "../Events//EventListener.h"
#include "../Rendering/SceneGraph.h"

#include <memory>


class Engine
{
public:

	Engine(const Engine&) = delete;
	Engine(Engine&&) = delete;
	Engine& operator=(const Engine&) = delete;
	Engine& operator=(Engine&&) = delete;

	


	 bool Initialize(std::string name_, int width_, int height_);
	 void Run();
	 bool GetIsRunning();
	

	static Engine* GetInstance();
	glm::vec2 GetScreenSize() const;
	void SetGameInterface(GameInterface* gameInterface_);

	void NotifyOfMousePressed(int x_, int y_);
	void NotifyOfMouseReleased(int x_, int y_, int buttonType_);
	void NotifyOfMouseMove(int x_, int y_);
	void NotifyOfMouseScroll(int y_);
	void ExitGame();

private:

	Engine();
	~Engine();

	static std::unique_ptr<Engine> engineInstance;
	friend std::default_delete<Engine>;

	void Update(const float deltaTime_);
	void Render();
    void Shutdown();
	

	Window* window;
	bool isRunning;

	Timer timer;
	GameInterface* gameInterface;
	unsigned int fps;




};

#endif 

