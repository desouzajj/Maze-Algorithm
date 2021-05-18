#pragma once
#include "Point.h"
#include "Player.h"
#include <iostream>
#include <string>
#include <vector>
#include<set>

using namespace std;
class Maze
{

private:
	char* maze;
	set <Point> bonusPos;
	int height, width;
	Player player;
	const char _player = 'P'; 
	const char wall = 'x';
	const char bonus = '$';
	Point exit;
	vector <Point> path;

	Point celltopoint(int index);
	int cellindex(Point cell);

public:
	Maze(string path);
	void LoadMaze(string path);
	void Print();
	void AStar(Point start, Point end);
	bool checkmaze(Point p);
	int Heuristic(Point start, Point end);
	void MovePlayer();
	void FindBonus();
	void Solvebonus();
	void FindExit();
	~Maze();
};


