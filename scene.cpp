#include "scene.h"

scene::scene() {
	m_Render = nullptr;
	m_Utils  = nullptr;
	m_Input  = nullptr;

	sceneState = SCENE_STATE_INIT;
	nextScene = 0;
}

scene::~scene() {
	m_Render = nullptr;
	m_Utils  = nullptr;
	m_Input  = nullptr;

	sceneState = SCENE_STATE_END;
	nextScene = 0;
}

/*
 * sceneState
 * set new state
 * no return
 */
void scene::setState(const SCENE_STATE& sceneState) {
	this->sceneState = sceneState;
}

/*
 * setContext
 * this function set the scene objects context
 * no return
 */
void scene::setContext(render *m_Render, utils *m_Utils, input *m_Input, sound *m_Sound) {
	this->m_Render = m_Render;
	this->m_Utils  = m_Utils;
	this->m_Input  = m_Input;
	this->m_Sound  = m_Sound;
}

/*
 * getNextScene
 * return next scene
 * return unsigned int of scene index
 */
unsigned int scene::getNextScene() const { return nextScene; }

/*
 * getState
 * return scene state
 * return SCENE_STATE type
 */
SCENE_STATE scene::getState() const { return sceneState; }

/* 
 * stateMachine
 * used to handle all scene state
 */
void scene::stateMachine() {

}

/*
 * start
 * start all scene resource
 */
void scene::start() {

}

void scene::setState(SCENE_STATE& sceneState) { 
	this->sceneState = sceneState;
}

void scene::setNextScene(unsigned int& nextScene) {
	this->nextScene = nextScene;
}