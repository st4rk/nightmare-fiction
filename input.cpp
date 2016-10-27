#include "input.h"


input::input() {
	c_Pad  = 0;
	window = nullptr;

}


input::~input() {
	c_Pad  = 0;
	window = nullptr;
}

/*
 * setInputInfo
 * set input information, glfw context
 * no return
 */
void input::setInputInfo(GLFWwindow* window) {
	this->window = window;

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
}

/*
 * updateInput
 * This function is called to start the buttons update
 * no return
 */

void input::update() {
	switch (inputType) {
		case INPUT_KEYBOARD:
			keyboardInput();
		break;

		case INPUT_JOYSTICK:
			joystickInput();
		break;
	}
}

/*
 * keyboardInput
 * This function is used to check keyboard inputs and update c_Pad buttons
 * no return
 */
void input::keyboardInput() {
	
	c_Pad = 0;

	if ( glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS )
		c_Pad = c_Pad | CORE_PAD_UP;

	if ( glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS )
		c_Pad = c_Pad | CORE_PAD_DOWN;

	if ( glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS )
		c_Pad = c_Pad | CORE_PAD_LEFT;

	if ( glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS )
		c_Pad = c_Pad | CORE_PAD_RIGHT;

	if ( glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS )
		c_Pad = c_Pad | CORE_PAD_CANCELL;

	if ( glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS )
		c_Pad = (c_Pad | CORE_PAD_OK);
}

/*
 * joystickInput
 * This function is used to check joystick inputs and update c_Pad buttons
 * no return
 */
void input::joystickInput() {
	int present = glfwJoystickPresent(GLFW_JOYSTICK_1);

	present > 0 ? joyStatus = true : joyStatus = false;


	if (present) {
		int count;
		const unsigned char* axes = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &count);

		/*
		for (int i = 0; i < count; i++) {
			printf("i: %d button: %d\n", i, axes[i]);
		}
		*/

		if ( axes[4] == GLFW_PRESS ) {
			c_Pad = c_Pad | CORE_PAD_UP;
		} else {
			c_Pad = c_Pad & ~CORE_PAD_UP;
		}

		if ( axes[6] == GLFW_PRESS )
			c_Pad = c_Pad | CORE_PAD_DOWN;
		else
			c_Pad = c_Pad & ~CORE_PAD_DOWN;

		if ( axes[7] == GLFW_PRESS )
			c_Pad = c_Pad | CORE_PAD_LEFT;
		else
			c_Pad = c_Pad & ~CORE_PAD_LEFT;

		if ( axes[5] == GLFW_PRESS )
			c_Pad = c_Pad | CORE_PAD_RIGHT;
		else
			c_Pad = c_Pad & ~CORE_PAD_RIGHT;

		if ( axes[14] == GLFW_PRESS )
			c_Pad = (c_Pad | CORE_PAD_OK);
		else
			c_Pad = c_Pad & ~CORE_PAD_OK;

	}

}

/*
 * setInputType
 * This function is a set to configurate the input type
 * no return
 */
void input::setInputType(INPUT_CONFIGURATION inputType) {
	this->inputType = inputType;
}

/*
 * getPad
 * this function return c_Pad 
 * return c_Pad
 */

unsigned int input::getPad() const { return c_Pad; }


bool input::isJoystick() const { return joyStatus; }