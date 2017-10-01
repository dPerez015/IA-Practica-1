#include "SceneWander.h"


using namespace std;

SceneWander::SceneWander()
{
	Agent *agent = new Agent;
	agent->setPosition(Vector2D(640,360));
	agent->setTarget(Vector2D(640, 360));
	agent->setMass(0.035);
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agents.push_back(agent);
	target = Vector2D(640, 360);
	wanderMaxChange = 50;
	wanderCircleOffset = 70;
	wanderCircleRadius = 80;
	wanderAngle = 0.0f;
	wanderCircleCenter = {};
	wanderDisplacementVector = {};
	srand(time(nullptr));
}

SceneWander::~SceneWander()
{
	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
}

Vector2D SceneWander::Wander(Agent* agent, float angle, float* wanderAngle, int wanderMaxChange, int wanderCircleOffset, int wanderCircleRadius, float dt) {
	
	//vector del centre del cercle respecte l'agent
	wanderCircleCenter = agent->getVelocity().Normalize() * wanderCircleOffset;

	//Displacement force
	wanderDisplacementVector.x = cos(*wanderAngle) * wanderCircleRadius;
	wanderDisplacementVector.y = sin(*wanderAngle) * wanderCircleRadius;

	
	wanderAngle += rand() % wanderMaxChange - wanderMaxChange / 2;
	
	//Calcular WanderForce (suma dels 2 vectors)
	Vector2D wanderForce = wanderCircleCenter + wanderDisplacementVector;

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
	Vector2D steering_force = Wander(agents[0], angle, &wanderAngle, wanderMaxChange,
		wanderCircleOffset, wanderCircleRadius, dtime);
	agents[0]->update(steering_force, dtime, event);
}

void SceneWander::draw()
{
	agents[0]->draw();
}

const char* SceneWander::getTitle()
{
	return "SDL Steering Behaviors :: Wander Demo";
}