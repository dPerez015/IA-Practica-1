#pragma once
#include "Scene.h"
#include "Agent.h"

class SceneAvoidance :
	public Scene
{
public:
	SceneAvoidance();
	~SceneAvoidance();
	Vector2D Avoid(Agent *agent, Vector2D target, float dtime);
	Vector2D Avoid(Agent *agent, Agent *target, float dtime);
	void update(float dtime, SDL_Event *event);
	void draw();
	const char*getTitle();
	void changeDebugMode();
private:
	std::vector<Agent*> agents;
	Vector2D target;
	float perimeterBorder;
};
