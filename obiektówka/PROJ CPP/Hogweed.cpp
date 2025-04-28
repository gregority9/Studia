#include <iostream>
#include <string>
#include <cstdlib>
#include "Hogweed.h"
#include "Plant.h"
#include "Animal.h"
#include "Organism.h"

#define addDebug getWorld()->debugList.push_back
#define ts to_string
#define myMap getWorld()->getMap()

using namespace std;

Hogweed::Hogweed(int x, int y, World* world) : Plant(x, y, world) {
	setStrength(10);
	setInitiative(0);
	setSymbol('H');
	setName("Hogweed");
}

void Hogweed::action() {
	//usmiercic wszystkie organizmy w sasiedztwie
	while (true) {
		Animal* animal = getAnimalInRange();
		if (animal == nullptr) {
			break;
		}
		else {
			addDebug("Hogweed has killed " + animal->getName() + " at (" + ts(animal->getX()) + ", " + ts(animal->getY()) + ").");
			myMap[animal->getX()][animal->getY()] = '.'; // Remove the animal from the map
			animal->setisAlive(false); // Mark the animal as dead
			return;
		}
	}
}

Animal* Hogweed::getAnimalInRange() {
	//sprawdzic czy w sasiedztwie jest jakis organizm
	//jesli tak to zwroc go
	for (auto& org : getWorld()->getOrganisms()) {
		if (abs(org->getX() - getX()) <= 1 && abs(org->getY() - getY()) <= 1) {
			if (Animal* animal = dynamic_cast<Animal*>(org)) {
				return animal;
			}
		}
	}

	//jesli nie to zwroc nullptr
	return nullptr;
}

bool Hogweed::respondToCollision(Organism* other) {
	other->setStrength(other->getStrength() + 3);
	myMap[getX()][getY()] = '.';
	other->move(getX(), getY());
	myMap[getX()][getY()] = other->getSymbol();
	addDebug(other->getName() + " has eaten hogweed.");
	setisAlive(false);
	return true;
}

void Hogweed::addOrganism(int X, int Y) {
	Hogweed* hogweed = new Hogweed(X, Y, getWorld());
	getWorld()->addOrganism(hogweed);
	addDebug("New hogweed created at (" + ts(X) + ", " + ts(Y) + ").");
}