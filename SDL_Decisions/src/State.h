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

	void Enter(Agent* agent, float delayTime);
	virtual void Update() = 0;
	void Exit(State* state);

protected:
	Agent* agent;
	float delayTime;
	Vector2D bankPos;
	Vector2D homePos;
	Vector2D minePos;
	Vector2D saloonPos;
};
