#include <iostream>
#include <string>
#include "Dandelion.h"

#define addDebug getWorld()->debugList.push_back
#define ts to_string

using namespace std;

Dandelion::Dandelion(int x, int y, World* world) : Plant(x, y, world) {
	setStrength(0);
	setInitiative(0);
	setSymbol('D');
	setName("Dandelion");
}

void Dandelion::action() {
	Plant::action();
	Plant::action();
	Plant::action();
}

void Dandelion::addOrganism(int X, int Y) {
	Dandelion* dandelion = new Dandelion(X, Y, getWorld());
	getWorld()->addOrganism(dandelion);
	addDebug("New dandelion created at (" + ts(X) + ", " + ts(Y) + ").");
}