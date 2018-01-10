#pragma once
#include "Agent.h"
#include <iostream>
class Agent;

/// <summary>
/// Virtual methods we override in child classes
/// Normal methods we don't override, because they are the same for child classes
/// </summary>
class State {

public:
	State();
	~State();

	void Init(Agent* agent, Uint32 delayTime);
	virtual void Update() = 0;
	void Quit(State* state);

protected:
	Agent* agent;
	Uint32 delayTime;
	Vector2D bankPosition, homePosition, minePosition, saloonPosition;
};
