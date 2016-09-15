#ifndef _MAIN_MENU_H_
#define _MAIN_MENU_H_

#include "../../scene.h"

class mainMenu: public scene {
public:
	mainMenu();
   ~mainMenu();

   virtual void stateMachine();

private:
	nTexture* menu;

};

#endif