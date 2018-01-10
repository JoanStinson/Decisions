#include "Home.h"

Home::Home() {}

Home::~Home() {}

void Home::Update() {
	cout << "Go Home and Rest" << endl;
	SDL_Delay(delayTime);

	if (agent->wealthy) {
		agent->wealth = 0;
		agent->wealthy = false;
	}

	if (agent->tireness > 0) agent->tireness--;

	if (agent->tireness <= 0) {
		cout << "Rested" << endl;
		agent->goalPos = minePos;
		Exit(agent->mine);
	}
}

