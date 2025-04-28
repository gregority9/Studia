#include <iostream>
#include <string>
#include "Grass.h"

#define addDebug getWorld()->debugList.push_back
#define ts to_string

using namespace std;

Grass::Grass(int x, int y, World* world) : Plant(x, y, world) {
	setStrength(0);
	setInitiative(0);
	setSymbol('G');
	setName("Grass");
}

void Grass::addOrganism(int X, int Y) {
	Grass* grass = new Grass(X, Y, getWorld());
	getWorld()->addOrganism(grass);
	addDebug("New grass created at (" + ts(X) + ", " + ts(Y) + ").");
}