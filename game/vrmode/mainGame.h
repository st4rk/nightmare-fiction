#ifndef _MAIN_GAME_H_
#define _MAIN_GAME_H_

#include <ctime>
#include "../../scene.h"

#include "../common/player.h"
#include "../common/rdt.h"
#include "../common/debug.h"
#include "../common/room.h"
#include "../common/inventory.h"
#include "../common/AI/zombie.h"


/*    in game key list       */
#define KEY_UP       0b00000001
#define KEY_DOWN     0b00000010
#define KEY_LEFT     0b00000100
#define KEY_RIGHT    0b00001000
#define KEY_1        0b00010000 
#define KEY_2        0b00100000
#define KEY_3        0b01000000 
#define KEY_4        0b10000000 

enum TEXTURE_LIST {
	TEXTURE_DEBUG,
	TEXTURE_SHADOW
};

enum MAIN_GAME_LAYERS {
	MAIN_GAME_LAYER_INIT,
	MAIN_GAME_LAYER_GAME,
	MAIN_GAME_LAYER_INV,
	MAIN_GAME_LAYER_DOOR
};

enum SHADER_LIST {
	SHADER_UI,
	SHADER_MODEL
};

struct rankTmr {
	int ms;
	int sec;
	int min;
	int tick;
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
	void renderInv();

	player m_Player;
	debug  m_Debug;
	modelObj m_Shadow;
	RDT    pRDT;


	/** player model and weapon information */
	std::unique_ptr<nf3d>  pModel;
	std::unique_ptr<nf3d>  pWeapon;
	//std::unique_ptr<nf3d>  eModel;

	/** Enemy entity model and information */
	std::vector<std::unique_ptr<nf3d>> em_List;
	std::vector<entity> e_List;
	std::vector<item> itemList;
	std::vector<std::unique_ptr<nTexture>> textureList;
	std::vector<std::unique_ptr<nTexture>> pRDT_tex;
	std::vector<std::unique_ptr<soundChunk>> stepList;
	std::vector<std::unique_ptr<nTexture>> invUI;
	std::vector<GLuint> shaderList;
	std::vector<std::unique_ptr<musicChunk>> musicList;

	bool isDebug;

	unsigned int currState;

	MAIN_GAME_LAYERS layers;

	rankTmr rTmr;
};


#endif