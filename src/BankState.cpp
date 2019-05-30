#include "BankState.h"

BankState::BankState() {}

BankState::~BankState() {}

void BankState::Update() {
	cout << "Visit Bank and Deposit Gold" << endl;
	agent->wealth++;
	agent->pockets--;

	if (agent->wealth >= 12 && agent->pockets <= 0) {
		cout << "Wealthy Enough" << endl;
		agent->objectivePosition = homePosition;
		Quit(agent->homeState);
	}
	else if (agent->wealth <= 11 && agent->pockets <= 0) {
		cout << "Not Wealthy Enough" << endl;
		agent->objectivePosition = minePosition;
		Quit(agent->mineState);
	}

	SDL_Delay(delayTime);
}
