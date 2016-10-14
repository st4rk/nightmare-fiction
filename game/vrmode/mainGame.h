#ifndef _MAIN_GAME_H_
#define _MAIN_GAME_H_

#include "../../scene.h"
#include "../../physics.h"

#include "../common/player.h"
#include "../common/rdt.h"
#include "../common/debug.h"

enum MAIN_GAME_LAYERS {
	MAIN_GAME_LAYER_INIT,
	MAIN_GAME_LAYER_GAME
};

enum SHADER_LIST {
	SHADER_UI,
	SHADER_MODEL
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
	void renderGame();

	void loadRoom();

	player m_Player;
	debug  m_Debug;

	std::unique_ptr<nf3d>  pModel;
	std::unique_ptr<RDT>   pRDT;
	std::vector<nTexture*> pRDT_tex;
	std::vector<GLuint> shaderList;

	bool isDebug;

	unsigned int currState;

	MAIN_GAME_LAYERS layers;
};


#endif