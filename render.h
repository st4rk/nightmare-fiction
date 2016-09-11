/*================================================
 * render
 * - this class deal with low-level rendering
 * - stuff, if you want to modify the API used
 * - to graphic render, you're in the right place
 * written by St4rk
 *================================================
 */

#ifndef _RENDER_H_
#define _RENDER_H_

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "shaders/loader.h"
#include "lib/libstk.h"

enum RENDER_INFORMATION {
	RENDER_RES_WIDTH   = 640,
	RENDER_RES_HEIGHT  = 480,
	RENDER_SAMPLES = 1
};

enum GL_INFORMATION {
	GL_CTX_MAJOR_VERSION = 3,
	GL_CTX_MINOR_VERSION = 3
};

struct nTexture {
	libstk texture;
	GLuint id;
};

class render {
public:
	render();
   ~render();

	bool initGL();
	void swapBuffers();
	void clearScene();
	GLFWwindow* getContext();

	nTexture* loadTexture(const std::string& dir);

	GLuint getTexUnit() const;

private:
	GLFWwindow *window;
	GLuint programID;
	GLuint texUnit;
	GLuint vaoID;

};


#endif