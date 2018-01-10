#include "Bank.h"

Bank::Bank() {}

Bank::~Bank() {}

inline void Bank::Enter(Agent * agent) {
	cout << "Entered Bank State" << endl;
}

void Bank::Update(Agent * agent) {
	cout << "Visit Bank and Deposit Gold" << endl;
	SDL_Delay(250);
	
	agent->wealth++;
	agent->totalWealth++;
	agent->gold--;

	if (agent->wealth >= 7) agent->wealthy = true;
	
	if (agent->gold <= 0 && !agent->wealthy) {
		cout << "Wealth: " << agent->wealth << endl;
		cout << "Not Wealthy Enough" << endl;
		agent->goalPos = Vector2D(82, 177);
		Exit(agent, agent->mine);
	}
	else if (agent->gold <= 0 && agent->wealthy) {
		cout << "Wealth: " << agent->wealth << endl;
		cout << "Wealthy Enough" << endl;
		agent->goalPos = Vector2D(656, 624);
		Exit(agent, agent->home);
	}
}

inline void Bank::Exit(Agent * agent, State * state) {
	agent->SwitchState(state);
}
