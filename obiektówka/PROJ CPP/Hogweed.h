#pragma once
#include <iostream>
#include "Plant.h"
#include "Animal.h"

class Hogweed : public Plant {
public:
	Hogweed(int x, int y, World* world);
	void action() override;
	Animal* getAnimalInRange();
	bool respondToCollision(Organism* other) override;
	void addOrganism(int X, int Y) override;
};