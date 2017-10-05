#include "SceneAvoidance.h"

using namespace std;

SceneAvoidance::SceneAvoidance()
{
	Agent *agent = new Agent;
	agent->setPosition(Vector2D(640, 360));
	agent->setTarget(Vector2D(640, 360));
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agents.push_back(agent);
	target = Vector2D(640, 360);
}

SceneAvoidance::~SceneAvoidance()
{
	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
}

Vector2D SceneAvoidance::Avoid(Agent *agent, Vector2D target, float dtime) {
	Vector2D desiredVel;
	Vector2D steeringForce;
	desiredVel = target - agent->getPosition();
	return 0;
}

Vector2D SceneAvoidance::Avoid(Agent *agnet, Agent *target, float dtime) {
	return 0;
}

void SceneAvoidance::update(float dtime, SDL_Event *event)
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
	//Vector2D steering_force = Avoidance(agents[0], agents[0]->getTarget(), dtime);
	//agents[0]->update(steering_force, dtime, event);
}

void SceneAvoidance::draw()
{
	draw_circle(TheApp::Instance()->getRenderer(), (int)target.x, (int)target.y, 15, 255, 0, 0, 255);
	agents[0]->draw();
}

const char* SceneAvoidance::getTitle()
{
	return "SDL Steering Behaviors :: Avoidance Demo";
}

void SceneAvoidance::changeDebugMode() {
	debugMode != debugMode;
	for (int i = 0; i < agents.size(); i++) {
		agents[i]->changeDrawMode();
	}
}