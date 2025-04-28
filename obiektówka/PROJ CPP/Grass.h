#pragma once
#include <iostream>
#include "Plant.h"

class Grass : public Plant {
public:
	Grass(int x, int y, World* world);
	void addOrganism(int X, int Y) override;
};