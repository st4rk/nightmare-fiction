#ifndef _SCENE_SCHEDULE_H_
#define _SCENE_SCHEDULE_H_

#include <iostream>
#include <vector>

#define DEBUG

#include "scene.h"

/* ==================================================
 * game scene list
 * this is not part of the engine framework itself
 * here we have each game scene, like: main menu, 
 * in game, and other kind of stuff
 */
#include "game/mainmenu/mainMenu.h"
#include "game/mainmenu/config.h"
#include "game/vrmode/mainGame.h"

enum GAME_SCENE_LIST {
	GAME_SCENE_MAIN_MENU,
	GAME_SCENE_CONFIG,
	GAME_SCENE_VR_MODE,
	GAME_SCENE_END
};


class schedule {
public:
	schedule();
   ~schedule();

   void start(render *m_Render, utils *m_Utils, input *m_Input);
   void dispatch();


   unsigned int getSceneNum() const;

private:
	render *m_Render;
	utils  *m_Utils;
	input  *m_Input;

	unsigned int n_Scene;

	std::vector<scene*> sceneList;

};

#endif