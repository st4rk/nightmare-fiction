#include "mainMenu.h"

mainMenu::mainMenu() {
	layers = MAIN_MENU_LAYER_LOGO;
	arrow = 0;
	pressed = false;
}


mainMenu::~mainMenu() {

	if (textureList.size() > 0) {
		for (unsigned int i = 0; i < textureList.size(); i++) {
			textureList[i]->destroy();
		}
	}

	arrow = 0;
	pressed = false;
}

void mainMenu::start() {
	nTexture* node = nullptr;

	node = m_Render->loadTexture("resource/ui/intro_1.bmp");
	textureList.push_back(node);
	node = m_Render->loadTexture("resource/ui/intro_2.bmp");
	textureList.push_back(node);
	node = m_Render->loadTexture("resource/ui/mainMenu.bmp");
	textureList.push_back(node);

	m_Utils->setupFadeEffect(0.007f, 0.0f, 0.0f, 0.0f, FADE_IN_OUT);

	layers = MAIN_MENU_LAYER_LOGO;
}

void mainMenu::checkInput() {
	// verify what input is pressed and verify if the state can change
	if (m_Input->getPad() & CORE_PAD_UP) {
		if (!pressed) {
			if (arrow > 0) arrow--; 
			pressed = true;
		}
	} else if (m_Input->getPad() & CORE_PAD_DOWN) {
		if (!pressed) {
			if (arrow < 2) arrow++;
			pressed = true;
		}
	} else if (m_Input->getPad() & CORE_PAD_OK) {
		if (!pressed) {
			switch (arrow) {
				case 0:

				break;

				case 1: {
					m_Utils->setupFadeEffect(0.007f, 0.0f, 0.0f, 0.0f, FADE_IN);
					layers = MAIN_MENU_LAYER_CONFIG;
				}
				break;

				case 2:

				break;
			}
		}
	} else {
		pressed = false;
	}
}

void mainMenu::stateMachine() {
	switch (layers) {

		case MAIN_MENU_LAYER_LOGO: {
			if (!m_Utils->isInFade()) {
				m_Utils->setupFadeEffect(0.007f, 0.0f, 0.0f, 0.0f, FADE_IN_OUT);
				layers = MAIN_MENU_LAYER_WARNING;
			}

			m_Utils->renderRectangle(textureList[MAIN_MENU_LAYER_LOGO]->id, m_Render->getTexUnit(), {1.0f, 1.0f, 1.0f, 1.0f});
		}
		break;

		case MAIN_MENU_LAYER_WARNING: {
			if (!m_Utils->isInFade()) {
				m_Utils->setupFadeEffect(0.007f, 0.0f, 0.0f, 0.0f, FADE_OUT);
				layers = MAIN_MENU_LAYER_SEL;
			}

			m_Utils->renderRectangle(textureList[MAIN_MENU_LAYER_WARNING]->id, m_Render->getTexUnit(), {1.0f, 1.0f, 1.0f, 1.0f});
		}
		break;

		case MAIN_MENU_LAYER_SEL: {
			m_Utils->renderRectangle(textureList[MAIN_MENU_LAYER_START]->id, m_Render->getTexUnit(), {1.0f, 1.0f, 1.0f, 1.0f});
				
			// check if the fade effect is end, so we can
			// draw the main menu
			if (!m_Utils->isInFade()) {
				checkInput();

				switch (arrow) {
					case 0:
						m_Utils->renderText("NEW GAME", -0.25f, -0.5f, 0.0f, FONT_TYPE_SMALL, m_Render->getTexUnit(), {0.0f, 1.0f, 0.0f, 1.0f});
						m_Utils->renderText("OPTIONS", -0.23f, -0.6f, 0.0f, FONT_TYPE_SMALL, m_Render->getTexUnit(), {1.0f, 1.0f, 1.0f, 1.0f});					
						m_Utils->renderText("EXIT", -0.15f, -0.7f, 0.0f, FONT_TYPE_SMALL, m_Render->getTexUnit(), {1.0f, 1.0f, 1.0f, 1.0f});										
					break;

					case 1:
						m_Utils->renderText("NEW GAME", -0.25f, -0.5f, 0.0f, FONT_TYPE_SMALL, m_Render->getTexUnit(), {1.0f, 1.0f, 1.0f, 1.0f});
						m_Utils->renderText("OPTIONS", -0.23f, -0.6f, 0.0f, FONT_TYPE_SMALL, m_Render->getTexUnit(), {0.0f, 1.0f, 0.0f, 1.0f});					
						m_Utils->renderText("EXIT", -0.15f, -0.7f, 0.0f, FONT_TYPE_SMALL, m_Render->getTexUnit(), {1.0f, 1.0f, 1.0f, 1.0f});										
					break;

					case 2:
						m_Utils->renderText("NEW GAME", -0.25f, -0.5f, 0.0f, FONT_TYPE_SMALL, m_Render->getTexUnit(), {1.0f, 1.0f, 1.0f, 1.0f});
						m_Utils->renderText("OPTIONS", -0.23f, -0.6f, 0.0f, FONT_TYPE_SMALL, m_Render->getTexUnit(), {1.0f, 1.0f, 1.0f, 1.0f});					
						m_Utils->renderText("EXIT", -0.15f, -0.7f, 0.0f, FONT_TYPE_SMALL, m_Render->getTexUnit(), {0.0f, 1.0f, 0.0f, 1.0f});					
					break;
				}
			}
		}
		break;

		case MAIN_MENU_LAYER_CONFIG:{
			m_Utils->renderRectangle(textureList[MAIN_MENU_LAYER_START]->id, m_Render->getTexUnit(), {1.0f, 1.0f, 1.0f, 1.0f});
		
			if (!m_Utils->isInFade()) {
				m_Utils->setupFadeEffect(0.007f, 0.0f, 0.0f, 0.0f, FADE_OUT);
				layers = MAIN_MENU_LAYER_SEL;
				sceneState = SCENE_STATE_SLEEP;
				nextScene  = 1;
			}
		}
		break;

		case MAIN_MENU_LAYER_START:

		break;
	}
}