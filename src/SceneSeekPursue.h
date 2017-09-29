#pragma once
#include <vector>
#include "Scene.h"
#include "Agent.h"

class SceneSeekPursue :
	public Scene
{
public:
	SceneSeekPursue();
	~SceneSeekPursue();
	void update(float dtime, SDL_Event *event);
	void draw();
	const char* getTitle();
private:
	Vector2D Pursue(Agent* agent, Agent* pursued, float dt);
	std::vector<Agent*> agents;
	Vector2D target;
};

