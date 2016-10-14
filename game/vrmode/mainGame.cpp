#include "mainGame.h"

mainGame::mainGame() {
	isDebug = false;
	currState = 0;
}


mainGame::~mainGame() {
	isDebug = false;
	currState = 0;
}

void mainGame::loadRoom() {
	/* Load RDT File */
	char fileName[0xFF];
	memset (fileName, 0, 0xFF);
	sprintf(fileName, "resource/stages/RDT/ROOM%d%02X0.RDT", m_Player.getStage(), m_Player.getMap());
	pRDT.reset(new RDT(fileName, RDT_TYPE_RE2));

	/* Load Backgrounds */
	pRDT_tex.clear();
	nTexture* tex = nullptr;

	for (unsigned int i = 0; i < pRDT->rdtHeader.nCut; i++) {
		memset (fileName, 0, 0xFF);
		sprintf(fileName, "resource/stages/PAK/ROOM%d%02X/%d.PNG", m_Player.getStage(), m_Player.getMap(), i);

		tex = m_Render->loadTexture(fileName);

		pRDT_tex.push_back(tex);	
	}

}

void mainGame::start() {
	/* load player model */
	nTexture* tex = m_Render->loadTexture("resource/models/2.TIM");
	pModel.reset(new nf3d("resource/models/2.EMD", tex));

	/* hard coded player information */
	m_Player.setStage(1);
	m_Player.setMap(6);
	m_Player.setCam(0);
	m_Player.setModel(2);
	m_Player.setAngle(90.0f);
	m_Player.setXYZ(glm::vec3(-25843.0f, 0, -479.0f));
	pModel->setAnimSection(EMD_SECTION_4);
	pModel->setSec4Animation(STAND_SEC4_ANIM_IDLE);
	m_Debug.currMap = 0;

	/* load room */
	loadRoom();

	/* load shaders, TODO: plz, you can do better, i know */
	GLuint currentShader = 0;
	currentShader = LoadShaders("game/shaders/vertexShader.glsl", "game/shaders/fragmentShader.glsl");
	shaderList.push_back(currentShader);
	currentShader = LoadShaders("game/shaders/modelVertex.glsl", "game/shaders/modelFragment.glsl");
	shaderList.push_back(currentShader);

	/* state machine initial state */
	layers = MAIN_GAME_LAYER_INIT;

	/* disable debug settings */
	isDebug = false;

}

void mainGame::checkInput() {
	static bool bPressed = false;


	switch (layers) {
		case MAIN_GAME_LAYER_INIT: {

		}
		break;

		case MAIN_GAME_LAYER_GAME: {
			if (isDebug) {
				/* debug settings */
				if (m_Input->getPad() & CORE_PAD_RIGHT) {
					if (!bPressed) {
						m_Debug.nextMap();
						bPressed = true;
					}
				} else if (m_Input->getPad() & CORE_PAD_LEFT) {
					if (!bPressed) {
						m_Debug.priorMap();
						bPressed = true;
					}
				} else if (m_Input->getPad() & CORE_PAD_OK) {
					/* warp to room */
					m_Utils->setupFadeEffect(0.007f, 0.0f, 0.0f, 0.0f, FADE_IN);
					m_Player.setMap(m_Debug.currMap);
					m_Player.setCam(0);
					m_Player.setXYZ(glm::vec3(m_Debug.getMapX(), 0.0f, m_Debug.getMapZ()));
					loadRoom();
					m_Utils->setupFadeEffect(0.007f, 0.0f, 0.0f, 0.0f, FADE_OUT);
					isDebug = false;
				} else if (m_Input->getPad() & CORE_PAD_CANCELL) {
					if (!bPressed){
						bPressed = true;
						isDebug = false;
					}
				} else {
					bPressed = false;
				}


			} else {
				/* check angle */
				if (m_Input->getPad() & CORE_PAD_RIGHT) {
					m_Player.getAngle() > 360.0f ? m_Player.setAngle(0.0f) : m_Player.setAngle(m_Player.getAngle() + 4.0f);

					if (m_Player.getAction() == ENTITY_ACTION_IDLE) {
						if (pModel->getSec4Animation() != STAND_SEC4_ANIM_WALK) {
							pModel->setSec4Animation(STAND_SEC4_ANIM_WALK);
						}
					}

				} else if (m_Input->getPad() & CORE_PAD_LEFT) {
					m_Player.getAngle() < 0.0f ? m_Player.setAngle(360.0f) : m_Player.setAngle(m_Player.getAngle() - 4.0f);
			
					if (m_Player.getAction() == ENTITY_ACTION_IDLE) {
						if (pModel->getSec4Animation() != STAND_SEC4_ANIM_WALK) {
							pModel->setSec4Animation(STAND_SEC4_ANIM_WALK);
						}
					}
				} else {
					if (m_Player.getAction() == ENTITY_ACTION_IDLE) {
						if (pModel->getSec4Animation() == STAND_SEC4_ANIM_WALK) {
							pModel->setSec4Animation(STAND_SEC4_ANIM_IDLE);
						}
					}
				}

				if (m_Input->getPad() & CORE_PAD_UP) {
					if (m_Player.getAction() != ENTITY_ACTION_WALK) {
						m_Player.setAction(ENTITY_ACTION_WALK);
						pModel->setAnimSection(EMD_SECTION_4);
						pModel->setSec4Animation(STAND_SEC4_ANIM_WALK);
					}
				} else {
					if (m_Player.getAction() != ENTITY_ACTION_IDLE) {
						m_Player.setAction(ENTITY_ACTION_IDLE);	
						pModel->setAnimSection(EMD_SECTION_4);
						pModel->setSec4Animation(STAND_SEC4_ANIM_IDLE);
					}
				}

				/* enable debug ? */
				if (m_Input->getPad() & CORE_PAD_CANCELL) {
					if (!bPressed) {
						isDebug = true;
						bPressed = true;
						m_Debug.update(m_Player.getMap());
					}
				} else {
					bPressed = false;
				}
			}
		}
	}

}


void mainGame::renderGame() {
	/* perspective */
	static glm::mat4 mtx_pers = glm::perspective(glm::radians(60.0f), (float) 640 / (float) 480, 0.1f, 100000.0f);


	/* stage stuff */
	m_Utils->renderRectangle(pRDT_tex[m_Player.getCam()]->id, {1.0f, 1.0f, 1.0f, 1.0f});
	m_Render->setShaderId(shaderList[SHADER_MODEL]);

	glm::mat4 mtx_cam = glm::lookAt(glm::vec3(pRDT->rdtCameraPos[m_Player.getCam()].positionX, pRDT->rdtCameraPos[m_Player.getCam()].positionY, pRDT->rdtCameraPos[m_Player.getCam()].positionZ),
								    glm::vec3(pRDT->rdtCameraPos[m_Player.getCam()].targetX, pRDT->rdtCameraPos[m_Player.getCam()].targetY, pRDT->rdtCameraPos[m_Player.getCam()].targetZ),
								    glm::vec3(0.0f, -1.0f, 0.0f));


	m_Render->setProjectionMtx(mtx_pers);
	m_Render->setViewMtx(mtx_cam);


    m_Utils->renderNF3D(m_Player.getXYZ(), m_Player.getAngle(), pModel.get());

	m_Render->setShaderId(shaderList[SHADER_UI]);


	/* debug settings */
	if (isDebug) {
		for (int i = 0; i < 2; i++) {
			m_Utils->renderText(m_Debug.menu[i].text, m_Debug.menu[i].x, m_Debug.menu[i].y, m_Debug.menu[i].z, FONT_TYPE_SMALL, {1.0f, 1.0f, 1.0f, 1.0f});
		}
	}

}

void mainGame::logic() {
	static float x = 0;
	static float z = 0;

	/*
	 * Player Actions
	 * Here is handled all player actions
	 * TODO: Generalize it to all entities ( :
	 */
	switch (m_Player.getAction()) {
		case ENTITY_ACTION_IDLE: {

		}
		break;

		/*
		 * WALK
		 */
		case ENTITY_ACTION_WALK: {
			bool isCollision = false;

			x = cos(glm::radians(m_Player.getAngle())) * 80.0f;
			z = -sin(glm::radians(m_Player.getAngle()))  * 80.0f;

			/*
			 * check collision
			 */

			for (unsigned int i = 0; i < pRDT->rdtCollisionHeader.amount - 1; i++) {
				switch(pRDT->rdtCollisionArray[i].type & 0x7) {
					case 1:
						if (physics::collision::triangle(m_Player.getXYZ() + glm::vec3(x, 0, z),
														 glm::vec3(pRDT->rdtCollisionArray[i].x + pRDT->rdtCollisionArray[i].w, 0.0f, pRDT->rdtCollisionArray[i].z),
														 glm::vec3(pRDT->rdtCollisionArray[i].x + pRDT->rdtCollisionArray[i].w, 0.0f, pRDT->rdtCollisionArray[i].z + pRDT->rdtCollisionArray[i].h),
														 glm::vec3(pRDT->rdtCollisionArray[i].x, 0.0f, pRDT->rdtCollisionArray[i].z + pRDT->rdtCollisionArray[i].h)
														 )) {

							isCollision = true;
						}
					break;

					case 2:
						if (physics::collision::triangle(m_Player.getXYZ() + glm::vec3(x, 0, z),
														 glm::vec3(pRDT->rdtCollisionArray[i].x, 0.0f, pRDT->rdtCollisionArray[i].z),
														 glm::vec3(pRDT->rdtCollisionArray[i].x + pRDT->rdtCollisionArray[i].w, 0.0f, pRDT->rdtCollisionArray[i].z + pRDT->rdtCollisionArray[i].h),
														 glm::vec3(pRDT->rdtCollisionArray[i].x, 0.0f, pRDT->rdtCollisionArray[i].z + pRDT->rdtCollisionArray[i].h)
														 )) {

							isCollision = true;
						}
					break;

					case 3:
						if (physics::collision::triangle(m_Player.getXYZ() + glm::vec3(x, 0, z),
														 glm::vec3(pRDT->rdtCollisionArray[i].x, 0.0f, pRDT->rdtCollisionArray[i].z),
														 glm::vec3(pRDT->rdtCollisionArray[i].x + pRDT->rdtCollisionArray[i].w, 0.0f, pRDT->rdtCollisionArray[i].z),
														 glm::vec3(pRDT->rdtCollisionArray[i].x + pRDT->rdtCollisionArray[i].w, 0.0f, pRDT->rdtCollisionArray[i].z + pRDT->rdtCollisionArray[i].h)
														 )) {

							isCollision = true;
						}
					break;

					case 4:
						if (physics::collision::triangle(m_Player.getXYZ() + glm::vec3(x, 0, z),
														 glm::vec3(pRDT->rdtCollisionArray[i].x, 0.0f, pRDT->rdtCollisionArray[i].z),
														 glm::vec3(pRDT->rdtCollisionArray[i].x + pRDT->rdtCollisionArray[i].w, 0.0f, pRDT->rdtCollisionArray[i].z),
														 glm::vec3(pRDT->rdtCollisionArray[i].x, 0.0f, pRDT->rdtCollisionArray[i].z + pRDT->rdtCollisionArray[i].h)
														 )) {

							isCollision = true;
						}
					break;
				} 
			}

			if (!isCollision)
				m_Player.setXYZ(m_Player.getXYZ() + glm::vec3(x, 0.0f, z));

			/*
			 * check switch zone
			 */

			for (unsigned int i = 0; i < pRDT->rdtCameraSwitch.size(); i++) {
				if (pRDT->rdtCameraSwitch[i].cam1 != 0) {
					if (physics::collision::triangle(m_Player.getXYZ(),
												 glm::vec3(pRDT->rdtCameraSwitch[i].x1, 0, pRDT->rdtCameraSwitch[i].z1),
												 glm::vec3(pRDT->rdtCameraSwitch[i].x2, 0, pRDT->rdtCameraSwitch[i].z2),
												 glm::vec3(pRDT->rdtCameraSwitch[i].x4, 0, pRDT->rdtCameraSwitch[i].z4)) || 
						
						physics::collision::triangle(m_Player.getXYZ(),
												 glm::vec3(pRDT->rdtCameraSwitch[i].x2, 0, pRDT->rdtCameraSwitch[i].z2),
												 glm::vec3(pRDT->rdtCameraSwitch[i].x3, 0, pRDT->rdtCameraSwitch[i].z3),
												 glm::vec3(pRDT->rdtCameraSwitch[i].x4, 0, pRDT->rdtCameraSwitch[i].z4))) {
						
						m_Player.setCam(pRDT->rdtCameraSwitch[i].cam1);		
					}
				}								
			}
		}
		break;

		case ENTITY_ACTION_RUN:

		break;
	}

    /*
     * Call the animation update in nf3d
     */
    pModel->runAnimation();

}

void mainGame::stateMachine() {
	static _menu introTest[] { 
        {"Voce caiu na\narmadilha do coiote", -0.95f, -0.65f, 0.0f, 0, true, 0.0f, 0.2f},
        {"Sera que voce\nconseguira escapar?", -0.95f, -0.65f, 0.0f, 0, true, 0.0f, 0.2f}
    };

	static timer actionTmr = {0.0f, 0.0167f, false};

	switch (layers) {
		case MAIN_GAME_LAYER_INIT: {

			if (currState == 0) {
				if (!m_Utils->isInFade()) {

					if (introTest[currState].anim == false){
						currState = 1;
					}

	   				introTest[currState].checkTmr();
	        		m_Utils->renderText(introTest[currState].tmrText, introTest[currState].x, introTest[currState].y, introTest[currState].z, FONT_TYPE_BIG, {1.0f, 1.0f, 1.0f, 1.0f});

		    	}
		    } else if (currState == 1) {

		    	if (introTest[currState].anim == false) {
					m_Utils->setupFadeEffect(0.007f, 0.0f, 0.0f, 0.0f, FADE_OUT);
		    		layers = MAIN_GAME_LAYER_GAME;
		    	}

   				introTest[currState].checkTmr();
        		m_Utils->renderText(introTest[currState].tmrText, introTest[currState].x, introTest[currState].y, introTest[currState].z, FONT_TYPE_BIG, {1.0f, 1.0f, 1.0f, 1.0f});
		    }
		}
		break;

		case MAIN_GAME_LAYER_GAME: {
			actionTmr.run();
			if (actionTmr.enable) {
				checkInput();
		   		logic();
			}

			renderGame();
		}
		break;
	}


}

