/**
 * Project Tangram
 */


#pragma once
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
