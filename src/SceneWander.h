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
	Vector2D Wander(Agent* agent, float angle, float& wanderAngle, int wanderMaxChange, int wanderCircleOffset, int wanderCircleRadius, float dt);
	void update(float dtime, SDL_Event *event);
	void draw();
	const char* getTitle();
private:
	std::vector<Agent*> agents;
	Vector2D target;
public:
	// Wander fields
	int wanderMaxChange = 50;
	int wanderCircleOffset = 80;
	int wanderCircleRadius = 70;
	float wanderAngle = 0.0f;
	Vector2D wanderCircleCenter = {};
	Vector2D wanderDisplacementVector = {};
};

