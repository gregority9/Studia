#pragma once
#include <iostream>
#include "Plant.h"

class Guarana : public Plant {
public:
	Guarana(int x, int y, World* world);
	//do funkcji respondToCollision dodac +3 sily dla zwierzaka ktory to zje
	bool respondToCollision(Organism* other) override;
	void addOrganism(int X, int Y) override;
};