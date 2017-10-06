#pragma once
#include <vector>
#include "Scene.h"
#include "Agent.h"

class SceneKinematicFlee :
	public Scene
{
public:
	SceneKinematicFlee();
	~SceneKinematicFlee();
	void update(float dtime, SDL_Event *event);
	void draw();
	void debugDraw();
	const char* getTitle();
	void changeDebugMode();
private:
	std::vector<Agent*> agents;
	Vector2D target;
	Vector2D steering_force;
};

