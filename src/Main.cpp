/**
 * Project Tangram
 */

#include "Model/Point.h"
#include "Model/Piece.h"
#include "Controller/GameManager.h"

using namespace std;

int main(int argc, char const *argv[]) {
	GameManager manager(argv[1]);
	manager.initMainGameButtons();
	while (manager.isRunning())
	{
		manager.play();
	}
	return 0;
}
