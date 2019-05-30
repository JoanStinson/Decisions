#include "State.h"

State::State() {
	bankPosition = Vector2D(208, 624);
	homePosition = Vector2D(624, 624);
	minePosition = Vector2D(272, 112);
	saloonPosition = Vector2D(1040, 624);
}

State::~State() {
	delete agent;
}

void State::Init(Agent * agent, Uint32 delayTime) {
	this->agent = agent;
	this->delayTime = delayTime;
}

void State::Quit(State * state) {
	agent->SwitchState(state);
}
