#pragma once
#include <iostream>
#include "World.h"

class Organism {
private:
	string name;
	int x;
	int y;
	int strength;
	int initiative;
	char symbol;
	bool isAlive = true; // Flag to check if the organism is alive
	World* world; // Pointer to the world object
protected:
	int age;
public:
	Organism(int x, int y, World* world);

	void setX(int x);
	int getX();

	void setY(int y);
	int getY();

	void setSymbol(char symbol);
	char getSymbol();

	void setStrength(int strength);
	int getStrength();

	void setInitiative(int initiative);
	int getInitiative();

	bool getisAlive() const; // Getter for isAlive
	void setisAlive(bool alive); // Setter for isAlive

	void setName(string name);
	std::string getName();

	World* getWorld() const;
	virtual void setAge(int age);
	virtual int getAge();

	void move(int newX, int newY);
	virtual void tryMove(int* x, int* y);	

	virtual void addOrganism(int X, int Y) = 0; // Pure virtual function for adding an organism
	virtual void action() = 0; // Pure virtual function for action
	virtual void collision(Organism* other) = 0; // Pure virtual function for collision
	virtual bool respondToCollision(Organism* other) = 0; // Pure virtual function for responding to collision
};