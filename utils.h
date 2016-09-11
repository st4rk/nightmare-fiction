/*====================================
 * utils 
 * This class is used to some misc stuff like
 * text rendering, rectangle rendering and so on
 * written by St4rk
 *====================================
 */

#ifndef _UTILS_H_
#define _UTILS_H_

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>



class utils {
public:
	utils();
   ~utils();

   void setContext(GLFWwindow *window);
   void renderRectangle(GLuint texID, GLuint textureUnit);

private:
	GLFWwindow* window;

	GLuint textureUnit;
	GLuint utilsTexture;
	GLuint utilsVBO;
};

#endif