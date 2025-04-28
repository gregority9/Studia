#include <iostream>
#include <random>
#include "Organism.h"

enum Directions {UP, DOWN, LEFT, RIGHT};

using namespace std;


Organism::Organism(int x, int y, World* world)
	: x(x), y(y), world(world){
	this->strength = 0; // Default strength
	this->initiative = 0; // Default initiative
	this->symbol = '.'; // Default symbol
	this->name = "Organism"; // Default name
	this->age = 0;
}

void Organism::setX(int x) {
	this->x = x;
}
int Organism::getX() {
	return x;
}
void Organism::setY(int y) {
	this->y = y;
}
int Organism::getY() {
	return y;
}
void Organism::setSymbol(char symbol) {
	this->symbol = symbol;
}
char Organism::getSymbol() {
	return symbol;
}
void Organism::setStrength(int strength) {
	this->strength = strength;
}
int Organism::getStrength() {
	return strength;
}
void Organism::setInitiative(int initiative) {
	this->initiative = initiative;
}
int Organism::getInitiative() {
	return initiative;
}
void Organism::setName(string name) {
	this->name = name;
}
std::string Organism::getName() {
	return name;
}
bool Organism::getisAlive() const {
	return isAlive;
}
void Organism::setisAlive(bool alive) {
	this->isAlive = alive;
}

World* Organism::getWorld() const {
	return world;
}
void Organism::setAge(int age) {
	this->age = age;
}
int Organism::getAge() {
	return age;
}

void Organism::move(int newX, int newY) {
	x = newX;
	y = newY;
}

void Organism::tryMove(int* newX, int* newY) {
	// Move in a random direction
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dis(0, 3); // 0 to 3 for 4 directions
	bool goodDirr = false;
	int direction = -1;
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
		*newX = getX();
		*newY = getY() - 1;
		break;
	case DOWN:
		*newX = getX();
		*newY = getY() + 1;
		break;
	case LEFT:
		*newX = getX() - 1;
		*newY = getY();
		break;
	case RIGHT:
		*newX = getX() + 1;
		*newY = getY();
		break;
	}
}