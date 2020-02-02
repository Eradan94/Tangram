/**
 * Project Tangram
 */

#include "../../include/Model/Point.h"
#include "../../include/Model/Piece.h"
#include "../../include/Controller/GameManager.h"

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
