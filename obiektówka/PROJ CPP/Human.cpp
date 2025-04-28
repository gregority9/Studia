#include <iostream>
#include <string>
#include <windows.h>
#include "Human.h"
#include "Animal.h"


#define addDebug getWorld()->debugList.push_back
#define color getWorld()->colloredPositions.insert
#define ts to_string

using namespace std;

Human::Human(int x, int y, World* world) : Animal(x, y, world) {
	setStrength(5);
	setInitiative(4);
	setSymbol('O');
	setName("Human");
	setisAlive(true);
}

void Human::action() {
	// Implement the action logic for the animal
	addDebug(getName() + " is taking action.");
	char** map = getWorld()->getMap();
	////SuperPower Options
	COORD pos = { 60, 2 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	trySuperPower();
	// Select direction according to the player's choice
	
	int newX = getX(), newY = getY();
	tryMove(&newX, &newY);
	// Add colloring
	color({ getX(), getY() });
	color({ newX, newY });
	// Increment age
	setAge(getAge() + 1);
	// Check for collisions
	if (getWorld()->getOccupance(newX, newY)) {
		// Collision detected
		addDebug("Collision detected at (" + ts(newX) + ", " + ts(newY) + ").");
		// Placeholder for collision logic
		list<Organism*> organisms = getWorld()->getOrganisms();
		for (auto& other : organisms) {
			if (other->getX() == newX && other->getY() == newY && other->getisAlive() == true) {
				// Collision with another organism
				addDebug(other->getName() + " was attacked by " + getName());
				collision(other);
				if (getisAlive() == false) {
					addDebug("Human is dead :///");
				}
				break; // Exit loop after collision
			}
		}
	}
	else {
		addDebug("No collision at (" + ts(newX) + ", " + ts(newY) + ").");
		addDebug("Moved from (" + ts(getX()) + ", " + ts(getY()) + ") to (" + ts(newX) + ", " + ts(newY) + ").");
		map[getX()][getY()] = '.'; // Clear the current position on the map
		move(newX, newY); // Move to the new position
		map[getX()][getY()] = getSymbol(); // Set the new position on the map
	}
}

void Human::tryMove(int* newX, int* newY) {
	char dirr = ' ';
	cin >> dirr;
	setDirection(dirr);
	switch (getDirection()) {
		case 'A':
			*newX = getX();
			*newY = getY() - 1;
			break;
		case 'D':
			*newX = getX();
			*newY = getY() + 1;
			break;
		case 'W':
			*newX = getX() - 1;
			*newY = getY();
			break;
		case 'S':
			*newX = getX() + 1;
			*newY = getY();
			break;
		default:
			tryMove(newX, newY);
			break;
	}
	if (*newX >= 0 && *newX <= getWorld()->getSizeX() && *newY >= 0 && *newY <= getWorld()->getSizeY()) {
		addDebug("Human moved to (" + ts(*newX) + ", " + ts(*newY) + ").");
	}
	else {
		addDebug("Human can't move outside the world boundaries.");
		tryMove(newX, newY);
	}
}

void Human::addOrganism(int X, int Y) {
	Human* human = new Human(X, Y, getWorld());
	getWorld()->addOrganism(human);
	addDebug("New human created at (" + ts(X) + ", " + ts(Y) + ").");
}

void Human::setDirection(char dirr) {
	this->dirr = dirr;
}
char Human::getDirection() {
	return dirr;
}

void Human::trySuperPower() {
	if (superPowerCooldown > 0) {
		superPowerCooldown--;
		setStrength(getStrength() - 1); // Decrease strength by 1 for each turn
		addDebug("Super power cooldown: " + ts(superPowerCooldown));
	}
	else {
		cout << "Would you like to use super power? (Y/N): ";
		char choice;
		cin >> choice;
		switch(choice){
		case 'Y':
		case 'y':
			addDebug("Super power activated!");
			superPowerCooldown = 5; // Set cooldown to 5 turns
			setStrength(getStrength() + 5); // Increase strength by 5
			break;
		default:
			addDebug("Super power not activated.");
			break;
		}
	}
}