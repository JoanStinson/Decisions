#pragma once
#include "State.h"

class Home : public State {

public:
	Home();
	~Home();

	void Enter(Agent* agent);
	void Update(Agent* agent);
	void Exit(Agent* agent, State* state);
};
