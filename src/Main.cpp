/**
 * \file Main.cpp
 * \brief Main class.
 * \author Biguenet Denis & Gosset Severin
 * \date 22/02/2019
 *
 * Main class of Tangram project.
 *
 */

#include "../include/Model/Point.h"
#include "../include/Model/Piece.h"
#include "../include/Controller/GameManager.h"

using namespace std;

int main(int argc, char const *argv[]) {
	GameManager manager;
	manager.initMainMenuButtons();
	while (manager.isRunning())
	{
        manager.play();
	}
	return 0;
}
