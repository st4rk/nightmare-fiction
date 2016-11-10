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

/* core pad list */
#define CORE_PAD_UP       0b00000001
#define CORE_PAD_DOWN     0b00000010
#define CORE_PAD_LEFT     0b00000100
#define CORE_PAD_RIGHT    0b00001000
#define CORE_PAD_1        0b00010000   
#define CORE_PAD_2        0b00100000
#define CORE_PAD_3        0b01000000 
#define CORE_PAD_4        0b10000000 



class input {
public:
	input();
   ~input();

   void setInputInfo(GLFWwindow* window);
   void setInputType(INPUT_CONFIGURATION inputType);
   void update();

   unsigned int getPad() const;

   bool isJoystick() const;

private:
	INPUT_CONFIGURATION inputType;

	void keyboardInput();
	void joystickInput();
	GLFWwindow* window;
	unsigned int c_Pad;

	bool joyStatus;
};

#endif