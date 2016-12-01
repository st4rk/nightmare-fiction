#ifndef _SCENE_H_
#define _SCENE_H_

#include "render.h"
#include "input.h"
#include "utils.h"
#include "sound.h"

enum SCENE_STATE {
	SCENE_STATE_INIT,
	SCENE_STATE_RUN,
	SCENE_STATE_SLEEP,
	SCENE_STATE_END
};


class scene {
public:
	scene();
    virtual ~scene();

   	void setState(const SCENE_STATE& sceneState);
    void setContext(render *m_Render, utils *m_Utils, input *m_Input, sound *m_Sound);
    virtual void stateMachine();
    virtual void start();

    unsigned int getNextScene() const;
    SCENE_STATE getState() const;

    void setState(SCENE_STATE& sceneState);
    void setNextScene(unsigned int& nextScene);

protected:
	SCENE_STATE sceneState;

	unsigned int nextScene;

	render *m_Render;
	utils  *m_Utils;
	input  *m_Input;
	sound  *m_Sound;
};

#endif