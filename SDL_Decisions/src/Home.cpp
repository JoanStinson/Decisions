#include "Home.h"

Home::Home() {}

Home::~Home() {}

inline void Home::Enter(Agent * agent) {
	cout << "Entered Home State" << endl;

	if (agent->wealthy) {
		agent->wealth = 0;
		agent->wealthy = false;
	}
}

void Home::Update(Agent * agent) {
	cout << "Go Home and Rest" << endl;
	SDL_Delay(250);

	if (agent->tireness > 0) agent->tireness--;

	if (agent->tireness <= 0) {
		cout << "Rested" << endl;
		agent->goalPos = Vector2D(82, 177);
		Exit(agent, agent->mine);
	}
}

inline void Home::Exit(Agent * agent, State * state) {
	agent->SwitchState(state);
}

