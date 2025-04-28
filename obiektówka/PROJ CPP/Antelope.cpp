#include <iostream>
#include <string>
#include "Antelope.h"
#include <random>

#define ts to_string
#define addDebug getWorld()->debugList.push_back
#define myMap getWorld()->getMap()

Antelope::Antelope(int x, int y, World* world) : Animal(x, y, world) {
	setStrength(4);
	setInitiative(4);
	setSymbol('A');
	setName("Antelope");
}

void Antelope::action() {
	// Implement the action logic for the Antelope
	//addDebug("Antelope is taking action number 1.");
	Animal::action();
	//addDebug("Antelope is taking action number 2.");
	Animal::action();
}

void Antelope::collision(Organism* other) {
	//addDebug("Antelope collided with " + other->getName() + ".");
	//checking whether the same species
	if (other != nullptr && other->getSymbol() == this->getSymbol()) {
		//addDebug("Same species collision!");
		breed(other);
	}
	else {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dis(0, 1); // 0 or 1
		int chance = dis(gen);
		if (chance == 0) {
			//addDebug("Antelope is fighting with " + other->getName() + ".");
			Animal::fight(other);
		}
		else {
			addDebug("Antelope escaped from the collision.");
			// Escaping from the collision
			int newX = getX(), newY=getY();
			int iter = 0;
			while (getWorld()->getOccupance(newX, newY)) {
				if (++iter > 1000) {
					addDebug("Antelope is stuck in a loop, breaking out.");
					break;
				}
				tryMove(&newX, &newY);
			}
		}
	}
}

void Antelope::addOrganism(int X, int Y) {
	Antelope* antelope = new Antelope(X, Y, getWorld());
	getWorld()->addOrganism(antelope);
	addDebug("New antelope created at (" + ts(X) + ", " + ts(Y) + ").");
}

bool Antelope::respondToCollision(Organism* other) {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dis(0, 1); // 0 or 1
	int chance = dis(gen);
	if (chance == 0) {
		addDebug("Antelope is escaping from the collision.");
		int newX = getX(), newY = getY();
		int iter = 0;
		while (getWorld()->getOccupance(getX(), getY())) { // Check if the new position is occupied
			if (++iter > 1000) {
				addDebug("Antelope is stuck in a loop, breaking out.");
				break;
			}
			tryMove(&newX, &newY); // Try to move to a new position
		}
		myMap[other->getX()][other->getY()] = '.'; // Remove the other organism from the map
		other->move(getX(), getY()); // Move the other organism to the antelope's position
		myMap[getX()][getY()] = other->getSymbol(); // Set the new position on the map
		move(getX(), getY()); // Move the antelope to the new position
		myMap[getX()][getY()] = 'A'; // Set the new position on the map
		return true; // Escape
	}
	else {
		//addDebug("Antelope is not escaping from the collision.");
		return false; // Not escape
	}
}