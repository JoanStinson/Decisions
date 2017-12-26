#include "State.h"
#include <iostream>

void State::Init(Agent* a, float f) {
	std::cout << "Inicializating new State" << std::endl;
	agent = a;
	sleepTime = f;
}

void State::Update(Graph g) {
	agent->AStar(agent->getPosition(), agent->getTarget(), g, false);
}

void State::UpdateTarget(Vector2D v) {
	agent->setTarget(v);
}

void State::UpdateTarget(Vector2D rangeFrom, Vector2D rangeTo) {

	Vector2D newT;
	newT.x = rand() % (int)rangeFrom.x + rangeTo.x;
	newT.y = rand() % (int)rangeFrom.y + rangeTo.y;
	agent->setTarget(newT);

}

void State::Exit() {

}