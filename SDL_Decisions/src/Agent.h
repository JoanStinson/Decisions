#pragma once
#include <iostream>
#include <minmax.h>
#include <SDL.h>
#include <SDL_image.h>
#include "SDL_SimpleApp.h"
#include "Vector2D.h"
#include "utils.h"
#include "SteeringBehavior.h"
#include "Path.h"
#include "State.h"
#include "Graph.h"
#include <iostream>
#include <algorithm>
#include <queue>
#include <unordered_map>
#include <stdlib.h>     
#include <time.h>
using namespace std;
class State;

class Agent {

	friend class SteeringBehavior;

public:
	Agent();
	~Agent();

	SteeringBehavior *Behavior();
	Vector2D getPosition();
	Vector2D getTarget();
	Vector2D getVelocity();

	float getMaxVelocity();
	void setPosition(Vector2D position);
	void setTarget(Vector2D target);
	void setVelocity(Vector2D velocity);
	void setMass(float mass);
	void setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	void update(Vector2D steering_force, float dtime, SDL_Event *event);
	void draw();
	bool loadSpriteTexture(char* filename, int num_frames=1);

	// Our stuff
	float Heuristic(Vector2D a, Vector2D b);
	vector<Vector2D> AStar(Vector2D start, Vector2D goal, Graph graph);
	void SwitchState(State* state);

	int pockets;
	int wealth;
	int fatigue;
	int thirst;

	Vector2D objectivePosition;
	State *bankState, *homeState, *mineState, *saloonState, *currentState;

private:
	SteeringBehavior * steering_behavior;
	Vector2D position;
	Vector2D velocity;
	Vector2D target;

	float mass;
	float orientation;
	float max_force;
	float max_velocity;

	SDL_Color color;

	SDL_Texture *sprite_texture;
	bool draw_sprite;
	int sprite_num_frames;
	int sprite_w;
	int sprite_h;
	int min = 0, max = 0, average = 0, current = 0;
	vector<int> sizes;
};

//Implementation of different a priority queue than the STL one because it has problems with std::pair
//And we wanted to have a structure like this:
//	'PriorityQueue<Vector2D, float> frontier;'
//	'frontier.put(start, 0.f);'
template<typename T, typename priority_t>
struct PriorityQueue {
	typedef pair<priority_t, T> PQElement;
	priority_queue<PQElement, vector<PQElement>,
		std::greater<PQElement>> elements;

	inline bool empty() const { return elements.empty(); }

	inline void put(T item, priority_t priority) {
		elements.emplace(priority, item);
	}

	inline T get() {
		T best_item = elements.top().second;
		elements.pop(); // pop everytime we acces next element
		return best_item;
	}
};