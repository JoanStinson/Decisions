#pragma once
#include "State.h"

class Mine : public State {

public:
	Mine();
	~Mine();

	void Update() override;

private:
	int goldCount;
	int maxGold;
};
