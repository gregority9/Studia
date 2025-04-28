#pragma once
#include <iostream>
#include "Animal.h"

using namespace std;
class Fox : public Animal {
public:
	Fox(int x, int y, World* world);

	virtual void action() override;

	void addOrganism(int X, int Y) override;
};
