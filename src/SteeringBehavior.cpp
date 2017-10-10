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

Vector2D  SteeringBehavior::Pursue(Agent* agent, Agent* pursued, float dt) {
	float predictedT = Vector2D::Distance(agent->getPosition(), pursued->getPosition()) / agent->getMaxVelocity();
	Vector2D predictedPos = pursued->getPosition() + pursued->getVelocity()*predictedT;
	agent->setTarget(predictedPos);
	return agent->Behavior()->Seek(agent, predictedPos, dt);
}
Vector2D  SteeringBehavior::Wander(Agent* agent, float& wanderAngle, int wanderMaxChange, int wanderCircleOffset, int wanderCircleRadius, float& timeSinceLastChange,float timeToChange, Vector2D& wanderCircleCenter, Vector2D& wanderDisplacementVector, float dt) {
	timeSinceLastChange += dt;

	//vector del centre del cercle respecte l'agent
	wanderCircleCenter = agent->getVelocity().Normalize() * wanderCircleOffset;
	if (timeSinceLastChange > timeToChange) {
		//Displacement force
		wanderDisplacementVector.x = cos(wanderAngle*DEG2RAD) * wanderCircleRadius;
		wanderDisplacementVector.y = sin(wanderAngle*DEG2RAD) * wanderCircleRadius;
		/*float randomnumber = rand();
		float changeangle = (randomnumber / RAND_MAX)*wanderMaxChange;
		changeangle -= wanderMaxChange / 2;

		wanderAngle += changeangle;*/
		wanderAngle += (((float)rand() / RAND_MAX)* wanderMaxChange) - (wanderMaxChange / 2);
		timeSinceLastChange = 0;
	}
	//Calcular WanderForce (suma dels 2 vectors)
	Vector2D wanderForce = wanderCircleCenter + wanderDisplacementVector;


	agent->setTarget(agent->getPosition() + wanderCircleCenter + wanderDisplacementVector);
	//truncate maxForce
	return wanderForce.Truncate(agent->getMaxForce());

}

Vector2D SteeringBehavior::Combination(Agent * agent, Vector2D target1, Vector2D target2, float w1, float w2, float dt) {
	steeringForce = Arrive(agent, target1, 150, dt)*w1 + Flee(agent, target2, dt)*w2;
	return steeringForce;
};

Vector2D SteeringBehavior::Avoid(Agent* agent, Vector2D target, float perimeterBorder, float dt) {
	desiredVel = target - agent->getPosition();

	if (agent->getPosition().x < perimeterBorder) {
		desiredVel.x = agent->getMaxVelocity();
	}
	else if (agent->getPosition().x > TheApp::Instance()->getWinSize().x - perimeterBorder) {
		desiredVel.x = -agent->getMaxVelocity();
	}
	if (agent->getPosition().y < perimeterBorder) {
		desiredVel.y = agent->getMaxVelocity();
	}
	else if (agent->getPosition().y > TheApp::Instance()->getWinSize().y - perimeterBorder) {
		desiredVel.y = -agent->getMaxVelocity();
	}
	if (desiredVel.Length() > 0.f) {
		steeringForce = desiredVel - agent->getVelocity();
		steeringForce.Truncate(agent->getMaxForce());
	}
	return steeringForce;
}
