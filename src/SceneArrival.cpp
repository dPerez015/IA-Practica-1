#include "SceneArrival.h"

using namespace std;

SceneArrival::SceneArrival()
{
	Agent *agent = new Agent;
	agent->setPosition(Vector2D(640,360));
	agent->setTarget(Vector2D(640, 360));
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agents.push_back(agent);
	target = Vector2D(640, 360);
	radius = 100.f;
	debugMode = true;
}

SceneArrival::~SceneArrival()
{
	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
}

Vector2D SceneArrival::Arrive(Agent *agent, Vector2D target, float slowingRadius, float dtime){
	Vector2D desiredVel;
	Vector2D steeringForce;
	float distance;
	desiredVel = target - agent->getPosition();
	distance = desiredVel.Length();

	if (distance < slowingRadius) {
		desiredVel = desiredVel.Normalize()*agent->getMaxVelocity()*(distance/slowingRadius);
	}
	else {
		desiredVel = desiredVel.Normalize()*agent->getMaxVelocity();
	}

	steeringForce = desiredVel - agent->getVelocity();
	return steeringForce.Truncate(agent->getMaxForce());
}

Vector2D SceneArrival::Arrive(Agent *agent, Agent *target, float slowingRadius, float dtime){
	return Arrive(agent, target->getPosition(),  slowingRadius, dtime);
}

void SceneArrival::update(float dtime, SDL_Event *event)
{
	/* Keyboard & Mouse events */
	switch (event->type) {
	case SDL_MOUSEMOTION:
	case SDL_MOUSEBUTTONDOWN:
		if (event->button.button == SDL_BUTTON_LEFT)
		{
			target = Vector2D((float)(event->button.x), (float)(event->button.y));
			agents[0]->setTarget(target);
		}
		break;
	default:
		break;
	}
	Vector2D steering_force = Arrive(agents[0], agents[0]->getTarget(), radius, dtime);
	agents[0]->update(steering_force, dtime, event);
}

void SceneArrival::draw()
{
	if (debugMode) {
		draw_circle(TheApp::Instance()->getRenderer(), (int)target.x, (int)target.y, 15, 255, 0, 0, 255);
		agents[0]->draw();
	}
	else
		debugDraw();
}

void SceneArrival::debugDraw() {
	//radio
	draw_circle(TheApp::Instance()->getRenderer(), (int)target.x, (int)target.y, radius, 255, 0, 0, 255);
	agents[0]->draw();
}

const char* SceneArrival::getTitle()
{
	return "SDL Steering Behaviors :: Arrival Demo";
}
void SceneArrival::changeDebugMode() {
	debugMode =! debugMode;
	for (int i = 0; i < agents.size(); i++) {
		agents[i]->changeDrawMode();
	}
}

