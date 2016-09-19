#ifndef _MAIN_MENU_H_
#define _MAIN_MENU_H_

#include "../../scene.h"

enum MAIN_MENU_LAYERS {
	MAIN_MENU_LAYER_LOGO,
	MAIN_MENU_LAYER_WARNING,
	MAIN_MENU_LAYER_START
};

class mainMenu: public scene {
public:
	mainMenu();
   ~mainMenu();

   virtual void stateMachine();
   virtual void start();

private:
	std::vector<nTexture*> textureList;

	MAIN_MENU_LAYERS layers;
};

#endif