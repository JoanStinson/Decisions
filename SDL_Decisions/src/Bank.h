#pragma once
#include "State.h"

class State;
class Bank : public State {

public:
	Bank();
	~Bank();

	void Enter(Agent* agent);
	void Update(Agent* agent);
	void Exit(Agent* agent, State* state);
};
