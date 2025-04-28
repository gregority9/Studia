#include <iostream>
#include <string>
#include "Belladona.h"

#define addDebug getWorld()->debugList.push_back
#define ts to_string
#define myMap getWorld()->getMap()

using namespace std;

Belladona::Belladona(int x, int y, World* world) : Plant(x, y, world) {
	setStrength(99);
	setInitiative(0);
	setSymbol('B');
	setName("Belladona");
}


void Belladona::addOrganism(int X, int Y) {
	Belladona* belladona = new Belladona(X, Y, getWorld());
	getWorld()->addOrganism(belladona);
	addDebug("New belladona created at (" + ts(X) + ", " + ts(Y) + ").");
}

bool Belladona::respondToCollision(Organism* other) {
	// Belladona kills the organism that eats it
	addDebug(other->getName() + " has eaten belladona and died.");
	myMap[getX()][getY()] = '.';
	myMap[other->getX()][other->getY()] = '.';
	other->setisAlive(false);
	setisAlive(false);
	return true;
}