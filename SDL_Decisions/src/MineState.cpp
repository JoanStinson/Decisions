#include "MineState.h"

MineState::MineState() {}

MineState::~MineState() {}

void MineState::Update() {
	cout << "Enter Mine and Dig" << endl;

	agent->thirst++;
	agent->pockets++;
	agent->fatigue++;

	if (agent->thirst >= 7) {
		cout << "Thirsty" << endl;
		agent->objectivePosition = saloonPosition;
		Quit(agent->saloonState);
	}
	else if (agent->pockets >= 5) {
		cout << "Pockets Full" << endl;
		agent->objectivePosition = bankPosition;
		Quit(agent->bankState);
	}

	SDL_Delay(delayTime);
}
