#include "sceneSchedule.h"


schedule::schedule() {
	m_Render = nullptr;
	m_Utils  = nullptr;
	m_Input  = nullptr;

	n_Scene = GAME_SCENE_VR_MODE;
}

schedule::~schedule() {
	m_Render = nullptr;
	m_Utils  = nullptr;
	m_Input  = nullptr;

	n_Scene = 0;
}

/*
 * allocScene
 * alloc the scene object
 * no return
 */
void schedule::allocScene(const unsigned int& scene) {
	switch (scene) {
		case GAME_SCENE_MAIN_MENU: {
			if (sceneList[scene] == nullptr) {
				sceneList[scene].reset(new mainMenu);
			}
		}
		break;

		case GAME_SCENE_CONFIG: {
			if (sceneList[scene] == nullptr) {
				sceneList[scene].reset(new menuConfig);
			}
		}
		break;

		case GAME_SCENE_VR_MODE: {
			if (sceneList[scene] == nullptr) {
				sceneList[scene].reset(new mainGame);
			}
		}
		break;

		default:
			std::cout << "Internal error : Scene " << scene << " not found" << std::endl;
		break;
	}
}

/*
 * start
 * set the object context to the schedule, it will be used later by the scene objects
 * no return
 */
void schedule::start(render *m_Render, utils *m_Utils, input *m_Input, sound *m_Sound) {
	this->m_Render = m_Render;
	this->m_Utils  = m_Utils;
	this->m_Input  = m_Input;
	this->m_Sound  = m_Sound;

	sceneList.resize(3);
	sceneList[0].reset(new mainMenu);
	sceneList[1].reset(new menuConfig);
	sceneList[2].reset(new mainGame);

}

/*
 * dispatch
 * check and dispatch the scene that should be executed
 * no return
 */
void schedule::dispatch() {

	/* get scene state */
	switch (sceneList[n_Scene]->getState()) {
		case SCENE_STATE_INIT: {
			/* init scene */
			sceneList[n_Scene]->setContext(m_Render, m_Utils, m_Input, m_Sound);
			sceneList[n_Scene]->start();
			sceneList[n_Scene]->setState(SCENE_STATE_RUN);
		}
		break;

		case SCENE_STATE_RUN: {
			/* run current scene */
			sceneList[n_Scene]->stateMachine();
		}
		break;

		case SCENE_STATE_SLEEP: {
			/* get current scene */
			unsigned int oldScene = n_Scene;
			/* set the next scene to schedule */
			n_Scene = sceneList[n_Scene]->getNextScene();

			/* set the old scene object to sleep state */
			sceneList[oldScene]->setState(SCENE_STATE_SLEEP);

			/* check if the next scene is valid */
			if (sceneList[n_Scene] == nullptr) {
				std::cout << "ohay" << std::endl;
				allocScene(n_Scene);
			}

			/* check if the scene is sleeping */
			if (sceneList[n_Scene]->getState() == SCENE_STATE_SLEEP) 
				sceneList[n_Scene]->setState(SCENE_STATE_RUN);

		}
		break;

		case SCENE_STATE_END: {
			/* get current scene */
			unsigned int oldScene = n_Scene;
			
			/* set the next scene to schedule */
			n_Scene = sceneList[n_Scene]->getNextScene();

			/* free the old scene object */
			sceneList[oldScene].reset(nullptr);

			/* check if the next scene is valid */
			if (sceneList[n_Scene] == nullptr) {
				allocScene(n_Scene);
			}

			/* verify if scene is sleeping, if yes, set it to RUN */
			if (sceneList[n_Scene]->getState() == SCENE_STATE_SLEEP) 
				sceneList[n_Scene]->setState(SCENE_STATE_RUN);
		}
		break;
	}
}


unsigned int schedule::getSceneNum() const { return n_Scene; }