#include "SceneExecuteInOrder.h"
#include "SceneArrival.h"
#include "SceneAvoidance.h"

using namespace std;

SceneExecuteInOrder::SceneExecuteInOrder()
{
	Agent *agent = new Agent;
	agent->setPosition(Vector2D(640, 360));
	agent->setTarget(Vector2D(640, 360));
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agents.push_back(agent);
	target = Vector2D(640, 360);

	agent = new Agent;
	agent->setPosition(Vector2D(1000, 300));
	agent->setTarget(Vector2D(-100, -100));
	agent->setMass(0.1f);
	agent->setColor(0, 0, 255, 255);
	agent->loadSpriteTexture("../res/zombie1.png", 8);
	agents.push_back(agent);

	//añadir pesos al vector
	seekWeight = 1;
	fleeWeight = 1;

	timeSinceLastChange = 0;
	timeToChange = 0.02;
	wanderAngle = 0;
	wanderMaxChange = 30;
	wanderCircleOffset = 200;
	wanderCircleRadius = 80;
	wanderCircleCenter = {};
	wanderDisplacementVector = {};
	srand(time(nullptr));
}

SceneExecuteInOrder::~SceneExecuteInOrder()
{
	for (int i = 0; i < (int)agents.size(); i++) {
		delete agents[i];
	}
}
/*
Vector2D SceneExecuteInOrder::ExecuteInOrder(Agent *agent, Vector2D target, float dtime){
	
	return agent->Behavior()->Combination(agent, target, target, dtime);
}

Vector2D SceneExecuteInOrder::ExecuteInOrder(Agent *agent, Agent *target, float dtime) {

	return ExecuteInOrder(agent, target->getPosition(), dtime);

}*/


Vector2D SceneExecuteInOrder::WeighedSum(Agent* agent, Vector2D target) {
	Vector2D steeringForce = Vector2D(0, 0);
	//aqui hemos de ir aplicando las fuerzas y multiplicarlas por los pesos guardados en el vector "weights"



	//una vez hecho eso hacemos un truncate de la fuerza resultante y la devolvemos 

	return  Vector2D(0,0);
}


void SceneExecuteInOrder::update(float dtime, SDL_Event *event)
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

	if (Vector2D::Distance(agents[0]->getPosition(), agents[1]->getPosition()) <= 150)
		fleeWeight = 1.3;
	else
		fleeWeight = 0;



	Vector2D steering_force = agents[0]->Behavior()->Combination(agents[0], agents[0]->getTarget(), agents[1]->getPosition(), seekWeight, fleeWeight, dtime);
	agents[0]->update(steering_force.Truncate(agents[0]->getMaxForce()), dtime, event);

	steering_force = agents[1]->Behavior()->Wander(agents[1], wanderAngle, wanderMaxChange, wanderCircleOffset, wanderCircleRadius, timeSinceLastChange, timeToChange, wanderCircleCenter, wanderDisplacementVector, dtime);
	agents[1]->update(steering_force, dtime, event);
}

void SceneExecuteInOrder::draw()
{
	draw_circle(TheApp::Instance()->getRenderer(), (int)target.x, (int)target.y, 15, 255, 0, 0, 255);
	agents[0]->draw();
	agents[1]->draw();
}

const char* SceneExecuteInOrder::getTitle()
{
	return "SDL Steering Behaviors :: Execute In Order Demo";
}

void SceneExecuteInOrder::changeDebugMode() {
	debugMode != debugMode;
	for (int i = 0; i < agents.size(); i++) {
		agents[i]->changeDrawMode(); 
	}
}