#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "SDL_SimpleApp.h"
#include "ScenePlanning.h"

#define FRAMES_PER_SEC 30
using namespace std;

/*
Copyright 2012 Abraham T. Stolk
Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at
http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License.
*/

#include "Goap.h"	// for planner interface.
#include "AStar.h"	// for A* search over worldstate space.


#include <string.h>
#include <stdio.h> 

int main(int argc, char ** argv) {

	bool quit = false;
	SDL_Event event;
	int this_tick = 0;
	int next_tick = 1000/FRAMES_PER_SEC;

	SDL_SimpleApp *app = SDL_SimpleApp::Instance();

	Scene *curr_scene = new ScenePlanning;
	app->setWindowTitle(curr_scene->getTitle());

	while (!quit) {
		this_tick = SDL_GetTicks();
		/*if (this_tick < next_tick) 
			SDL_Delay(next_tick - this_tick);*/
		
		next_tick = this_tick + (1000 / FRAMES_PER_SEC);

		// run app frame by frame
		event = app->run(curr_scene);

		/* Keyboard events */
		switch (event.type) {
		case SDL_KEYDOWN:
			if (event.key.keysym.scancode == SDL_SCANCODE_1) {
				delete(curr_scene);
				curr_scene = new ScenePlanning;
				app->setWindowTitle(curr_scene->getTitle());
			}

			if (event.key.keysym.scancode == SDL_SCANCODE_2) {


				static actionplanner_t ap;
				goap_actionplanner_clear(&ap);

				goap_set_pre(&ap, "scout", "armedwithgun", true);
				goap_set_pst(&ap, "scout", "enemyvisible", true);

				goap_set_pre(&ap, "approach", "enemyvisible", true);
				goap_set_pst(&ap, "approach", "nearenemy", true);

				goap_set_pre(&ap, "aim", "enemyvisible", true);
				goap_set_pre(&ap, "aim", "weaponloaded", true);
				goap_set_pst(&ap, "aim", "enemylinedup", true);

				goap_set_pre(&ap, "shoot", "enemylinedup", true);
				goap_set_pst(&ap, "shoot", "enemyalive", false);

				goap_set_pre(&ap, "load", "armedwithgun", true);
				goap_set_pst(&ap, "load", "weaponloaded", true);

				goap_set_pre(&ap, "detonatebomb", "armedwithbomb", true);
				goap_set_pre(&ap, "detonatebomb", "nearenemy", true);
				goap_set_pst(&ap, "detonatebomb", "alive", false);
				goap_set_pst(&ap, "detonatebomb", "enemyalive", false);

				goap_set_pre(&ap, "flee", "enemyvisible", true);
				goap_set_pst(&ap, "flee", "nearenemy", false);


				char desc[4096];
				goap_description(&ap, desc, sizeof(desc));
				LOGI("%s", desc);

				worldstate_t fr;
				goap_worldstate_clear(&fr);
				goap_worldstate_set(&ap, &fr, "enemyvisible", false);
				goap_worldstate_set(&ap, &fr, "armedwithgun", true);
				goap_worldstate_set(&ap, &fr, "weaponloaded", false);
				goap_worldstate_set(&ap, &fr, "enemylinedup", false);
				goap_worldstate_set(&ap, &fr, "enemyalive", true);
				goap_worldstate_set(&ap, &fr, "armedwithbomb", true);
				goap_worldstate_set(&ap, &fr, "nearenemy", false);
				goap_worldstate_set(&ap, &fr, "alive", true);

				goap_set_cost(&ap, "detonatebomb", 5);	// make suicide more expensive than shooting.

				worldstate_t goal;
				goap_worldstate_clear(&goal);
				goap_worldstate_set(&ap, &goal, "enemyalive", false);
				//goap_worldstate_set( &ap, &goal, "alive", true ); // add this to avoid suicide actions in plan.

				worldstate_t states[16];
				const char* plan[16];
				int plansz = 16;
				const int plancost = astar_plan(&ap, fr, goal, plan, states, &plansz);
				LOGI("plancost = %d", plancost);
				goap_worldstate_description(&ap, &fr, desc, sizeof(desc));
				LOGI("%-23s%s", "", desc);
				for (int i = 0; i<plansz && i<16; ++i)
				{
					goap_worldstate_description(&ap, states + i, desc, sizeof(desc));
					LOGI("%d: %-20s%s", i, plan[i], desc);
				}

				//return plancost;
			}

			if (event.key.keysym.scancode == SDL_SCANCODE_3) {
			}

			if ((event.key.keysym.scancode == SDL_SCANCODE_Q) || (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE))
				quit = true;
			
			if (event.key.keysym.scancode == SDL_SCANCODE_F)
				app->setFullScreen();
			
			break;
		case SDL_QUIT:
			quit = true;
			break;
		}
	}

	return 0;
}