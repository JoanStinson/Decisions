#pragma once
#include "State.h"

class Home : public State {

public:
	Home();
	~Home();

	void Update() override;
};
