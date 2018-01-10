#include "State.h"

State::State() {
	bankPosition = Vector2D(209, 656);
	homePosition = Vector2D(656, 656);
	minePosition = Vector2D(656, 145);
	saloonPosition = Vector2D(1042, 656);
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
