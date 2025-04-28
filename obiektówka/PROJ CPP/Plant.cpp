#include <iostream>
#include "Plant.h"
#include <random>
#include <string>

#define addDebug getWorld()->debugList.push_back
#define myMap getWorld()->getMap()
#define ts to_string
#define color getWorld()->colloredPositions.insert

using namespace std;

Plant::Plant(int x, int y, World* world)
	: Organism(x, y, world){
	setSymbol('P');
	setStrength(0);
	setInitiative(0);
	setName("Plant");
}

void Plant::action() {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dis(1, 100);
	int chance = dis(gen);
	color({ getX(), getY() });
	if (chance < chanceOfSpread) {
		spread();
	}
	else {
		//addDebug(getName() + " is not spreading this turn.");
	}
}

void Plant::collision(Organism* other) {

}

void Plant::spread() {
	int newX = getX(), newY = getY();
	int iter = 0;
	while (getWorld()->getOccupance(newX, newY)) {
		if (++iter > 1000) {
			addDebug("Plant is stuck in a loop, breaking out.");
			break;
		}
		tryMove(&newX, &newY);
	}
	addOrganism(newX, newY);
	myMap[newX][newY] = getSymbol();
	color({ newX, newY });
	//addDebug("New plant created at (" + ts(newX) + ", " + ts(newY) + ").");
}

void Plant::addOrganism(int X, int Y) {
	Plant* plant = new Plant(X, Y, getWorld());
	getWorld()->addOrganism(plant);
	addDebug("New plant created at (" + ts(X) + ", " + ts(Y) + ").");
}

bool Plant::respondToCollision(Organism* other) {
	// Default: Plants don't cause fights, they just get eaten
	myMap[other->getX()][other->getY()] = '.';
	other->move(getX(), getY());
	myMap[getX()][getY()] = other->getSymbol();
	// Add debug message
	addDebug(getName() + " was eaten by " + other->getName() + " and destroyed");
	setisAlive(false);
	return true;
}