#ifndef _MAIN_GAME_H_
#define _MAIN_GAME_H_

#include "../../scene.h"

enum MAIN_GAME_LAYERS {
	MAIN_GAME_LAYER_INIT,
	MAIN_GAME_LAYER_GAME
};

#define TOTAL_ENTRY 3

class mainGame : public scene {
public:

	mainGame();
	~mainGame();

	virtual void stateMachine();
	virtual void start();


private:
	void checkInput();


};


#endif