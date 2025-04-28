#pragma once
#include <iostream>
#include "Organism.h"

using namespace std;

class Animal : public Organism {
public:
	Animal(int x, int y, World* world);

	void setAge(int age) override;
	int getAge() override;

	virtual void action() override;
	virtual void collision(Organism* other) override;
	virtual bool respondToCollision(Organism* other) override;
	void fight(Organism* other);
	void breed(Organism* other);
	virtual void addOrganism(int X, int Y);
};