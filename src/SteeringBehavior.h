#pragma once
#include "Agent.h"
#include "Vector2D.h"

class Agent;

class SteeringBehavior
{
private:
	Vector2D desiredVel;
	Vector2D steeringForce;
public:
	SteeringBehavior();
	~SteeringBehavior();
	Vector2D KinematicSeek(Agent *agent, Vector2D target, float dtime);
	Vector2D KinematicSeek(Agent *agent, Agent *target, float dtime);
	Vector2D KinematicFlee(Agent *agent, Vector2D target, float dtime);
	Vector2D KinematicFlee(Agent *agent, Agent *target, float dtime);

	/* Add here your own Steering Behavior functions declarations */
	Vector2D Seek(Agent *agent, Vector2D target, float dtime);
	Vector2D Seek(Agent *agent, Agent *target, float dtime);
	Vector2D Flee(Agent *agent, Vector2D target, float dtime);
	Vector2D Flee(Agent *agent, Agent *target, float dtime);
	//etc...

	Vector2D Arrive(Agent* agent, Vector2D target, float slowingRadius, float dt);
	Vector2D Pursue(Agent* agent, Agent* target, float dt);
	Vector2D Wander(Agent* agent, float angle, float* wanderAngle, int wanderMaxChange,int wanderCircleOffset, int wanderCircleRadius, float dt);
	Vector2D Avoid(Agent* agent, Vector2D target, float perimeterBorder, float dt);
	
	//Behaviour combination
	Vector2D Combination(Agent * agent, Vector2D target1, Vector2D target2, float dt);

};
