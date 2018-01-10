#include "Mine.h"

Mine::Mine() {}

Mine::~Mine() {}

inline void Mine::Enter(Agent * agent) {
	cout << "Entered Mine State" << endl;
}

void Mine::Update(Agent * agent) {
	cout << "Enter Mine and Dig" << endl;
	SDL_Delay(250);

	agent->gold++;
	agent->tireness++;
	agent->thirst += 0.5f;

	if (agent->thirst >= 5) {
		cout << "Thirsty" << endl;
		agent->goalPos = Vector2D(1038, 624);
		Exit(agent, agent->saloon);
	}
	else if (agent->gold == 3) {
		cout << "Pockets Full" << endl;
		agent->goalPos = Vector2D(209, 624);
		Exit(agent, agent->bank);
	}
}

inline void Mine::Exit(Agent * agent, State * state) {
	agent->SwitchState(state);
}
