#pragma once
#include "Scene.h"
#include "Agent.h"
#include <vector>

class ScenePathFollowing: public Scene
{
public:
	ScenePathFollowing();
	~ScenePathFollowing();

	void update(float dtime, SDL_Event *event);
	void draw();
	const char* getTitle();
	void debugDraw();
	void changeDebugMode();
private:
	std::vector<Agent*> agents;
	std::vector<Vector2D>path;
};