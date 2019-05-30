#include "HomeState.h"

HomeState::HomeState() {}

HomeState::~HomeState() {}

void HomeState::Update() {
	cout << "Go Home and Rest" << endl;

	if (agent->fatigue >= 0) 
		agent->fatigue--;

	if (agent->wealth >= 12) 
		agent->wealth = 0;

	if (agent->fatigue < 0) {
		cout << "Rested" << endl;
		agent->objectivePosition = minePosition;
		Quit(agent->mineState);
	}

	SDL_Delay(delayTime);
}

