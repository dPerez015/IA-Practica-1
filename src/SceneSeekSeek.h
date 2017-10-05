#pragma once
#include <vector>
#include "Scene.h"
#include "Agent.h"

class SceneSeekSeek :
	public Scene
{
public:
	SceneSeekSeek();
	~SceneSeekSeek();
	void update(float dtime, SDL_Event *event);
	void draw();
	void changeDebugMode();
	const char* getTitle();
private:
	std::vector<Agent*> agents;
	Vector2D target;
};

