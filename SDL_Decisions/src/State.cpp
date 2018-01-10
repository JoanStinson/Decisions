#include "State.h"

State::State() {}

State::~State() {
	delete agent;
}

void State::Enter(Agent * agent, float delayTime) {
	this->agent = agent;
	this->delayTime = delayTime;

	bankPos = Vector2D(209, 624);
	homePos = Vector2D(656, 624);
	minePos = Vector2D(82, 177);
	saloonPos = Vector2D(1038, 624);
}

void State::Exit(State * state) {
	agent->SwitchState(state);
}
