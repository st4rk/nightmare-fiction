#include "mainMenu.h"

mainMenu::mainMenu() {
	menu = nullptr;
}


mainMenu::~mainMenu() {
	menu = nullptr;
}



void mainMenu::stateMachine() {

	if (menu == nullptr) {
		menu = m_Render->loadTexture("resource/TITLE00.PNG");
	}

	m_Utils->renderRectangle(menu->id, m_Render->getTexUnit());

	m_Utils->renderText("Hello MainMenu", -0.7f, -0.5f, 0.0f, FONT_TYPE_SMALL, m_Render->getTexUnit());
	m_Utils->renderText("NF Framework\nVer:0%02a", -0.7f, 0.0f, 0.0f, FONT_TYPE_SMALL, m_Render->getTexUnit());

}