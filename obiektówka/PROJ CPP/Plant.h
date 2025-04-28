#pragma once
#include "Organism.h"

class Plant : public Organism {
private:
	int chanceOfSpread = 30;
public:
	Plant(int x, int y, World* world);


	virtual void action() override;
	virtual void collision(Organism* other) override;
	void spread();
	virtual void addOrganism(int X, int Y) override;
	virtual bool respondToCollision(Organism* other) override;
};