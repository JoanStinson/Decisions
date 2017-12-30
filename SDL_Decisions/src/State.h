#pragma once
#include "Agent.h"
#include <iostream>

/// <summary>
/// Virtual methods we override in child classes
/// Normal methods we don't override, because they are the same for child classes
/// </summary>
class State {

public:
	State();
	~State();

	inline void Enter(Agent* agent, float sleepTime);
	virtual void Update();
	inline void UpdateTarget(Vector2D vector);
	void UpdateTarget(Vector2D rangeFrom, Vector2D rangeTo);
	inline void Exit(State* state);

protected:
	Agent* agent;
	float sleepTime;
};
