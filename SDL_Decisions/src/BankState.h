#pragma once
#include "State.h"

class BankState : public State {

public:
	BankState();
	~BankState();

	void Update();
};
