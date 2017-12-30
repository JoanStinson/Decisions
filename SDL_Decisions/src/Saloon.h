#pragma once
#include "State.h"

class Saloon : public State {

public:
	Saloon();
	~Saloon();

	void Update() override;
};
