#include "mainGame.h"

float z = 0.0f;

mainGame::mainGame() {

}


mainGame::~mainGame() {

}

void mainGame::start() {
	nTexture* tex = m_Render->loadTexture("resource/models/2.TIM");
	pModel.reset(new nf3d("resource/models/2.EMD", tex));

	m_Entity.setModel(2);

	pModel->setAnimSection(EMD_SECTION_4);
	pModel->setSec4Animation(STAND_SEC4_ANIM_RUNNING);

	layers = MAIN_GAME_LAYER_INIT;
}

void mainGame::checkInput() {
	static bool pButton = false;


	if (m_Input->getPad() & CORE_PAD_UP) {
		if (!pButton) {
			z += 100.0f;
			pButton = true;
		}
	} else if (m_Input->getPad() & CORE_PAD_DOWN) {
		if (!pButton) {
			z -= 100.0f;
			pButton = true;
		}
	} else {
		pButton = false;
	}

}

void mainGame::logic() {
	/* perspective */
	static glm::mat4 mtx_pers = glm::perspective(glm::radians(45.0f), (float) 640 / (float) 480, 0.1f, 100000.0f);

	glm::mat4 mtx_cam = glm::lookAt(glm::vec3(0.0f, 2.0f, 6800.0f),
								    glm::vec3(1.0f, 1.0f, 5.0f),
								    glm::vec3(0.0f, 1.0f, 0.0f));


	m_Render->setProjectionMtx(mtx_pers);
	m_Render->setViewMtx(mtx_cam);

    /*
     * Call the animation update in nf3d
     */
    pModel->runAnimation();
    
    m_Utils->renderNF3D(pModel.get());

}

void mainGame::stateMachine() {
	static _menu introTest[] { 
        {"Voce caiu na\narmadilha do coiote", -0.95f, -0.65f, 0.0f},
        {"Sera que voce\nconseguira escapar?", -0.95f, -0.65f, 0.0f}
    };


	switch (layers) {
		case MAIN_GAME_LAYER_INIT: {
			checkInput();
				
 
			logic();

	        m_Utils->renderText(introTest[0].text, introTest[0].x, introTest[0].y, introTest[0].z, FONT_TYPE_BIG, {1.0f, 1.0f, 1.0f, 1.0f});

		}
		break;

		case MAIN_GAME_LAYER_GAME: {

		}
		break;
	}


}

