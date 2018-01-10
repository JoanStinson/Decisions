#pragma once
#include "State.h"

class Mine : public State {

public:
	Mine();
	~Mine();

	void Enter(Agent* agent);
	void Update(Agent* agent);
	void Exit(Agent* agent, State* state);
};
