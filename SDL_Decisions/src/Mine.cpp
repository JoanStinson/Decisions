#include "Mine.h"

Mine::Mine() {}

Mine::~Mine() {}

void Mine::Update() {
	cout << "Enter Mine and Dig" << endl;
	SDL_Delay(delayTime);

	agent->gold++;
	agent->tireness++;
	agent->thirst += 0.5f;

	if (agent->thirst >= 5) {
		cout << "Thirsty" << endl;
		agent->goalPos = saloonPos;
		Exit(agent->saloon);
	}
	else if (agent->gold == 3) {
		cout << "Pockets Full" << endl;
		agent->goalPos = bankPos;
		Exit(agent->bank);
	}
}
