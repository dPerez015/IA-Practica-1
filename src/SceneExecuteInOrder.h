#pragma once
#include "Scene.h"
#include "Agent.h"

class SceneExecuteInOrder :
	public Scene
{
public:
	SceneExecuteInOrder();
	~SceneExecuteInOrder();
	Vector2D ExecuteInOrder(Agent *agent, Vector2D target, float dtime);
	Vector2D ExecuteInOrder(Agent *agent, Agent *tarfet, float dtime);
	Vector2D WeighedSum(Agent* agent, Vector2D target);
	void update(float dtime, SDL_Event *event);
	void draw();
	const char*getTitle();
	void changeDebugMode();
private:
	std::vector<Agent*> agents;
	Vector2D target;
	std::vector<float> weights;
};