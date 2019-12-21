/**
 * Project Tangram
 */


#ifndef _GAME_H
#define _GAME_H

#include "../View/Drawable.h"
#include "../View/Button.h"
#include "../Model/Shape.h"

#include <list>
#include <vector>

class Game: public Drawable {
public :
    Game();
private :
    std::vector<Shape<double>> pieces;
    std::list<Button> buttons;
};

Game::Game() {


}

#endif //_GAME_H
