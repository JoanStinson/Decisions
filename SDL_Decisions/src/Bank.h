#pragma once
#include "State.h"

class Bank : public State {

public:
	Bank();
	~Bank();

	void Update() override;
};
