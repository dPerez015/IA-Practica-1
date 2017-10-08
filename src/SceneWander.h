#pragma once
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "Scene.h"
#include "Agent.h"

class SceneWander :
	public Scene
{
public:
	SceneWander();
	~SceneWander();
	Vector2D Wander(Agent* agent, float angle, float& wanderAngle, float wanderMaxChange, int wanderCircleOffset, int wanderCircleRadius, float dt);
	void update(float dtime, SDL_Event *event);
	void draw();
	void changeDebugMode();
	void debugDraw();
	const char* getTitle();
private:
	std::vector<Agent*> agents;
	Vector2D target;
public:
	// Wander fields
	float wanderMaxChange;
	int wanderCircleOffset = 80;
	int wanderCircleRadius = 70;
	float wanderAngle = 0.0f;
	Vector2D wanderCircleCenter = {};
	Vector2D wanderDisplacementVector = {};
};

