#pragma once
#include "Agent.h"

class State {
	
public:
	void Init(Agent*, float);
	void Update(Graph);
	void UpdateTarget(Vector2D);
	void UpdateTarget(Vector2D, Vector2D);
	void Exit();
	
	Agent* agent;
	float sleepTime;

};

class Mining : public State {
	int goldCount;
	int maxGold;

	void CustomUpdate();

};

class Bank : public State {

};

class Chill : public State {

};

class Sleep : public State {

};