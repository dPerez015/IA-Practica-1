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

	//añadir pesos al vector

}

SceneExecuteInOrder::~SceneExecuteInOrder()
{
	for (int i = 0; i < (int)agents.size(); i++) {
		delete agents[i];
	}
}

Vector2D SceneExecuteInOrder::ExecuteInOrder(Agent *agent, Vector2D target, float dtime){
	
	return agent->Behavior()->Combination(agent, target, target, dtime);
}

Vector2D SceneExecuteInOrder::ExecuteInOrder(Agent *agent, Agent *target, float dtime) {

	return ExecuteInOrder(agent, target->getPosition(), dtime);

}


Vector2D SceneExecuteInOrder::WeighedSum(Agent* agent, Vector2D target) {
	Vector2D steeringForce = Vector2D(0, 0);
	//aqui hemos de ir aplicando las fuerzas y multiplicarlas por los pesos guardados en el vector "weights"



	//una vez hecho eso hacemos un truncate de la fuerza resultante y la devolvemos 


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
	Vector2D steering_force = ExecuteInOrder(agents[0], agents[0]->getTarget(), dtime);
	agents[0]->update(steering_force, dtime, event);
}

void SceneExecuteInOrder::draw()
{
	draw_circle(TheApp::Instance()->getRenderer(), (int)target.x, (int)target.y, 15, 255, 0, 0, 255);
	agents[0]->draw();
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