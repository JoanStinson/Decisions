#include "SaloonState.h"

SaloonState::SaloonState() {}

SaloonState::~SaloonState() {}

void SaloonState::Update() {
	cout << "Drink at the Saloon" << endl;

	agent->thirst--;

	if (agent->thirst <= 0) {
		cout << "Not Thirsty" << endl;
		agent->objectivePosition = minePosition;
		Quit(agent->mineState);
	}

	SDL_Delay(delayTime);
}
