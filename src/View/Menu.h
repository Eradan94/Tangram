/**
 * Project Tangram
 */


#pragma once
#include "Drawable.h"
#include "Button.h"

#include <list>

class Menu: public Drawable {
public :

private :
    std::list<Button> buttons;
};

