#pragma once
#include <iostream>
#include "Plant.h"

class Belladona : public Plant {
public:
	Belladona(int x, int y, World* world);
	bool respondToCollision(Organism* other) override;
	void addOrganism(int X, int Y) override;
};