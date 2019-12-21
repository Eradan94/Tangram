/**
 * Project Tangram
 */


#ifndef _MENU_H
#define _MENU_H

#include "Drawable.h"
#include "Button.h"

#include <list>

class Menu: public Drawable {
public :

private :
    std::list<Button> buttons;
};

#endif //_MENU_H
