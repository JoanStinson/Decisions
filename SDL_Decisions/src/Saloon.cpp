#include "Saloon.h"

Saloon::Saloon() {}

Saloon::~Saloon() {}

void Saloon::Update() {
	cout << "Drink at the Saloon" << endl;
	SDL_Delay(delayTime);

	agent->thirst--;

	if (agent->thirst <= 0) {
		cout << "Not Thirsty" << endl;
		agent->goalPos = minePos;
		Exit(agent->mine);
	}
}
