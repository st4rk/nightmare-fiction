/*====================================
 * input 
 * - insert a good description here -
 * - insert a good description here -
 * - insert a good description here -
 * written by St4rk
 *====================================
 */
#ifndef _INPUT_H_
#define _INPUT_H_

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

enum INPUT_CONFIGURATION {
	INPUT_KEYBOARD = 0,
	INPUT_JOYSTICK = 1
};

enum CORE_PAD_BUTTONS {
	CORE_PAD_UP      = 0,
	CORE_PAD_DOWN    = 1,
	CORE_PAD_LEFT    = 2,
	CORE_PAD_RIGHT   = 3,
	CORE_PAD_OK      = 4,
	CORE_PAD_CANCELL = 5
};


class input {
public:
	input();
   ~input();

   void setInputInfo(GLFWwindow* window);
   void setInputType(INPUT_CONFIGURATION inputType);
   void updateInput();

   unsigned int getPad() const;

private:
	INPUT_CONFIGURATION inputType;

	void keyboardInput();
	void joystickInput();
	GLFWwindow* window;
	unsigned int c_Pad;
};

#endif