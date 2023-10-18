#include "Maze.h"
#include <fstream>
#include <algorithm>
#include <set>
#include <map>
void Maze::LoadMaze(string path) {
	fstream file;
	string line;
	string buffermaze;

	file.open(path, ios::in);
	if (!file) {
		cout << "File not found";
		return;
	}
	height = 0;

	while (getline(file, line)) {	
		buffermaze += line;
		height++;
	}

	width = line.size();
	file.close();

	maze = new char[buffermaze.size()];

	for (int i = 0; i < buffermaze.size(); i++) {
		maze[i] = buffermaze[i];

		if (maze[i] == bonus) {
			bonusPos.insert(celltopoint(i));
		}
		if (maze[i] == _player) {
			player.setposition(celltopoint(i));
			exit = celltopoint(i);
		}
	}
}

Maze::~Maze() {
	delete[] maze;
}

Maze::Maze(string path) {
	LoadMaze(path);
}


Point Maze::celltopoint(int index) {
	
	Point temp;
	temp.y = index / width;
	temp.x = index - temp.y * width;
	return temp;
}

int Maze::cellindex(Point cell) {
	return cell.y * width + cell.x;
}

void Maze::Print() {

	system("cls");
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			cout << maze[cellindex({j,i})];
		}
		cout << endl;
	}
	cout << player.gethp();
}

bool Maze::checkmaze(Point p) {
	return (p.x < width && p.x >= 0) && (p.y < height && p.y >= 0);
}

void Maze::AStar(Point start, Point end)
{
	path.clear();
	vector <Node> openlist;
	set <Point> closelist;
	map <Point, Point> backtrack;
	openlist.push_back({ 0,0, player.getposition() });

	while (!openlist.empty()) 
	{
		sort(openlist.begin(), openlist.end());
		Node temp = *openlist.begin();
		Node bestnode;
		bestnode.f = INT_MAX;
		openlist.erase(openlist.begin());
		closelist.insert(temp.pos);

		if (temp.pos.x == end.x && temp.pos.y == end.y) 
		break;
		Point direction [4] = { {1,0}, {-1, 0 }, {0, 1}, {0, -1} };
		for (int x = 0; x < 4; x++) 
		{
			Point next;
			next.x = temp.pos.x + direction[x].x;
			next.y = temp.pos.y + direction[x].y;
			if (closelist.find(next) != closelist.end()) continue;
			if (maze[cellindex(next)] == wall) continue;
			if (!checkmaze(next)) continue;	
			int h = Heuristic(next, end);
			int g = temp.g + 1;
			int f = h + g;
			openlist.push_back({ g, f, next });
			backtrack.insert(pair<Point, Point>(next, temp.pos));
		}		
	}
	Point step = end;
	while (step.x != start.x || step.y != start.y) 
	{
		path.push_back(step);
		step = backtrack[step];		
	}
}

void Maze::MovePlayer() {
	if (path.empty())
		return;
	for (int i = 0; i < path.size(); i++) {
		Point temp = path[path.size() - 1 - i];
		maze[cellindex(player.getposition())] = ' ';
		if (maze[cellindex(temp)] == bonus)
		{
			player.Changehp(11);
			bonusPos.erase(bonusPos.find(temp));
		}

		player.Changehp(-1);
		player.setposition(temp);
		maze[cellindex(player.getposition())] = _player;
	
		Print();
	}
}

void Maze::Solvebonus() {
	while (!bonusPos.empty()) {
		FindBonus();
		MovePlayer();
	}

	FindExit();
}


void Maze::FindExit() {
	AStar(player.getposition(), exit);
	MovePlayer();
}
void Maze::FindBonus() {

	vector<vector<Point>> BonusPath;
	for (auto b : bonusPos) {
		AStar(player.getposition(), b);
		BonusPath.push_back(path);
		
	}

	int temp = INT_MAX;
	for (int i = 0; i < BonusPath.size(); i++)
	{
		if (BonusPath[i].size() < temp)
		{
			temp = BonusPath[i].size();
			path = BonusPath[i];
		}
	}
}

int Maze::Heuristic(Point start, Point end)
{
	return abs(start.x - end.x) + abs(start.y - end.y);
}
