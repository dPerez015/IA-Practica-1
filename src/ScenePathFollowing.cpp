#include "ScenePathFollowing.h"

ScenePathFollowing::ScenePathFollowing() {
	Agent *agent = new Agent;
	agent->setPosition(Vector2D(640, 360));
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agents.push_back(agent);
	path.push_back(Vector2D(640, 360));
	detectionRadius = 20.f;

	currentTarget=searchNearTarget();
 	agents[0]->setTarget(path[currentTarget]);
	debugMode = true;
	pathCurrentDirection = 1;
	agentOnTarget = false;
	lastTimeTargetSeted = 0;
	timeToTarget = 0.2;

}

bool ScenePathFollowing::checkDistance(Vector2D p1, Vector2D p2, float radius) {
	if (Vector2D::Distance(p1, p2) < radius)
		return true;
	else
		return false;
}

ScenePathFollowing::~ScenePathFollowing()
{
	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
	path.clear();
}

int ScenePathFollowing::searchNearTarget() {
	int nearest=0;
	for (int i = 0; i < path.size();i++) {
		if (Vector2D::Distance(path[i], agents[0]->getPosition()) > Vector2D::Distance(path[nearest], agents[0]->getPosition()))
			nearest = i;
	}
	return nearest;
}


void ScenePathFollowing::checkPathState() {
	

}

void ScenePathFollowing::changeAgentTarget(Agent* agent,std::vector<Vector2D>& path , int& pathCurrentDirection, int& currentTarget, int pathSize) {
	if (pathSize < 0) {
		agent->setTarget(agent->getPosition());
	}
	else if (pathSize > 1) {
		if (currentTarget + pathCurrentDirection<0 || currentTarget + pathCurrentDirection >= pathSize) {
			pathCurrentDirection *= -1;
			currentTarget += pathCurrentDirection;
			agent->setTarget(path[currentTarget]);
		}
		else {
			currentTarget += pathCurrentDirection;
			agent->setTarget(path[currentTarget]);
		}
	}
}


void ScenePathFollowing::update(float dtime, SDL_Event* even) {
	lastTimeTargetSeted += dtime;

	switch (even->type) {
	case SDL_MOUSEMOTION:
	case SDL_MOUSEBUTTONDOWN:
		
			if (even->button.button == SDL_BUTTON_LEFT)
			{
				if (lastTimeTargetSeted > timeToTarget) {
					lastTimeTargetSeted = 0;
					path.push_back(Vector2D((float)(even->button.x), (float)(even->button.y)));
				}
			}
			else if (even->button.button == SDL_BUTTON_RIGHT) {
				if (lastTimeTargetSeted > timeToTarget) {
					lastTimeTargetSeted = 0;
					bool notFound = true;
					int i = 0;
					while (notFound && i < path.size()) {
						
						if (checkDistance(Vector2D((float)(even->button.x), (float)(even->button.y)), path[i], 10)) {
							notFound = false;
							path.erase(path.begin() + i );

							if (i == currentTarget && i == path.size()) {
								changeAgentTarget(agents[0], path, pathCurrentDirection, currentTarget, path.size());
							}
							//else if (i == currentTarget && i == 0) {
							//	agents[0]->setTarget(path[0]);
							//}
							else if (pathCurrentDirection == -1)
								currentTarget -= 1;

							agents[0]->setTarget(path[currentTarget]);
						}
						i++;
					}
				}
			}
		
			break;
		default:
			break;
	}
	//calculos de los puntos del camino
	if (checkDistance(agents[0]->getPosition(),agents[0]->getTarget(),detectionRadius)) {
		changeAgentTarget(agents[0], path, pathCurrentDirection, currentTarget, path.size());
	}
	//calculos de fuerza
	Vector2D steeringForce = agents[0]->Behavior()->Arrive(agents[0], agents[0]->getTarget(), detectionRadius, dtime);
	agents[0]->update(steeringForce, dtime, even);

}
void ScenePathFollowing::draw() {
	for (int i = 0; i < path.size(); i++) {
		draw_circle(TheApp::Instance()->getRenderer(), (int)path[i].x, (int)path[i].y, 10, 255, 0, 0, 255);
		if (i != path.size()-1) {
			SDL_RenderDrawLine(TheApp::Instance()->getRenderer(),path[i].x , path[i].y, path[i+1].x, path[i+1].y);
		}
	}
	agents[0]->draw();
}

const char* ScenePathFollowing::getTitle() {
	return "SDL Steering Behaviors :: Path Following Demo";
}
void ScenePathFollowing::changeDebugMode() {
	debugMode = !debugMode;
	for (int i = 0; i < agents.size(); i++) {
		agents[i]->changeDrawMode();
	}
}
