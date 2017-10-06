#pragma once
#include <vector>
#include "Scene.h"
#include "Agent.h"

class SceneSeek :
	public Scene
{
public:
	SceneSeek();
	~SceneSeek();
	void update(float dtime, SDL_Event *event);
	void draw();
	void debugDraw();
	void changeDebugMode();
	const char* getTitle();
private:
	std::vector<Agent*> agents;
	Vector2D target;
};

