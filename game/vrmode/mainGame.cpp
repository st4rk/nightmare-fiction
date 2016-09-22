#include "mainGame.h"

mainGame::mainGame() {

}


mainGame::~mainGame() {

}

void mainGame::start() {

}

bool whatever = false;

void mainGame::stateMachine() {
	// TEST CODE, PLEASE, IGNORE IT
	static glm::mat4 pers = glm::perspective(glm::radians(45.0f), (float) 640 / (float) 480, 0.1f, 100.0f);
	m_Render->setProjectionMtx(pers);

	static _menu introTest[TOTAL_ENTRY];
	introTest[0] = {"Voce caiu no\nconto do canario...", -0.95f, -0.65f, 0.0f};
	introTest[1] = {"Sera que voce\nconseguira escapar?", -0.95f, -0.65f, 0.0f};

	/*switch (layers) {
		case MAIN_GAME_LAYER_INIT:

		break;

		case MAIN_GAME_LAYER_GAME:

		break;

	}*/
	if (!whatever) 
		m_Utils->renderText(introTest[0].text, introTest[0].x, introTest[0].y, introTest[0].z, FONT_TYPE_BIG, {1.0f, 1.0f, 1.0f, 1.0f});
	else
		m_Utils->renderText(introTest[1].text, introTest[1].x, introTest[1].y, introTest[1].z, FONT_TYPE_BIG, {1.0f, 1.0f, 1.0f, 1.0f});


	if (m_Input->getPad() & CORE_PAD_OK) {
		whatever = true;
	}
}

