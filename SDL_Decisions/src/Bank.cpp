#include "Bank.h"

Bank::Bank() {}

Bank::~Bank() {}

void Bank::Update() {
	cout << "Visit Bank and Deposit Gold" << endl;
	SDL_Delay(delayTime);
	
	agent->wealth++;
	agent->totalWealth++;
	agent->gold--;

	if (agent->wealth >= 7) agent->wealthy = true;
	
	if (agent->gold <= 0 && !agent->wealthy) {
		cout << "Not Wealthy Enough" << endl;
		agent->goalPos = minePos;
		Exit(agent->mine);
	}
	else if (agent->gold <= 0 && agent->wealthy) {
		cout << "Wealthy Enough" << endl;
		agent->goalPos = homePos;
		Exit(agent->home);
	}
}
