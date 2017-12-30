#include "State.h"

State::State() {}

State::~State() {}

void State::Enter(Agent* agent, float sleepTime) {
	std::cout << "Inicializing new State" << std::endl;
	this->agent = agent;
	this->sleepTime = sleepTime;
}

void State::Update() {}

void State::UpdateTarget(Vector2D vector) {
	agent->setTarget(vector);
}

void State::UpdateTarget(Vector2D rangeFrom, Vector2D rangeTo) {
	Vector2D newT;
	newT.x = rand() % (int)rangeFrom.x + rangeTo.x;
	newT.y = rand() % (int)rangeFrom.y + rangeTo.y;
	agent->setTarget(newT);
}

void State::Exit(State* state) {
	agent->SwitchState(state);
}
