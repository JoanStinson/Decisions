#pragma once
#include <vector>
#include <time.h>
#include "Scene.h"
#include "Agent.h"
#include "Path.h"
#include "Graph.h"
#include <iostream>
#include <time.h>
#include "BankState.h"
#include "HomeState.h"
#include "MineState.h"
#include "SaloonState.h"
using namespace std;

class ScenePlanning : public Scene {

public:
	ScenePlanning();
	~ScenePlanning();
	void update(float dtime, SDL_Event *event);
	void draw();
	const char* getTitle();

private:
	vector<Agent*> agents;
	Vector2D coinPosition;
	Vector2D currentTarget;
	int currentTargetIndex;
	Path path;
	int num_cell_x;
	int num_cell_y;
	bool draw_grid;
	std::vector<SDL_Rect> maze_rects;
	void drawMaze();
	void drawCoin();
	SDL_Texture *background_texture;
	SDL_Texture *coin_texture;
	void initMaze();
	bool loadTextures(char* filename_coin, char* filename_bg);
	vector<vector<int>> terrain;
	Vector2D cell2pix(Vector2D cell);
	Vector2D pix2cell(Vector2D pix);
	bool isValidCell(Vector2D cell);

	// Our stuff
	void InitConnections();
	Graph graph;
	Vector2D start;
	vector<Vector2D> astar;
	Vector2D pastLocation;
	bool isFirstState;
};
