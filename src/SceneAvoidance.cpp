#include "SceneAvoidance.h"
#include "SDL_SimpleApp.h"

using namespace std;

SceneAvoidance::SceneAvoidance()
{
	Agent *agent = new Agent;
	agent->setPosition(Vector2D(640, 360));
	agent->setTarget(Vector2D(640, 360));
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agents.push_back(agent);
	target = Vector2D(640, 360);
	perimeterBorder = 100.f;
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

Vector2D SceneAvoidance::Avoid(Agent *agent, Agent *target, float dtime) {
	return Avoid(agent, target->getPosition(), dtime);
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
	Vector2D steering_force = Avoid(agents[0], agents[0]->getTarget(), dtime);
	agents[0]->update(steering_force, dtime, event);
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