#include <iostream>
#include <list>
#include <windows.h>
#include <string>
#include <fstream>
#include "World.h"
#include "Organism.h"
#include "Wolf.h"
#include "Sheep.h"
#include "Fox.h"
#include "Turtle.h"
#include "Antelope.h"
#include "Grass.h"
#include "Dandelion.h"
#include "Guarana.h"
#include "Belladona.h"
#include "Hogweed.h"
#include "Human.h"


#define ts to_string
#define addDebug debugList.push_back

using namespace std;

class Organism;

World::World(string name, int sizeX, int sizeY) : Name(name), sizeX(sizeX), sizeY(sizeY), turn(0) {
	if (sizeX <= 0) {
		cout << "Invalid sizeX. Setting to default size of 10." << endl;
		sizeX = 10;
	}
	if (sizeY <= 0) {
		cout << "Invalid sizeX. Setting to default size of 10." << endl;
		sizeY = 10;
	}
	map = new char* [sizeX];
	for (int i = 0; i < sizeX; i++) {
		map[i] = new char[sizeY];
		for (int j = 0; j < sizeY; j++) {
			map[i][j] = '.';
		}
	}
}

void World::setName(string name) { Name = name; }
string World::getName() { return Name; }
void World::setTurn(int t) { turn = t; }
int World::getTurn() { return turn; }
char** World::getMap() { return map; }
int World::getSizeX() { return sizeX; }
int World::getSizeY() { return sizeY; }
bool World::getOccupance(int x, int y) {
	if (x < 0 || x >= sizeX || y < 0 || y >= sizeY) {
		return 0;
	}
	return map[y][x] != '.'; // Assuming '.' indicates empty space
}
list<Organism*> World::getOrganisms() { return organisms; }

void World::sortOrganisms() {
	// Sorting elements by initiative
	organisms.sort([](Organism* a, Organism* b) {
		if(a->getInitiative() != b->getInitiative())
			return a->getInitiative() > b->getInitiative();
		else
			return a->getAge() > b->getAge(); // Sort by age if initiative is the same
		});
}

void World::addOrganism(Organism* org)
{
	ofstream wyjscie("addOrganism.txt");

	// Adding organism to the list
	organisms.push_back(org);

	wyjscie << org->getSymbol() << "\n";

	// Adding organism to the map
	int x = org->getX();
	int y = org->getY();
	if (x >= 0 && x < sizeX && y >= 0 && y < sizeY) {
		map[x][y] = org->getSymbol();
	}
	else {
		cout << "Organism coordinates out of bounds." << endl;
	}

	

	// Add debug information
	//addDebug("Added organism: " + org->getName() + " at (" + ts(x) + ", " + ts(y) + ")");
}

void World::removeOrganism(Organism* org)
{
	organisms.remove(org);
	int x = org->getX();
	int y = org->getY();
	if (x >= 0 && x < sizeX && y >= 0 && y < sizeY) {
		map[x][y] = '.'; // Assuming '.' indicates empty space
	}
	else {
		cout << "Organism coordinates out of bounds." << endl;
	}
	delete org; // Free the memory allocated for the organism
}

void World::display() {
	clearConsole(); // Clear the console before displaying
	cout << "World: " << Name << endl;
	cout << "Turn: " << turn << endl;
	for (int i = 0; i < sizeY; i++) {
		COORD pos = { 1, 3+i }; // Set cursor position to (0, 2)
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos); // Set cursor position
		cout << " ";
		for (int j = 0; j < sizeX; j++) {
			if (colloredPositions.count({ i, j })) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
			}
			else {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			}
			cout << map[i][j] << " "; // Print the map
		}
		cout << endl;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	colloredPositions.clear(); // Clear colored positions after displaying
	drawBorderWithBuffer(sizeY + 2, sizeX + 2); // Draw border with buffer
	writeDebugInfo();
}

void World::displaySpecialInfo() {
	COORD pos{ 10, sizeY + 10};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	cout << "S - Save the game\n";
	COORD pos2{ 10, sizeY + 11 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos2);
	cout << "L - Load the game\n";
	COORD pos3{ 10, sizeY + 12 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos3);
	cout << "Enter - play next turn\n";
	cin.get();
}

void World::waitForCommands() {
	cin >> noskipws;
	char commands;
	cin >> commands;
	cin >> skipws;
	switch (commands) {
	case 's':
	case 'S':
		saveTheWorld();
		break;
	case 'L':
	case 'l':
		loadTheWorld();
		break;
	}
}

void World::saveTheWorld() {
	ofstream zapis("zapisGry.txt");
	zapis << turn << " " << sizeX << " " << sizeY << endl;
	for (auto& org : organisms) {
		if(org->getisAlive() == true) zapis << org->getSymbol() << " " << org->getStrength() << " " << org->getAge() << " " << org->getX() << " " << org->getY() << endl;
	}
}

void World::loadTheWorld() {
	ifstream zapis("zapisGry.txt");
	zapis >> turn >> sizeX >> sizeY;
	char symbol;
	int strenght, age, posX, posY;
	
	organisms.clear();
	for (int i = 0; i < sizeY; i++) {
		delete[] map[i];
	}
	delete[] map;

	map = new char* [sizeY];
	for (int i = 0; i < sizeY; i++) {
		map[i] = new char[sizeX];
		for (int j = 0; j < sizeX; j++) {
			map[i][j] = '.';
		}
	}

	while (zapis >> symbol) {
		zapis >> strenght >> age >> posX >> posY;
			switch (symbol) {
			case 'W': {
				Wolf* news = new Wolf(posX, posY, this);
				news->setAge(age);
				news->setStrength(strenght);
				addOrganism(news);
				break;
			}
			case 'S': {
				Sheep* news = new Sheep(posX, posY, this);
				news->setAge(age);
				news->setStrength(strenght);
				addOrganism(news);
				break;
			}
			case 'F': {
				Fox* news = new Fox(posX, posY, this);
				news->setAge(age);
				news->setStrength(strenght);
				addOrganism(news);
				break;
			}
			case 'T': {
				Turtle* news = new Turtle(posX, posY, this);
				news->setAge(age);
				news->setStrength(strenght);
				addOrganism(news);
				break;
			}
			case 'A': {
				Antelope* news = new Antelope(posX, posY, this);
				news->setAge(age);
				news->setStrength(strenght);
				addOrganism(news);
				break;
			}
			case 'G': {
				Grass* news = new Grass(posX, posY, this);
				news->setAge(age);
				news->setStrength(strenght);
				addOrganism(news);
				break;
			}
			case 'B': {
				Belladona* news = new Belladona(posX, posY, this);
				news->setAge(age);
				news->setStrength(strenght);
				addOrganism(news);
				break;
			}
			case 'D': {
				Dandelion* news = new Dandelion(posX, posY, this);
				news->setAge(age);
				news->setStrength(strenght);
				addOrganism(news);
				break;
			}
			case 'L': {
				Guarana* news = new Guarana(posX, posY, this);
				news->setAge(age);
				news->setStrength(strenght);
				addOrganism(news);
				break;
			}
			case 'H': {
				Hogweed* news = new Hogweed(posX, posY, this);
				news->setAge(age);
				news->setStrength(strenght);
				addOrganism(news);
				break;
			}
			case 'O': {
				Human* news = new Human(posX, posY, this);
				news->setAge(age);
				news->setStrength(strenght);
				addOrganism(news);
				break;
			}
		}
	}
}

void World::drawBorderWithBuffer(int height, int width) {
	width = (width - 2) * 2 + 3; // Adjust width for buffer
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { 0, 2 };

	// Górna ramka
	SetConsoleCursorPosition(hConsole, pos);
	std::cout << "+";
	for (int i = 0; i < width - 2; ++i) std::cout << "-";
	std::cout << "+";

	// Boczne ramki i środek
	for (int y = 1; y < height - 1; ++y) {
		pos.Y = y+2;
		pos.X = 0;
		SetConsoleCursorPosition(hConsole, pos);
		std::cout << "|";

		pos.X = width - 1;
		SetConsoleCursorPosition(hConsole, pos);
		std::cout << "|";
	}

	// Dolna ramka
	pos.Y = height + 1;
	pos.X = 0;
	SetConsoleCursorPosition(hConsole, pos);
	std::cout << "+";
	for (int i = 0; i < width - 2; ++i) std::cout << "-";
	std::cout << "+";
}

void World::clearConsole() {
	COORD topLeft = { 0, 0 };
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen;
	DWORD written;

	GetConsoleScreenBufferInfo(console, &screen);
	FillConsoleOutputCharacterA(
		console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	FillConsoleOutputAttribute(
		console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
		screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	SetConsoleCursorPosition(console, topLeft);
}

void World::writeDebugInfo() {
	int y = 3;
	COORD pos = { sizeX * 2 + 20, ++y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	cout << "Debug Info: ";
	for (const auto& info : debugList) {
		COORD pos = { sizeX * 2 + 20, ++y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
		cout << info << endl;
	}
	cout << endl;
	debugList.clear(); // Clear debug list after displaying
}

void World::start() {
	cout << "Enter the number of organisms of each species: ";
	cout << "Wolf: ";
	int wolfCount;
	cin >> wolfCount;
	cout << "Sheep: ";
	int sheepCount;
	cin >> sheepCount;
	cout << "Fox: ";
	int foxCount;
	cin >> foxCount;
	cout << "Turtle: ";
	int turtleCount;
	cin >> turtleCount;
	cout << "Antelope: ";
	int antelopeCount;
	cin >> antelopeCount;
	cout << "Grass: ";
	int grassCount;
	cin >> grassCount;
	cout << "Dandelion: ";
	int dandelionCount;
	cin >> dandelionCount;
	cout << "Guarana: ";
	int guaranaCount;
	cin >> guaranaCount;
	cout << "Belladona: ";
	int belladonaCount;
	cin >> belladonaCount;
	cout << "Hogweed: ";
	int hogweedCount;
	cin >> hogweedCount;
	// Add organisms to the world
	int x, y;
	for (int i = 0; i < min(wolfCount, 5); i++) {
		do {
			y = rand() % sizeX;
			x = rand() % sizeY;
		} while (getOccupance(x, y));
		Wolf* newWolf = new Wolf(x, y, this);
		addOrganism(newWolf);
		map[x][y] = 'W';
	}
	for (int i = 0; i < min(sheepCount, 5); i++) {
		do {
			y = rand() % sizeX;
			x = rand() % sizeY;
		} while (getOccupance(x, y));
		addOrganism(new Sheep(x, y, this));
		map[x][y] = 'S';
	}
	for (int i = 0; i < min(foxCount, 5); i++) {
		do {
			y = rand() % sizeX;
			x = rand() % sizeY;
		} while (getOccupance(x, y));
		addOrganism(new Fox(x, y, this));
		map[x][y] = 'F';
	}
	for (int i = 0; i < min(turtleCount, 5); i++) {
		do {
			y = rand() % sizeX;
			x = rand() % sizeY;
		} while (getOccupance(x, y));
		addOrganism(new Turtle(x, y, this));
		map[x][y] = 'T';
	}
	for (int i = 0; i < min(antelopeCount, 5); i++) {
		do {
			y = rand() % sizeX;
			x = rand() % sizeY;
		} while (getOccupance(x, y));
		addOrganism(new Antelope(x, y, this));
		map[x][y] = 'A';
	}
	for (int i = 0; i < min(grassCount, 5); i++) {
		do {
			y = rand() % sizeX;
			x = rand() % sizeY;
		} while (getOccupance(x, y));
		addOrganism(new Grass(x, y, this));
		map[x][y] = 'G';
	}
	for (int i = 0; i < min(dandelionCount, 5); i++) {
		do {
			y = rand() % sizeX;
			x = rand() % sizeY;
		} while (getOccupance(x, y));
		addOrganism(new Dandelion(x, y, this));
		map[x][y] = 'D';
	}
	for (int i = 0; i < min(guaranaCount, 5); i++) {
		do {
			y = rand() % sizeX;
			x = rand() % sizeY;
		} while (getOccupance(x, y));
		addOrganism(new Guarana(x, y, this));
		map[x][y] = 'U';
	}
	for (int i = 0; i < min(belladonaCount, 5); i++) {
		do {
			y = rand() % sizeX;
			x = rand() % sizeY;
		} while (getOccupance(x, y));
		addOrganism(new Belladona(x, y, this));
		map[x][y] = 'B';
	}
	for (int i = 0; i < min(hogweedCount, 5); i++) {
		do {
			y = rand() % sizeX;
			x = rand() % sizeY;
		} while (getOccupance(x, y));
		addOrganism(new Hogweed(x, y, this));
		map[x][y] = 'H';
	}
	do {
		y = rand() % sizeX;
		x = rand() % sizeY;
	} while (getOccupance(x, y));
	addOrganism(new Human(x, y, this));
	map[x][y] = 'O';
}

World::~World() {
	for (int i = 0; i < sizeY; i++) {
		delete[] map[i];
	}
	delete[] map;
}

bool World::whetherHumanAlive() {
	for (auto& org : organisms) {
		if (org->getName() == "Human") {
			return org->getisAlive();
		}
	}
	return false;
}