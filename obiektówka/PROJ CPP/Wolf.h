#pragma once
#include <iostream>
#include "Animal.h"

class Wolf : public Animal {
public:
	Wolf(int x, int y, World* world);

	void addOrganism(int X, int Y) override;
};
