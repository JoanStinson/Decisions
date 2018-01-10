#pragma once
#include "State.h"

class Saloon : public State {

public:
	Saloon();
	~Saloon();

	void Enter(Agent* agent);
	void Update(Agent* agent);
	void Exit(Agent* agent, State* state);
};
