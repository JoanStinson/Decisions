#include "Mine.h"

Mine::Mine() {}

Mine::~Mine() {}

void Mine::Update() {
	//TODO fer aixo bé, de moment he ficat un exemple:
	// if gold == 3
		//exit to saloon
	// if tired == 9
		//exit to home

	goldCount++;

	if (goldCount >= maxGold) {
		UpdateTarget(209, 624);
		Exit(agent->bank);
	}
}
