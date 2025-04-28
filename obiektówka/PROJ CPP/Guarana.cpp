#include <iostream>
#include <string>
#include "Guarana.h"

#define addDebug getWorld()->debugList.push_back
#define ts to_string
#define myMap getWorld()->getMap()

using namespace std;

Guarana::Guarana(int x, int y, World* world) : Plant(x, y, world) {
	setStrength(0);
	setInitiative(0);
	setSymbol('L');
	setName("Guarana");
}

void Guarana::addOrganism(int X, int Y) {
	Guarana* guarana = new Guarana(X, Y, getWorld());
	getWorld()->addOrganism(guarana);
	addDebug("New guarana created at (" + ts(X) + ", " + ts(Y) + ").");
}

bool Guarana::respondToCollision(Organism* other) {
	other->setStrength(other->getStrength() + 3);
	myMap[getX()][getY()] = '.';
	other->move(getX(), getY());
	myMap[getX()][getY()] = other->getSymbol();
	addDebug(other->getName() + " has eaten guarana and gained 3 strength.");
	setisAlive(false);
	return true;
}