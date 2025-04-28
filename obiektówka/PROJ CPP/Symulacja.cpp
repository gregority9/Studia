#include <iostream>
#include <windows.h>
#include "World.h"
#include "Organism.h"
#include "Animal.h"
#include "Wolf.h"
#include "Sheep.h"
#include "Fox.h"
#include "Turtle.h"
#include "Antelope.h"

#define addDebug myWorld->debugList.push_back

using namespace std;


int main() {
	cout << "Welcome to the simulation!" << endl;
	cout << "Enter the size of the world Y: ";
	int sizeX;
	cin >> sizeX;
	if (sizeX < 1 || sizeX > 50) {
		cout << "Invalid size. Setting to default size of 20." << endl;
		sizeX = 20;
	}
	cout << "Enter the size of the world X: ";
	int sizeY;
	cin >> sizeY;
	if (sizeY < 1 || sizeY > 50) {
		cout << "Invalid size. Setting to default size of 20." << endl;
		sizeY = 20;
	}
	World* myWorld = new World("MyWorld", sizeX, sizeY);
	myWorld->start();
	while (true) {
		
		myWorld->clearConsole();
		myWorld->setTurn(myWorld->getTurn() + 1);
		myWorld->display();
		COORD pos = { 10, myWorld->getSizeY()+8};
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
		/*cin.ignore();
		cin.get();
		myWorld->displaySpecialInfo();
		myWorld->waitForCommands();
		cout << endl;*/
		int sizeOfList = myWorld->getOrganisms().size();
		myWorld->sortOrganisms();
		int it = 0;
		list<Organism*> lista = myWorld->getOrganisms();
		for (auto& org : lista) {
			if (++it > sizeOfList) break; // Skip the rest of the organisms if we have already processed all of them
			if (org->getisAlive() == false) continue;
			if (org->getName() == "Human") {
				myWorld->clearConsole();
				myWorld->display();
				addDebug("Human Turn");
				COORD pos = { 60, 1 };
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				cout << "Your turn: ";
				org->action();
				cin.ignore();
			}
			else {
				//myWorld->clearConsole();
				org->action();
				/*myWorld->display();
				cin.get();*/
			}
		}
		if (myWorld->whetherHumanAlive() == false) {
			myWorld->clearConsole();
			myWorld->debugList.clear();
			addDebug("Koniec gry, człowiek umarł");
			myWorld->display();
			cin.ignore();
			break;
		}
	}
	return 0;
}