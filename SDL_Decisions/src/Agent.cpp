#include "Agent.h"
#include "ScenePlanning.h"
using namespace std;

Agent::Agent() : sprite_texture(0),
                 position(Vector2D(100, 100)),
	             target(Vector2D(1000, 100)),
	             velocity(Vector2D(0,0)),
	             mass(0.1f),
	             max_force(150),
	             max_velocity(200),
	             orientation(0),
	             color({ 255,255,255,255 }),
				 sprite_num_frames(0),
	             sprite_w(0),
	             sprite_h(0),
	             draw_sprite(false)
{
	steering_behavior = new SteeringBehavior;
	home = new Home;
	saloon = new Saloon;
	mine = new Mine;
	bank = new Bank;
	tireness = 0;
	gold = 0;
}

Agent::~Agent()
{
	if (sprite_texture)
		SDL_DestroyTexture(sprite_texture);
	if (steering_behavior)
		delete (steering_behavior);
}

void Agent::SwitchState(State * state) {
	currentState = state;
}

float Agent::RandomFloat(float a, float b) {
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}

float Agent::Heuristic(Vector2D a, Vector2D b) {
	return abs(a.x - b.x) + abs(a.y - b.y);
}

void Agent::PrintStatistics(int a) {
	// Current
	current = a;

	// Min
	if (min == 0) min = a;
	else if (a < min) min = a;

	// Max
	if (max == 0) max = a;
	else if (a > max) max = a;

	// Average
	sizes.push_back(a);
	int temp = 0;
	for (int i = 0; i < sizes.size(); i++) {
		temp += sizes[i];
	}
	average = temp / sizes.size();

	// Print
	cout << "\r" << "  Current: " << current << " Min: " << min << " Max: " << max << " Average: " << average << "            ";
}

vector<Vector2D> Agent::AStar(Vector2D start, Vector2D goal, Graph graph, bool show_nodes) {
	PriorityQueue<Vector2D, float> frontier;
	frontier.put(start, 0.f);

	unordered_map<Vector2D, Vector2D> came_from;
	came_from[start] = NULL;

	unordered_map<Vector2D, float> cost_so_far;
	cost_so_far[start] = 0.f;

	vector<Vector2D> path, neighbors;
	Vector2D current, next;
	bool visited;
	float new_cost, priority;
	float randCost;

	while (!frontier.empty()) {

		current = frontier.get();

		if (current == goal) {
			if (show_nodes) {
				int size = frontierCount.size();
				PrintStatistics(size);
			}
			else cout << "\r" << "           " << "    " << "      " << "    " << "      " << "    " << "          " << "    " << "            ";
			path.push_back(current);
			while (current != start) {
				current = came_from[current];
				path.push_back(current);
			}
			path.push_back(start);
			std::reverse(path.begin(), path.end());
			return path;
		}

		neighbors = graph.GetConnections(current);

		for (unsigned int i = 0; i < neighbors.size(); i++) {
			visited = false;
			next = neighbors[i];
			randCost = (rand() % 6) + 1; //RandomFloat(0, 7);
			new_cost = cost_so_far[current] + randCost; //TODO implement GetCost method to do + 'graph.GetCost(current, next)' instead of rand

			for (unsigned int j = 0; j < cost_so_far.size(); j++) {
				// If next in cost_so_far 
				if (cost_so_far.find(next) != cost_so_far.end()) {
					if (new_cost > cost_so_far[next]) { // if 'new_cost < cost_so_far[next]' visited = false perque el volem afegir, if 'new_cost > cost_so_far[next]' nol volem per tant visited = false
						visited = true;
					}
				}
				// If next not in cost_so_far
				else {
					visited = false;
				}

			}

			if (!visited) {
				cost_so_far[next] = new_cost;
				priority = new_cost + Heuristic(goal, next);
				frontier.put(next, priority);
				came_from[next] = current;
				//Count :)
				frontierCount.push_back(next);
				vector_costs.push_back(std::make_pair(next, randCost));
			}
		}
	}
}

SteeringBehavior * Agent::Behavior()
{
	return steering_behavior;
}

Vector2D Agent::getPosition()
{
	return position;
}

Vector2D Agent::getTarget()
{
	return target;
}

Vector2D Agent::getVelocity()
{
	return velocity;
}

float Agent::getMaxVelocity()
{
	return max_velocity;
}

void Agent::setPosition(Vector2D _position)
{
	position = _position;
}

void Agent::setTarget(Vector2D _target)
{
	target = _target;
}

void Agent::setVelocity(Vector2D _velocity)
{
	velocity = _velocity;
}

void Agent::setMass(float _mass)
{
	mass = _mass;
}

void Agent::setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	color = { r, g, b, a };
}

void Agent::update(Vector2D steering_force, float dtime, SDL_Event *event)
{

	//cout << "agent update:" << endl;

	switch (event->type) {
		/* Keyboard & Mouse events */
	case SDL_KEYDOWN:
		if (event->key.keysym.scancode == SDL_SCANCODE_SPACE)
			draw_sprite = !draw_sprite;
		break;
	default:
		break;
	}


	Vector2D acceleration = steering_force / mass;
	velocity = velocity + acceleration * dtime;
	velocity = velocity.Truncate(max_velocity);

	position = position + velocity * dtime;


	// Update orientation
	if (velocity.Length()>0)
		orientation = (float)(atan2(velocity.y, velocity.x) * RAD2DEG);


	// Trim position values to window size
	if (position.x < 0) position.x = TheApp::Instance()->getWinSize().x;
	if (position.y < 0) position.y = TheApp::Instance()->getWinSize().y;
	if (position.x > TheApp::Instance()->getWinSize().x) position.x = 0;
	if (position.y > TheApp::Instance()->getWinSize().y) position.y = 0;
}

void Agent::draw()
{
	if (draw_sprite)
	{
		Uint32 sprite;
		
		if (velocity.Length() < 5.0)
			sprite = 1;
		else
			sprite = (int)(SDL_GetTicks() / (max_velocity)) % sprite_num_frames;
		
		SDL_Rect srcrect = { (int)sprite * sprite_w, 0, sprite_w, sprite_h };
		SDL_Rect dstrect = { (int)position.x - (sprite_w / 2), (int)position.y - (sprite_h / 2), sprite_w, sprite_h };
		SDL_Point center = { sprite_w / 2, sprite_h / 2 };
		SDL_RenderCopyEx(TheApp::Instance()->getRenderer(), sprite_texture, &srcrect, &dstrect, orientation+90, &center, SDL_FLIP_NONE);
	}
	else 
	{
		draw_circle(TheApp::Instance()->getRenderer(), (int)position.x, (int)position.y, 15, color.r, color.g, color.b, color.a);
		SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), (int)position.x, (int)position.y, (int)(position.x+15*cos(orientation*DEG2RAD)), (int)(position.y+15*sin(orientation*DEG2RAD)));
	}
}

bool Agent::loadSpriteTexture(char* filename, int _num_frames)
{
	if (_num_frames < 1) return false;

	SDL_Surface *image = IMG_Load(filename);
	if (!image) {
		cout << "IMG_Load: " << IMG_GetError() << endl;
		return false;
	}
	sprite_texture = SDL_CreateTextureFromSurface(TheApp::Instance()->getRenderer(), image);

	sprite_num_frames = _num_frames;
	sprite_w = image->w / sprite_num_frames;
	sprite_h = image->h;
	draw_sprite = true;

	if (image)
		SDL_FreeSurface(image);

	return true;
}
