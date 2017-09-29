#pragma once
#include <vector>
#include "Scene.h"
#include "Agent.h"

class SceneArrival :
	public Scene
{
public:
	SceneArrival();
	~SceneArrival();
	Vector2D Arrive(Agent *agent, Vector2D target, float slowingRadius, float dtime);
	Vector2D Arrive(Agent *agent, Agent *target, float slowingRadius, float dtime);
	void update(float dtime, SDL_Event *event);
	void draw();
	const char* getTitle();
private:
	std::vector<Agent*> agents;
	Vector2D target;
};

