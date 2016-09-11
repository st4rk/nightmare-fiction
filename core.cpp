#include "core.h"


core::core()  {
	coreLoop = false;
}

core::~core() {
	coreLoop = false;
}


/*
 * start
 * this function initialize all engine stuff
 * no return
 */
void core::start() {
	m_Render.initGL();
	m_Input.setInputInfo(m_Render.getContext(), &c_Pad);
	m_Utils.setContext(m_Render.getContext());

	coreLoop = true;

	mainLoop();
}

/*
 * mainLoop
 * this function deal with the main loop
 * no return
 */
void core::mainLoop() {

	nTexture *test = m_Render.loadTexture("resource/TITLE00.PNG");

	while (coreLoop) {
		m_Render.clearScene();
		
		m_Utils.renderRectangle(test->id, m_Render.getTexUnit());

		m_Render.swapBuffers();
	}

}