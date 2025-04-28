#pragma once
#include <iostream>
#include "Plant.h"

#define addDebug getWorld()->debugList.push_back
#define ts to_string

using namespace std;

class Dandelion : public Plant {
public:
	Dandelion(int x, int y, World* world);
	void action() override;
	void addOrganism(int X, int Y) override;
};
