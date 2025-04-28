#include <iostream>
#include <list>
#include <random>
#include <string>
#include "Animal.h"
#include "Organism.h"
#include "Antelope.h"

#define ts to_string
#define addDebug getWorld()->debugList.push_back
#define color getWorld()->colloredPositions.insert

enum Direction { UP, DOWN, LEFT, RIGHT };

using namespace std;

Animal::Animal(int x, int y, World* world)
	: Organism(x, y, world)
{
	setSymbol('A');
	setStrength(1);
	setInitiative(1);
	setName("Animal");
}
void Animal::setAge(int age) {
	this->age = age;
}
int Animal::getAge() {
	return age;
}
void Animal::action() {
	// Implement the action logic for the animal
	//addDebug(getName() + " is taking action.");
	char** map = getWorld()->getMap();
	// Randomly select a direction
	int newX, newY;
	tryMove(&newX, &newY);
	// Add colloring
	color({ getX(), getY() });
	color({ newX, newY });
	// Increment age
	this->age++;
	// Check for collisions
	if (getWorld()->getOccupance(newX, newY)) {
		// Collision detected
		//addDebug("Collision detected at (" + ts(newX) + ", " + ts(newY) + ").");
		// Placeholder for collision logic
		list<Organism*> organisms = getWorld()->getOrganisms();
		for (auto other : organisms) {
			if (other->getX() == newX && other->getY() == newY && other->getisAlive() == true) {
				// Collision with another organism
				//addDebug(other->getName() + " was attacked by " + getName());
				collision(other);
				break; // Exit loop after collision
			}
		}
	}
	else {
		//addDebug("No collision at (" + ts(newX) + ", " +ts(newY) + ").");
		//addDebug("Moved from (" + ts(getX()) + ", " + ts(getY()) + ") to (" + ts(newX) + ", " + ts(newY) + ").");
		map[getX()][getY()] = '.'; // Clear the current position on the map
		move(newX, newY); // Move to the new position
		map[getX()][getY()] = getSymbol(); // Set the new position on the map
	}
}

void Animal::collision(Organism* other) {
	// Implement the collision logic for the animal
	// Example: Check if the other organism is of the same species
	if (other != nullptr && other->getSymbol() == this->getSymbol()) {
		//addDebug("Same species collision!");
		breed(other);
	}
	else {
		//addDebug("Different species collision!");
		//addDebug("Attacker: " + getName() + " vs Defender: " + other->getName());
		//addDebug("Attacker strength: " + ts(getStrength()) + " vs Defender strength: " + ts(other->getStrength()));
		if (!other->respondToCollision(this)) {
			//addDebug("Defender did not respond to collision, proceeding to fight.");
			fight(other); // Call the fight method if the other organism doesn't respond to the collision
		}
	}
}

bool Animal::respondToCollision(Organism* other) {
	// Default behavior: do nothing
	return false;
}

void Animal::fight(Organism* other) {
	if (this->getStrength() >= other->getStrength()) {
		addDebug(this->getName() + " kills " + other->getName());
		getWorld()->getMap()[getX()][getY()] = '.'; // Clear the old position on the map
		move(other->getX(), other->getY()); // Move to the other organism's position
		other->setisAlive(false); // Set the other organism as dead
		getWorld()->getMap()[getX()][getY()] = getSymbol(); // Set the new position on the map

		//addDebug(ts(getX()) + " " + ts(getY()) + " " + getWorld()->getMap()[getX()][getY()] + " " + getName() + " " + getSymbol());
	}
	else {
		addDebug(other->getName() + " kills " + this->getName());
		getWorld()->getMap()[getX()][getY()] = '.'; // Set the new position on the map
		setisAlive(false); // Set the current organism as dead
	}
}

void Animal::breed(Organism* other) {
	// Implement the breeding logic for the animal
	//addDebug("Breeding with another organism.");
	// Example: Create a new organism at an adjacent empty space
	getWorld()->display();
	int newX = getX();
	int newY = getY();
	char** map = getWorld()->getMap();
	int iter = 0;
	while (getWorld()->getOccupance(newX, newY)) {
		iter++;
		if (iter > 1000) {
			addDebug("No free space for breeding.");
			return;
		}
		// Randomly select a new position
		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<> dis(1, 8);
		int newPos = dis(gen);
		switch (newPos) {
			case 1:
				newX = getX() - 1; newY = getY(); break; // Left from me
			case 2:
				newX = getX() + 1; newY = getY(); break; // Right from me
			case 3:
				newX = getX(); newY = getY() - 1; break; // Up from me
			case 4:
				newX = getX(); newY = getY() + 1; break; // Down from me
			case 5:
				newX = other->getX() - 1; newY = other->getY(); break; // Left from other
			case 6:
				newX = other->getX() + 1; newY = other->getY(); break; // Right from other
			case 7:
				newX = other->getX(); newY = other->getY() - 1; break; // Up from other
			case 8:
				newX = other->getX(); newY = other->getY() + 1; break; // Down from other
		}
		if (newX < 0) newX = 0;
		if (newY < 0) newY = 0;
		if (newX >= getWorld()->getSizeX()) newX = getWorld()->getSizeX() - 1;
		if (newY >= getWorld()->getSizeY()) newY = getWorld()->getSizeY() - 1;
	}
	// Create a new animal and add it to the world
	addOrganism(newX, newY);
}



void Animal::addOrganism(int X, int Y) {
	Animal* offspring = new Animal(X, Y, getWorld());
	getWorld()->addOrganism(offspring);
	addDebug("New animal created at (" + ts(X) + ", " + ts(Y) + ").");
}



