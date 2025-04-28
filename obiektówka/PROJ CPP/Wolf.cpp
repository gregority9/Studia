#include <iostream>
#include "Animal.h"
#include <fstream>
#include <string>
#include "Wolf.h"

#define addDebug getWorld()->debugList.push_back
#define ts to_string

Wolf::Wolf(int x, int y, World* world) : Animal(x, y, world) {
	setStrength(9);
	setInitiative(5);
	setSymbol('W');
	setName("Wolf");
}

void Wolf::addOrganism(int X, int Y) {
	Wolf* wolf = new Wolf(X, Y, getWorld());
	getWorld()->addOrganism(wolf);
	addDebug("New wolf created at (" + ts(X) + ", " + ts(Y) + ").");
}