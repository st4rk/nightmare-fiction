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
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

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
	~nTexture() {
		glDeleteTextures(1, &id);
		id = 0;
	}

	libstk texture;
	GLuint id;
};

class modelObj {
public:
	modelObj() {
		tex = nullptr;
		vbo = 0;
	}

	~modelObj() {
		if (tex != nullptr) {
			delete tex;
			tex = nullptr;
		}

		glDeleteBuffers(1, &vbo);
	}

	nTexture *tex;
	GLuint vbo;
};

class render {
public:
	render();
   ~render();

	bool initGL();
	void swapBuffers();
	void clearScene();

	void setProjectionMtx(const glm::mat4& p_Matrix);
	void setViewMtx(const glm::mat4& v_Matrix);
	void setModelMtx(const glm::mat4& m_Matrix);

	GLFWwindow* getContext();

	nTexture* loadTexture(const std::string& dir, bool remove = false, color rColor = {1.0f, 1.0f, 1.0f, 1.0f});

	GLuint getTexUnit() const;
	GLuint getProgramId() const;

private:
	void updateMVP();

	GLFWwindow *window;
	GLuint programID;
	GLuint texUnit;
	GLuint mvpID;
	GLuint vaoID;
	
	glm::mat4 p_Matrix; // projection matrix
	glm::mat4 v_Matrix; // view matrix
	glm::mat4 m_Matrix; // model matrix

};


#endif