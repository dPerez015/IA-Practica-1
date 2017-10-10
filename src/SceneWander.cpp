#include "SceneWander.h"


using namespace std;

SceneWander::SceneWander()
{
	debugMode = true;
	Agent *agent = new Agent;
	agent->setPosition(Vector2D(640, 360));
	agent->setTarget(Vector2D(640, 360));
	agent->setMass(0.035);
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agents.push_back(agent);
	target = Vector2D(640, 360);
	wanderMaxChange = 30.f;
	wanderCircleOffset = 200;
	wanderCircleRadius = 80;
	wanderAngle = 0.0f;
	wanderCircleCenter = {};
	wanderDisplacementVector = {};
	srand(time(nullptr));

	timeToChange = 0.02;
	timeSinceLastChange = 0;
}

SceneWander::~SceneWander()
{
	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
}

Vector2D SceneWander::Wander(Agent* agent, float angle, float &wanderAngle, float wanderMaxChange, int wanderCircleOffset, int wanderCircleRadius, float dt) {
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
		wanderAngle += ((float)(rand() / RAND_MAX)* wanderMaxChange) - (wanderMaxChange / 2);
		timeSinceLastChange = 0;
	}
	//Calcular WanderForce (suma dels 2 vectors)
	Vector2D wanderForce = wanderCircleCenter + wanderDisplacementVector;


	agents[0]->setTarget(agents[0]->getPosition() + wanderCircleCenter + wanderDisplacementVector);
	//truncate maxForce
	return wanderForce.Truncate(agent->getMaxForce());
}

void SceneWander::update(float dtime, SDL_Event *event)
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
	Vector2D velocity = agents[0]->getVelocity();
	float angle = (float)(atan2(velocity.y, velocity.x) * RAD2DEG);
	Vector2D steering_force = Wander(agents[0], angle, wanderAngle, wanderMaxChange,
		wanderCircleOffset, wanderCircleRadius, dtime);
	agents[0]->update(steering_force, dtime, event);
}

void SceneWander::draw()
{
	if (debugMode)
		agents[0]->draw();
	else
		debugDraw();
}

void SceneWander::debugDraw() {
	agents[0]->draw();
	draw_circle(TheApp::Instance()->getRenderer(), wanderCircleCenter.x + agents[0]->getPosition().x, wanderCircleCenter.y + agents[0]->getPosition().y, wanderCircleRadius, 255, 0, 0, 255);
}

void SceneWander::changeDebugMode() {
	debugMode = !debugMode;
	for (int i = 0; i < agents.size(); i++) {
		agents[i]->changeDrawMode();
	}
}
const char* SceneWander::getTitle()
{
	return "SDL Steering Behaviors :: Wander Demo";
}