#ifndef _MAIN_GAME_H_
#define _MAIN_GAME_H_

#include "../../scene.h"

#include "entity.h"

enum MAIN_GAME_LAYERS {
	MAIN_GAME_LAYER_INIT,
	MAIN_GAME_LAYER_GAME
};

class mainGame : public scene {
public:

	mainGame();
	~mainGame();

	virtual void stateMachine();
	virtual void start();


private:
	void checkInput();
	void logic();

	entity m_Entity;
	std::unique_ptr<nf3d> pModel;

	MAIN_GAME_LAYERS layers;
};


#endif