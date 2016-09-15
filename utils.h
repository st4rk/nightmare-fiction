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
#include <cstring>
#include <vector>

#include "render.h"

enum FONT_TYPE {
	FONT_TYPE_SMALL = 0,
	FONT_TYPE_BIG   = 1
};


static const GLfloat vertex_rectangle_data[] = {
   -1.0f, -1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
   -1.0f,  1.0f, 0.0f,


    1.0f,  1.0f, 0.0f,
   -1.0f,  1.0f, 0.0f,
    1.0f, -1.0f, 0.0f
};

static const GLfloat vertex_rectangle_uv[] = {
	0.0f, 0.0f,
	1.0f, 0.0f,
	0.0f, 1.0f,

	1.0f, 1.0f,
	0.0f, 1.0f,
	1.0f, 0.0f,
};



class utils {
public:
	utils();
   ~utils();

   void start(render *m_Render);
   void renderRectangle(GLuint texID, GLuint textureUnit);
   void renderText(const std::string& text, const float& Xo, const float& Yo, const float& Zo, const FONT_TYPE& font, GLuint textureUnit);

private:

	GLuint textureUnit;
	GLuint utilsTexture;
	GLuint utilsVBO;

	render *m_Render;

	modelObj fontSet;

	FONT_TYPE font;
};

#endif