#include "mainMenu.h"

mainMenu::mainMenu() {
	layers = MAIN_MENU_LAYER_LOGO;
}


mainMenu::~mainMenu() {

	if (textureList.size() > 0) {
		for (unsigned int i = 0; i < textureList.size(); i++) {
			textureList[i]->destroy();
		}
	}

}

void mainMenu::start() {
	nTexture* node = nullptr;

	node = m_Render->loadTexture("resource/ui/intro_1.bmp");
	textureList.push_back(node);
	node = m_Render->loadTexture("resource/ui/intro_2.bmp");
	textureList.push_back(node);
	node = m_Render->loadTexture("resource/ui/mainMenu.bmp");
	textureList.push_back(node);

	layers = MAIN_MENU_LAYER_LOGO;
}

void mainMenu::stateMachine() {
	switch (layers) {
		case MAIN_MENU_LAYER_LOGO: {
			m_Utils->renderRectangle(textureList[MAIN_MENU_LAYER_LOGO]->id, m_Render->getTexUnit());
			
			/* FUN TIME : D */
			m_Utils->renderText("-- INPUT TEST -- ", -0.7f, -0.5f, 0.0f, FONT_TYPE_SMALL, m_Render->getTexUnit());
			if (m_Input->isJoystick()) {
				m_Utils->renderText("Joy Connecteed", -0.7f, -0.6f, 0.0f, FONT_TYPE_SMALL, m_Render->getTexUnit());
			} else {
				m_Utils->renderText("No Joystick", -0.7f, -0.6f, 0.0f, FONT_TYPE_SMALL, m_Render->getTexUnit());
			}

			printf("%d\n", m_Input->getPad());
			if (m_Input->getPad() & CORE_PAD_UP) {
				m_Utils->renderText("BUTTON: UP", -0.7f, -0.8f, 0.0f, FONT_TYPE_SMALL, m_Render->getTexUnit());
			}

			if (m_Input->getPad() & CORE_PAD_DOWN) {
				m_Utils->renderText("BUTTON: DOWN", -0.7f, -0.8f, 0.0f, FONT_TYPE_SMALL, m_Render->getTexUnit());
			}

			if (m_Input->getPad() & CORE_PAD_LEFT) {
				m_Utils->renderText("BUTTON: LEFT", -0.7f, -0.8f, 0.0f, FONT_TYPE_SMALL, m_Render->getTexUnit());
			}

			if (m_Input->getPad() & CORE_PAD_RIGHT) {
				m_Utils->renderText("BUTTON: RIGHT", -0.7f, -0.8f, 0.0f, FONT_TYPE_SMALL, m_Render->getTexUnit());
			}

			if (m_Input->getPad() & CORE_PAD_OK) {
				m_Utils->renderText("BUTTON: X", -0.7f, -0.8f, 0.0f, FONT_TYPE_SMALL, m_Render->getTexUnit());
			}

		}
		break;

		case MAIN_MENU_LAYER_WARNING: {
			m_Utils->renderRectangle(textureList[MAIN_MENU_LAYER_WARNING]->id, m_Render->getTexUnit());
		}
		break;

		case MAIN_MENU_LAYER_START: {
			m_Utils->renderRectangle(textureList[MAIN_MENU_LAYER_START]->id, m_Render->getTexUnit());
		}
		break;
	}
}