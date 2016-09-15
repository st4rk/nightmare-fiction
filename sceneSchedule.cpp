#include "sceneSchedule.h"


schedule::schedule() {
	m_Render = nullptr;
	m_Utils  = nullptr;
	m_Input  = nullptr;

	n_Scene = 0;
}

schedule::~schedule() {
	m_Render = nullptr;
	m_Utils  = nullptr;
	m_Input  = nullptr;

	n_Scene = 0;

	if (sceneList.size() > 0) {
		for (unsigned int i = 0; i < sceneList.size(); i++) {
			delete [] sceneList[i];
			sceneList[i] = nullptr;
		}
	}
}

/*
 * start
 * set the object context to the schedule, it will be used later by the scene objects
 * no return
 */
void schedule::start(render *m_Render, utils *m_Utils, input *m_Input) {
	this->m_Render = m_Render;
	this->m_Utils  = m_Utils;
	this->m_Input  = m_Input;

	mainMenu *node = new mainMenu;

	sceneList.push_back(static_cast<scene*>(node));

}

/*
 * dispatch
 * check and dispatch the scene that should be executed
 * no return
 */
void schedule::dispatch() {

	switch (sceneList[n_Scene]->getState()) {
		case SCENE_STATE_INIT:
			sceneList[n_Scene]->setContext(m_Render, m_Utils, m_Input);
			sceneList[n_Scene]->setState(SCENE_STATE_RUN);
		break;

		case SCENE_STATE_RUN:
			sceneList[n_Scene]->stateMachine();
		#ifdef DEBUG
			m_Utils->renderText("Scene: 1", -0.9f, 0.9f, 0.0f, FONT_TYPE_SMALL, m_Render->getTexUnit());
		#endif
		break;

		case SCENE_STATE_SLEEP:

		break;

		case SCENE_STATE_END:

		break;
	}
}