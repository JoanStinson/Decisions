#include "ScenePlanning.h"
#include "State.h"

using namespace std;


ScenePlanning::ScenePlanning()
{
	draw_grid = true;

	num_cell_x = SRC_WIDTH / CELL_SIZE;
	num_cell_y = SRC_HEIGHT / CELL_SIZE;
	initMaze();
	loadTextures("../res/coin.png");

	srand((unsigned int)time(NULL));

	Agent *agent = new Agent;
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agents.push_back(agent);


	// Set agent position coords to the center of a random cell
	Vector2D rand_cell(-1, -1);
	while (!isValidCell(rand_cell))
		rand_cell = Vector2D((float)(rand() % num_cell_x), (float)(rand() % num_cell_y));
	agents[0]->setPosition(cell2pix(rand_cell));
	start = agents[0]->getPosition();

	// Set the coin in a random cell (but at least 3 cells far from the agent)
	coinPosition = Vector2D(-1, -1);
	while ((!isValidCell(coinPosition)) || (Vector2D::Distance(coinPosition, rand_cell) < 3))
		coinPosition = Vector2D((float)(rand() % num_cell_x), (float)(rand() % num_cell_y));

	// PathFollowing next Target
	currentTarget = Vector2D(0, 0);
	currentTargetIndex = -1;

	// A* Algorithm
	
	/*agents[0]->vector_costs.clear();
	agents[0]->frontierCount.clear();
	astar = agents[0]->AStar(pix2cell(start), coinPosition, graph, true);
	for (unsigned int i = 0; i < astar.size(); i++) {
		path.points.push_back(cell2pix(astar[i]));
	}

	Mine mining;
	mining.Init(agents[0], 0);

	Bank bank;
	bank.Init(agents[0], 1000);

	Saloon chill;
	chill.Init(agents[0], 1000);

	Home sleep;
	sleep.Init(agents[0], 5000);*/

}

ScenePlanning::~ScenePlanning()
{
	if (background_texture)
		SDL_DestroyTexture(background_texture);
	if (coin_texture)
		SDL_DestroyTexture(coin_texture);

	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
}

void ScenePlanning::update(float dtime, SDL_Event *event)
{
	/* Keyboard & Mouse events */
	switch (event->type) {
	case SDL_KEYDOWN:
		/*if (event->key.keysym.scancode == SDL_SCANCODE_C)
			draw_costs = !draw_costs;
		else if (event->key.keysym.scancode == SDL_SCANCODE_F)
			draw_frontier = !draw_frontier;
		else if (event->key.keysym.scancode == SDL_SCANCODE_L)
			draw_lines = !draw_lines;
		else if (event->key.keysym.scancode == SDL_SCANCODE_M)
			draw_map = !draw_map;
		else if (event->key.keysym.scancode == SDL_SCANCODE_N)
			draw_numbers = !draw_numbers;*/
		if (event->key.keysym.scancode == SDL_SCANCODE_SPACE)
			draw_grid = !draw_grid;
		break;
	default:
		break;
	}
	if ((currentTargetIndex == -1) && (path.points.size() > 0))
		currentTargetIndex = 0;

	if (currentTargetIndex >= 0) {
		float dist = Vector2D::Distance(agents[0]->getPosition(), path.points[currentTargetIndex]);
		if (dist < path.ARRIVAL_DISTANCE) {
			if (currentTargetIndex == path.points.size() - 1) {
				if (dist < 3) {
					currentTargetIndex = -1;
					agents[0]->setVelocity(Vector2D(0, 0));
					// if we have arrived to the coin, replace it ina random cell!
					if (pix2cell(agents[0]->getPosition()) == coinPosition) {

						coinPosition = Vector2D(-1, -1);

						while ((!isValidCell(coinPosition)) || (Vector2D::Distance(coinPosition, pix2cell(agents[0]->getPosition())) < 3))
							coinPosition = Vector2D((float)(rand() % num_cell_x), (float)(rand() % num_cell_y));
						agents[0]->setPosition(path.points.back());
						start = agents[0]->getPosition();
						path.points.clear();

						// A* Algorithm
						/*agents[0]->vector_costs.clear();
						agents[0]->frontierCount.clear();
						astar = agents[0]->AStar(pix2cell(start), coinPosition, graph, true);
						for (unsigned int i = 0; i < astar.size(); i++) {
							path.points.push_back(cell2pix(astar[i]));
						}*/
					}
				}
				else {
					Vector2D steering_force = agents[0]->Behavior()->Arrive(agents[0], currentTarget, path.ARRIVAL_DISTANCE, dtime);
					agents[0]->update(steering_force, dtime, event);
				}
				return;
			}
			currentTargetIndex++;
		}

		currentTarget = path.points[currentTargetIndex];
		Vector2D steering_force = agents[0]->Behavior()->Seek(agents[0], currentTarget, dtime);
		agents[0]->update(steering_force, dtime, event);
	}
	else {
		agents[0]->update(Vector2D(0, 0), dtime, event);
	}
}

void ScenePlanning::draw()
{
	drawMaze();
	drawCoin();

	// Draw grid
	if (draw_grid)
	{
		SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 255, 255, 255, 127);
		for (int i = 0; i < SRC_WIDTH; i+=CELL_SIZE)
		{
			SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), i, 0, i, SRC_HEIGHT);
		}
		for (int j = 0; j < SRC_HEIGHT; j = j += CELL_SIZE)
		{
			SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), 0, j, SRC_WIDTH, j);
		}
	}

	// Draw path
	for (int i = 0; i < (int)path.points.size(); i++)
	{
		draw_circle(TheApp::Instance()->getRenderer(), (int)(path.points[i].x), (int)(path.points[i].y), 15, 255, 255, 0, 255);
		if (i > 0)
			SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), (int)(path.points[i - 1].x), (int)(path.points[i - 1].y), (int)(path.points[i].x), (int)(path.points[i].y));
	}

	// Draw floors
	/*for (auto it = graph.allConnections.begin(); it != graph.allConnections.end(); ++it) {
		draw_circle(TheApp::Instance()->getRenderer(), cell2pix((*it).first).x, cell2pix((*it).first).y, 15, 0, 0, 255, 255);
	}*/


	draw_circle(TheApp::Instance()->getRenderer(), (int)currentTarget.x, (int)currentTarget.y, 15, 255, 0, 0, 255);

	agents[0]->draw();
}

const char* ScenePlanning::getTitle()
{
	return "SDL Steering Behaviors :: PathFinding1 Demo";
}

void ScenePlanning::drawMaze()
{
	if (draw_grid)
	{

		SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 0, 0, 255, 255);
		for (unsigned int i = 0; i < maze_rects.size(); i++)
			SDL_RenderFillRect(TheApp::Instance()->getRenderer(), &maze_rects[i]);
	}
	else
	{
		//SDL_RenderCopy(TheApp::Instance()->getRenderer(), background_texture, NULL, NULL );
	}
}

void ScenePlanning::drawCoin()
{
	Vector2D coin_coords = cell2pix(coinPosition);
	int offset = CELL_SIZE / 2;
	SDL_Rect dstrect = {(int)coin_coords.x-offset, (int)coin_coords.y - offset, CELL_SIZE, CELL_SIZE};
	SDL_RenderCopy(TheApp::Instance()->getRenderer(), coin_texture, NULL, &dstrect);
}

void ScenePlanning::initMaze()
{

	// Initialize a list of Rectagles describing the maze geometry (useful for collision avoidance)
	SDL_Rect rect = { 0, 0, 1280, 32 };
	maze_rects.push_back(rect);
	rect = { 128, 160, 1152, 32 };
	maze_rects.push_back(rect);
	rect = { 0, 736, 1280, 32 };
	maze_rects.push_back(rect);
	
	rect = { 0,32,32,736 };
	maze_rects.push_back(rect);
	rect = { 1248,32,32,736 };
	maze_rects.push_back(rect);

	rect = { 416,512,32,268 };
	maze_rects.push_back(rect);
	rect = { 832,512,32,268 };
	maze_rects.push_back(rect);
	
	rect = { 32,480,128,32 };
	maze_rects.push_back(rect);
	rect = { 288,480,288,32 };
	maze_rects.push_back(rect);
	rect = { 704,480,288,32 };
	maze_rects.push_back(rect);
	rect = { 1120,480,128,32 };
	maze_rects.push_back(rect);

	// Initialize the terrain matrix (for each cell a zero value indicates it's a wall)
	
	// (1st) initialize all cells to 1 by default
	for (int i = 0; i < num_cell_x; i++)
	{
		vector<int> terrain_col(num_cell_y, 1); 
		terrain.push_back(terrain_col);
	}
	// (2nd) set to zero all cells that belong to a wall
	int offset = CELL_SIZE / 2;
	for (int i = 0; i < num_cell_x; i++)
	{
		for (int j = 0; j < num_cell_y; j++)
		{
			Vector2D cell_center ((float)(i*CELL_SIZE + offset), (float)(j*CELL_SIZE + offset));
			for (unsigned int b = 0; b < maze_rects.size(); b++)
			{
				if (Vector2DUtils::IsInsideRect(cell_center, (float)maze_rects[b].x, (float)maze_rects[b].y, (float)maze_rects[b].w, (float)maze_rects[b].h))
				{
					terrain[i][j] = 0;
				    break;
				}  
			}
			
		}
	}

	// Add connections to all cells of the game (that are not walls)
	//40 X CELLS 24 Y CELLS
	for (int i = 0; i < num_cell_x; i++) {
		for (int j = 0; j < num_cell_y; j++) {

			if (terrain[i][j] == 1) {

				if (j < num_cell_y - 1 && terrain[i][j + 1] != 0) {
					graph.AddConnection(Vector2D(i, j), Vector2D(i, j + 1));
				}

				if (i < num_cell_x - 1 && terrain[i + 1][j] != 0) {
					graph.AddConnection(Vector2D(i, j), Vector2D(i + 1, j));
				}

				if (j > 0 && terrain[i][j - 1] != 0) {
					graph.AddConnection(Vector2D(i, j), Vector2D(i, j - 1));
				}

				if (i > 0 && terrain[i - 1][j] != 0) {
					graph.AddConnection(Vector2D(i, j), Vector2D(i - 1, j));
				}

			}
		}
	}

}

bool ScenePlanning::loadTextures(char* filename_coin)
{
	SDL_Surface *image = IMG_Load(filename_coin);
	if (!image) {
		cout << "IMG_Load: " << IMG_GetError() << endl;
		return false;
	}
	coin_texture = SDL_CreateTextureFromSurface(TheApp::Instance()->getRenderer(), image);

	if (image)
		SDL_FreeSurface(image);

	return true;
}

Vector2D ScenePlanning::cell2pix(Vector2D cell)
{
	int offset = CELL_SIZE / 2;
	return Vector2D(cell.x*CELL_SIZE + offset, cell.y*CELL_SIZE + offset);
}

Vector2D ScenePlanning::pix2cell(Vector2D pix)
{
	return Vector2D((float)((int)pix.x/CELL_SIZE), (float)((int)pix.y / CELL_SIZE));
}

bool ScenePlanning::isValidCell(Vector2D cell)
{
	if ((cell.x < 0) || (cell.y < 0) || (cell.x >= terrain.size()) || (cell.y >= terrain[0].size()) )
		return false;
	return !(terrain[(unsigned int)cell.x][(unsigned int)cell.y] == 0);
}