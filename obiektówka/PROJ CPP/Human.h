#pragma once
#include <iostream>
#include "Animal.h"

class Human : public Animal {
private:
	char dirr = 'W';
	int superPowerCooldown = 0;
public:
	Human(int x, int y, World* world);
	void action() override;
	void tryMove(int* newX, int* newY) override;
	void addOrganism(int X, int Y) override;
	void setDirection(char direction);
	char getDirection();
	void trySuperPower();
};