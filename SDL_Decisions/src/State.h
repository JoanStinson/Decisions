#pragma once
#include "Agent.h"
#include <iostream>

/// <summary>
/// Virtual methods we override in child classes
/// Normal methods we don't override, because they are the same for child classes
/// </summary>
class Agent;
class State {

public:
	State();
	~State();

	virtual void Enter(Agent* agent) = 0;
	virtual void Update(Agent* agent) = 0;
	virtual void Exit(Agent* agent, State* state) = 0;

//protected:
	//Agent* agent;
	//float sleepTime;
};
