#include "mainGame.h"

mainGame::mainGame() {
	isDebug = false;
	currState = 0;
}


mainGame::~mainGame() {
	isDebug = false;
	currState = 0;
}

void mainGame::start() {
	static GLfloat shadow_xyzuv[] = {
	   -960.0f,  -10.0f, -960.0f,
		0.0f, 0.0f,

	    960.0f,  -10.0f, -960.0f,
		1.0f, 0.0f,

	   -960.0f,  -10.0f,  960.0f,
		0.0f, 1.0f,

	    960.0f,  -10.0f,  960.0f,
		1.0f, 1.0f,

	   -960.0f,  -10.0f,  960.0f,
		0.0f, 1.0f,

	    960.0f,  -10.0f, -960.0f,
		1.0f, 0.0f,
	};

	std::unique_ptr<nTexture> node;

	/* load player model */
	nTexture* tex = m_Render->loadTexture("resource/models/2_shot.TIM");
	pModel.reset(new nf3d("resource/models/2_shot.EMD", tex, NF3D_TYPE_EMD));
	pWeapon.reset(new nf3d("resource/models/PL0BW07.PLW", tex, NF3D_TYPE_PLW));

	/* macgyver to be removed soon */
	pModel->setAnimSet(pWeapon->weapon.sec2Data, pWeapon->weapon.animList);

	/* load dummy texture to debug */
	node.reset(m_Render->loadTexture("resource/ui/dummy.png"));
	textureList.push_back(std::move(node));

	/* load shadow */
	m_Shadow.tex.reset(m_Render->loadTexture("resource/textures/shadow.png"));
	m_Shadow.createVBO(shadow_xyzuv, sizeof(shadow_xyzuv), 2);

	/* hard coded player information */
	m_Player.setStage(1);
	m_Player.setMap(6);
	m_Player.setCam(1);
	m_Player.setModel(2);
	m_Player.setAngle(90.0f);
	m_Player.setXYZ(glm::vec3(18391.0f, 0, 12901.0f));
	pModel->setAnimSection(EMD_SECTION_4);
	pModel->setSec4Animation(STAND_SEC4_ANIM_IDLE);
	/* debug information */
	m_Debug.currMap = 0;

	/* load room */
	loadRoom(m_Render, &m_Player, &pRDT_tex, &pRDT, RDT_TYPE_RE1);

	/* load shaders, TODO: plz, you can do better, i know */
	GLuint currentShader = 0;
	currentShader = LoadShaders("game/shaders/vertexShader.glsl", "game/shaders/fragmentShader.glsl");
	shaderList.push_back(currentShader);
	currentShader = LoadShaders("game/shaders/modelVertex.glsl", "game/shaders/modelFragment.glsl");
	shaderList.push_back(currentShader);

	/* state machine initial state */
	layers = MAIN_GAME_LAYER_GAME;

	/* disable debug settings */
	isDebug = false;

	/* sound effect list */
	/* TODO: Otimize it, only load the sound effect when necessary */

	/**
	 * Step sound list
	 */
	std::unique_ptr<soundChunk> sound_node;
	sound_node.reset(new soundChunk("resource/sfx/FT_CPA.WAV"));
	stepList.push_back(std::move(sound_node));
	sound_node.reset(new soundChunk("resource/sfx/FT_CPB.WAV"));
	stepList.push_back(std::move(sound_node));
	sound_node.reset(new soundChunk("resource/sfx/FT_HAA.WAV"));
	stepList.push_back(std::move(sound_node));
	sound_node.reset(new soundChunk("resource/sfx/FT_HAB.WAV"));
	stepList.push_back(std::move(sound_node));
	sound_node.reset(new soundChunk("resource/sfx/FT_WDA.WAV"));
	stepList.push_back(std::move(sound_node));
	sound_node.reset(new soundChunk("resource/sfx/FT_WDB.WAV"));
	stepList.push_back(std::move(sound_node));

}

void mainGame::checkInput() {
	static bool bPressed = false;
	static unsigned int raw_pad = 0;

	raw_pad = m_Input->getPad();

	switch (layers) {
		case MAIN_GAME_LAYER_INIT: {

		}
		break;

		/* TODO: Better entity moviment handle */
		case MAIN_GAME_LAYER_GAME: {
			if (isDebug) {
				/* debug settings */
				if (raw_pad & KEY_RIGHT) {
					if (!bPressed) {
						m_Debug.nextMap();
						bPressed = true;
					}
				} else if (raw_pad & KEY_LEFT) {
					if (!bPressed) {
						m_Debug.priorMap();
						bPressed = true;
					}
				} else if (raw_pad & KEY_3) {
					if (!bPressed) {
						/* warp to room */
						m_Player.setMap(m_Debug.currMap);
						m_Player.setCam(0);
						m_Player.setXYZ(glm::vec3(m_Debug.getMapX(), 0.0f, m_Debug.getMapZ()));
						loadRoom(m_Render, &m_Player, &pRDT_tex, &pRDT, RDT_TYPE_RE1);
						m_Utils->setupFadeEffect(0.007f, 0.0f, 0.0f, 0.0f, FADE_OUT);
						bPressed = true;
					}
				
				} else if (raw_pad & KEY_2) {
					if (!bPressed){
						bPressed = true;
						isDebug = false;
					}
				} else {
					bPressed = false;
				}


			} else {
				/* check angle */
				if (raw_pad & KEY_RIGHT) {
					m_Player.getAngle() > 360.0f ? m_Player.setAngle(0.0f) : m_Player.setAngle(m_Player.getAngle() + 4.0f);

					if (m_Player.getAction() == ENTITY_ACTION_IDLE) {
						
						if (pModel->getSec4Animation() != STAND_SEC4_ANIM_WALK) {
							pModel->setSec4Animation(STAND_SEC4_ANIM_WALK);
						}
					}

				} else if (raw_pad & KEY_LEFT) {
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

				if (raw_pad & KEY_UP) {
					if (m_Player.getAction() != ENTITY_ACTION_WALK) {
						m_Player.setAction(ENTITY_ACTION_WALK);
						pModel->setAnimSection(EMD_SECTION_4);
					}
					
					if (raw_pad & KEY_1) {
						pModel->setSec4Animation(STAND_SEC4_ANIM_RUNNING);
					} else {
						pModel->setSec4Animation(STAND_SEC4_ANIM_WALK);
					}

				} else {
					if (m_Player.getAction() != ENTITY_ACTION_IDLE) {
						m_Player.setAction(ENTITY_ACTION_IDLE);	
						pModel->setAnimSection(EMD_SECTION_4);
						pModel->setSec4Animation(STAND_SEC4_ANIM_IDLE);
					}
				}

				/**
				 * TODO: A cool door system ( : 
				 */
				if (raw_pad & KEY_3) {
					if (!bPressed) {
					  checkDoor(m_Render, &m_Player, &pRDT_tex, &pRDT, RDT_TYPE_RE1);
					  bPressed = true;
					} 
				/* enable debug ? */
				}else if (raw_pad & KEY_2) {
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
	static glm::mat4 mtx_pers = glm::perspective(glm::radians(60.0f), (float) 640 / (float) 480, 1.0f, 100000.0f);
	static glm::mat4 model = glm::mat4(1.0f);
	static glm::mat4 mtx_cam = glm::mat4(1.0f);

	/*======================
	 *==  Render Scenario ==
	 *======================*/
	m_Utils->renderRectangle(pRDT_tex[m_Player.getCam()]->id, {1.0f, 1.0f, 1.0f, 1.0f});
	/*===================
	 *==  Perspective  ==
	  ==     and       ==
	  ==    Camera     == 
	 *===================*/

	/**
	 * TODO: Again, improve it to a single code, for the sake of God
	 */
	switch (pRDT.rdtType) {
		case RDT_TYPE_RE1:
			mtx_cam = glm::lookAt(glm::vec3(pRDT.rdtRE1CameraPos[m_Player.getCam()].positionX, pRDT.rdtRE1CameraPos[m_Player.getCam()].positionY, pRDT.rdtRE1CameraPos[m_Player.getCam()].positionZ),
										    glm::vec3(pRDT.rdtRE1CameraPos[m_Player.getCam()].targetX, pRDT.rdtRE1CameraPos[m_Player.getCam()].targetY, pRDT.rdtRE1CameraPos[m_Player.getCam()].targetZ),
										    glm::vec3(0.0f, -1.0f, 0.0f));
		break;

		case RDT_TYPE_RE2_PROTO:
		case RDT_TYPE_RE2:
		case RDT_TYPE_RE3:
			mtx_cam = glm::lookAt(glm::vec3(pRDT.rdtCameraPos[m_Player.getCam()].positionX, pRDT.rdtCameraPos[m_Player.getCam()].positionY, pRDT.rdtCameraPos[m_Player.getCam()].positionZ),
										    glm::vec3(pRDT.rdtCameraPos[m_Player.getCam()].targetX, pRDT.rdtCameraPos[m_Player.getCam()].targetY, pRDT.rdtCameraPos[m_Player.getCam()].targetZ),
										    glm::vec3(0.0f, -1.0f, 0.0f));
		break;
	}

	m_Render->setProjectionMtx(mtx_pers);
	m_Render->setViewMtx(mtx_cam);

	/*==============
	 *==  shadow  ==
	 *==============*/

	/* change shader to model */
	m_Render->setShaderId(shaderList[SHADER_MODEL]);

	/*================
	 *==  3D Model  ==
	 *================*/
    m_Utils->renderNF3D(m_Player.getXYZ(), m_Player.getAngle(), pModel.get());

    /* change the shader to UI */
	m_Render->setShaderId(shaderList[SHADER_UI]);
    model = glm::translate(glm::mat4(1.0f), m_Player.getXYZ());
    m_Render->setModelMtx(model);
	m_Utils->render3D_Obj(m_Shadow);

	/*======================
	 *==  Debug Settings  ==
	 *======================*/
	if (isDebug) {
		model = glm::scale(glm::mat4(1.0f), glm::vec3(0.8f, 0.2f, 0.0));
		
		m_Render->setProjectionMtx(glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f));
		m_Render->setViewMtx(glm::mat4(1.0f));
		m_Render->setModelMtx(model);

		m_Utils->renderRectangle(textureList[TEXTURE_DEBUG]->id, {0.0f, 0.0f, 0.3f, 0.5f});
		for (int i = 0; i < 2; i++) {
			m_Utils->renderText(m_Debug.menu[i].text, m_Debug.menu[i].x, m_Debug.menu[i].y, m_Debug.menu[i].z, FONT_TYPE_SMALL, {1.0f, 1.0f, 1.0f, 1.0f});
		}
	}

}

void mainGame::logic() {
	static float speed = 0.0f;

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
			static unsigned int stepZone = 0;
			static unsigned int stepCnt1 = 0;
			static unsigned int stepCnt2 = 0;

			pModel->getSec4Animation() == STAND_SEC4_ANIM_RUNNING ? speed = 180.0f : speed = 80.0f;

			/* verify collision boundaries */
			checkRoomCollision(&pRDT, &m_Player, speed);

			/* verify switch zone */
			checkSwitchZone(&pRDT, &m_Player);

			/* check current step zone */
			stepZone = checkStepZone(&m_Player, &pRDT);

			if (pModel->getSec4Animation() == STAND_SEC4_ANIM_RUNNING) {
				stepCnt1 = 3;
				stepCnt2 = 13;
				stepZone++;
			} else {
				stepCnt1 = 12;
				stepCnt2 = 27;
			}

			if ((pModel->getAnimCnt() == stepCnt1) || (pModel->getAnimCnt() == stepCnt2)) {
				m_Sound->playSoundChunk(stepList[stepZone]->get(), 0);
			}

		}
		break;
	}

    /*
     * Call the animation update in nf3d
     */
    pModel->run();

}

void mainGame::stateMachine() {
	static _menu introTest[] { 
        {"They have escaped\ninto the mansion", -0.95f, -0.65f, 0.0f, 0, true, 0.0f, 0.1f},
        {"where they thought\nit was safe% yet%%%", -0.95f, -0.65f, 0.0f, 0, true, 0.0f, 0.1f}
    };

	static timer actionTmr = {0.0f, 0.0167f, false};

	/**
	 * TODO: Better code implementation, because urg <_< 
	 */

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

