#include "Saloon.h"

Saloon::Saloon() {}

Saloon::~Saloon() {}

inline void Saloon::Enter(Agent * agent) {
	cout << "Entered Saloon State" << endl;
}

void Saloon::Update(Agent * agent) {
	cout << "Drink at the Saloon" << endl;
	SDL_Delay(250);

	agent->thirst--;

	if (agent->thirst <= 0) {
		cout << "Not Thirsty" << endl;
		agent->goalPos = Vector2D(82, 177);
		Exit(agent, agent->mine);
	}
}

inline void Saloon::Exit(Agent * agent, State * state) {
	agent->SwitchState(state);
}
