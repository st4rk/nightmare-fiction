#ifndef _MAIN_GAME_H_
#define _MAIN_GAME_H_

#include "../../scene.h"

#include "../common/player.h"
#include "../common/rdt.h"
#include "../common/debug.h"
#include "../common/room.h"


/*    in game key list       */
#define KEY_UP       0b00000001
#define KEY_DOWN     0b00000010
#define KEY_LEFT     0b00000100
#define KEY_RIGHT    0b00001000
#define KEY_OK       0b00010000 
#define KEY_CANCELL  0b00100000

enum TEXTURE_LIST {
	TEXTURE_DEBUG,
	TEXTURE_SHADOW
};

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

	player m_Player;
	debug  m_Debug;
	modelObj m_Shadow;
	RDT    pRDT;


	std::unique_ptr<nf3d>  pModel;

	std::vector<std::unique_ptr<nTexture>> textureList;
	std::vector<std::unique_ptr<nTexture>> pRDT_tex;
	std::vector<GLuint> shaderList;

	bool isDebug;

	unsigned int currState;

	MAIN_GAME_LAYERS layers;

};


#endif