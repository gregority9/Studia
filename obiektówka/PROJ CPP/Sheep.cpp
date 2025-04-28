#include <iostream>
#include "Animal.h"
#include "Sheep.h"


Sheep::Sheep(int x, int y, World* world) : Animal(x, y, world) {
	setStrength(4);
	setInitiative(4);
	setSymbol('S');
	setName("Sheep");
}

void Sheep::addOrganism(int X, int Y) {
	Sheep* sheep = new Sheep(X, Y, getWorld());
	getWorld()->addOrganism(sheep);
	std::cout << "New sheep created at (" << X << ", " << Y << ")." << std::endl;
}
