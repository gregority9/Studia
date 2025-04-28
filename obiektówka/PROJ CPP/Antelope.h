#pragma once
#include <iostream>
#include "Animal.h"

class Antelope : public Animal {
private:
	bool isBeingAttacked = false;
public:
	Antelope(int x, int y, World* world);

	void setisBeingAttacked(bool attacked) { isBeingAttacked = attacked; }
	bool getisBeingAttacked() { return isBeingAttacked; }

	void action() override;
	void collision(Organism* other) override;
	void addOrganism(int X, int Y) override;
	bool respondToCollision(Organism* other) override;
};