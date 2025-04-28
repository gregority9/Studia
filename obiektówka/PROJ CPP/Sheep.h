#pragma once
#include <iostream>
#include "Animal.h"

using namespace std;

class Sheep : public Animal {
public:
	Sheep(int x, int y, World* world);

	void addOrganism(int X, int Y) override;
};
