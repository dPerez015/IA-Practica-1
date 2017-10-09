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
	//void debugDraw();
	void changeDebugMode();
	bool checkDistance(Vector2D, Vector2D, float);
	int searchNearTarget();
	void checkPathState();
	void changeAgentTarget(Agent*, std::vector<Vector2D>&, int&, int&, int);
private:
	std::vector<Agent*> agents;
	std::vector<Vector2D>path;
	float detectionRadius;
	bool agentOnTarget;
	int currentTarget;
	int pathCurrentDirection;
	float lastTimeTargetSeted;
	float timeToTarget;
};