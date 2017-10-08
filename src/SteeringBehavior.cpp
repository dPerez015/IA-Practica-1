#include "SteeringBehavior.h"



SteeringBehavior::SteeringBehavior()
{
}


SteeringBehavior::~SteeringBehavior()
{
}

Vector2D SteeringBehavior::KinematicSeek(Agent *agent, Vector2D target, float dtime)
{
	Vector2D steering = target - agent->position;
	steering.Normalize();
	return steering * agent->max_velocity;
}

Vector2D SteeringBehavior::KinematicSeek(Agent *agent, Agent *target, float dtime)
{
	return KinematicSeek(agent, target->position, dtime);
}

Vector2D SteeringBehavior::KinematicFlee(Agent *agent, Vector2D target, float dtime)
{
	Vector2D steering = agent->position - target;
	steering.Normalize();
	return steering * agent->max_velocity;
}

Vector2D SteeringBehavior::KinematicFlee(Agent *agent, Agent *target, float dtime)
{
	return KinematicFlee(agent, target->position, dtime);
}

/* Add here your own Steering Behavior functions definitions */

Vector2D SteeringBehavior::Seek(Agent *agent, Vector2D target, float dtime)
{
	desiredVel = target - agent->position;
	desiredVel = desiredVel.Normalize()*agent->max_velocity;
	steeringForce = desiredVel - agent->velocity;
	//steeringForce /= agent->max_velocity;
	//return steeringForce.Normalize()*agent->max_force;
	return steeringForce.Truncate(agent->max_force);
}

Vector2D SteeringBehavior::Seek(Agent *agent, Agent *target, float dtime)
{
	return Seek(agent, target->position, dtime);
}

Vector2D SteeringBehavior::Flee(Agent *agent, Vector2D target, float dtime)
{
	desiredVel = agent->position - target;
	desiredVel = desiredVel.Normalize()*agent->max_velocity;
	steeringForce = desiredVel - agent->velocity;
	//steeringForce /= agent->max_velocity;
	return steeringForce.Truncate(agent->max_force);
}

Vector2D SteeringBehavior::Flee(Agent *agent, Agent *target, float dtime)
{
	return Flee(agent, target->position, dtime);
}

Vector2D  SteeringBehavior::Arrive(Agent* agent, Vector2D target, float slowingRadius, float dt) {
	Vector2D desiredVel;
	Vector2D steeringForce;
	float distance;
	desiredVel = target - agent->getPosition();
	distance = desiredVel.Length();

	if (distance < slowingRadius) {
		desiredVel = desiredVel.Normalize()*agent->getMaxVelocity()*(distance / slowingRadius);
	}
	else {
		desiredVel = desiredVel.Normalize()*agent->getMaxVelocity();
	}

	steeringForce = desiredVel - agent->getVelocity();
	return steeringForce.Truncate(agent->getMaxForce());
}
Vector2D  SteeringBehavior::Arrive(Agent* agent, Agent* target, int radius, float dt){
	return Vector2D(0, 0);
}
Vector2D  SteeringBehavior::Pursue(Agent* agent, Vector2D target, float dt) {
	return Vector2D(0, 0);
}
Vector2D  SteeringBehavior::Pursue(Agent* agent, Agent* pursued, float dt) {
	float predictedT = Vector2D::Distance(agent->getPosition(), pursued->getPosition()) / agent->getMaxVelocity();
	Vector2D predictedPos = pursued->getPosition() + pursued->getVelocity()*predictedT;
	agent->setTarget(predictedPos);
	return agent->Behavior()->Seek(agent, predictedPos, dt);
}
Vector2D  SteeringBehavior::Wander(Agent* agent, float angle, float* wanderAngle, int wanderMaxChange, int wanderCircleOffset, int wanderCircleRadius, float dt) {
	return Vector2D(0, 0);

}
