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
	m_Input.setInputInfo(m_Render.getContext());
	m_Utils.start(&m_Render);

	m_Schedule.start(&m_Render, &m_Utils, &m_Input);

	coreLoop = true;

	mainLoop();
}

/*
 * mainLoop
 * this function deal with the main loop
 * no return
 */
void core::mainLoop() {

	while (coreLoop) {
		m_Render.clearScene();

			m_Schedule.dispatch();

		m_Render.swapBuffers();
	}

}