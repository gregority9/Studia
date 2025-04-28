#include <iostream>
#include <random>
#include <list>
#include <string>
#include "Fox.h"
#include "World.h"
#include "Animal.h"

#define ts to_string
#define addDebug getWorld()->debugList.push_back
#define color getWorld()->colloredPositions.insert

enum Direction { UP, DOWN, LEFT, RIGHT };



Fox::Fox(int x, int y, World* world) : Animal(x, y, world) {
	setStrength(3);
	setInitiative(7);
	setSymbol('F');
	setName("Fox");
}
void Fox::addOrganism(int X, int Y) {
	Fox* fox = new Fox(X, Y, getWorld());
	getWorld()->addOrganism(fox);
	std::cout << "New fox created at (" << X << ", " << Y << ")." << std::endl;
}

void Fox::action() {
	// Implement the action logic for the animal
	//addDebug(getName() + " is taking action.");
	char** map = getWorld()->getMap();
	// Example: Move in a random direction
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dis(0, 3); // 0 to 3 for 4 directions
	// Randomly select a direction
	bool goodDirr = false;
	bool possibleMove = false;
	bool noCollision = true;
	int direction = -1;
	int newX, newY;
	int iter = 0;
	while (!possibleMove) {
		if (++iter > 1000) {
			addDebug("Fox is stuck in a loop, breaking out.");
			break;
		}
		while (!goodDirr) {
			direction = dis(gen);
			switch (direction)
			{
			case UP:
				if (getY() - 1 >= 0) goodDirr = true;
				break;
			case DOWN:
				if (getY() + 1 < getWorld()->getSizeY()) goodDirr = true;
				break;
			case LEFT:
				if (getX() - 1 >= 0) goodDirr = true;
				break;
			case RIGHT:
				if (getX() + 1 < getWorld()->getSizeX()) goodDirr = true;
				break;
			}
		}
		switch (direction) {
		case UP:
			newX = getX();
			newY = getY() - 1;
			break;
		case DOWN:
			newX = getX();
			newY = getY() + 1;
			break;
		case LEFT:
			newX = getX() - 1;
			newY = getY();
			break;
		case RIGHT:
			newX = getX() + 1;
			newY = getY();
			break;
		}

		// Increment age
		setAge(getAge() + 1);

		if (getWorld()->getOccupance(newX, newY)) {
			// Collision detected
			//addDebug("Collision detected at (" + ts(newX) + ", " + ts(newY) + ").");
			// Check for collisions
			list<Organism*> organisms = getWorld()->getOrganisms();
			for (auto other : organisms) {
				if (other->getX() == newX && other->getY() == newY && other->getisAlive() == true) {
					// Collision with another organism
					if (other->getStrength() > getStrength()) {
						addDebug("Fox can't get into this tile, trying again");
					}
					else {
						addDebug(other->getName() + " was attacked by " + getName());
						collision(other);
						possibleMove = true;
						noCollision = false;
					}
					break; // Exit loop after collision
				}
			}
		}
		else {
			possibleMove = true;
		}
	}
	if (noCollision) {
		//addDebug("No collision at (" + ts(newX) + ", " + ts(newY) + ").");
		addDebug("Moved from (" + ts(getX()) + ", " + ts(getY()) + ") to (" + ts(newX) + ", " + ts(newY) + ").");
		// Add colloring
		color({ getX(), getY() });
		color({ newX, newY });
		map[getX()][getY()] = '.'; // Clear the current position on the map
		move(newX, newY); // Move to the new position
		map[getX()][getY()] = getSymbol(); // Set the new position on the map
	}
}
