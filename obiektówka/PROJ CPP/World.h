#pragma once
#include <iostream>
#include <list>
#include <vector>
#include <unordered_set>
#include <functional>

using namespace std;

class Organism; // Forward declaration of Organism class

class World {
private:
	string Name;
	int turn;
	int sizeX, sizeY;
	list<Organism*> organisms;
	char** map;
	struct HashFunction {
		size_t operator()(const pair<int, int>& p) const {
			return hash<int>()(p.first) ^ hash<int>()(p.second);
		}
	};
public:
	vector<string> debugList;
	unordered_set<pair<int, int>, HashFunction> colloredPositions;

	World(string name, int sizeX, int sizeY);

	void setName(string name);
	string getName();
	void setTurn(int t);
	int getTurn();
	char** getMap();
	int getSizeX();
	int getSizeY();
	bool getOccupance(int x, int y);
	list<Organism*> getOrganisms();
	void sortOrganisms();
	bool whetherHumanAlive();
	void addOrganism(Organism* org);
	void removeOrganism(Organism* org);
	void display();
	void displaySpecialInfo();
	void waitForCommands();
	void saveTheWorld();
	void loadTheWorld();
	void drawBorderWithBuffer(int width, int height);
	void clearConsole();
	void writeDebugInfo();
	void start();
	virtual ~World();
};