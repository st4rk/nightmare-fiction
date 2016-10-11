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

#include "nf3d/nf3d.h"
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


enum FADE_EFFECT_TYPE {
	FADE_IN,
	FADE_OUT,
	FADE_BLINK,
	FADE_IN_OUT,
	FADE_NONE
};

struct fadeEffect {
	color r_Color;
	float speed;
	unsigned char type;
	bool inFade;
	bool inOut;
};

class utils {
public:
	utils();
	~utils();

	void start(render *m_Render);
	void renderRectangle(const GLuint& texID, const color& r_Color);
	void renderText(const std::string& text, const float& Xo, const float& Yo, const float& Zo, const FONT_TYPE& font,
				    const color& r_Color);

	void render3D_Obj(const modelObj& obj);

	void renderNF3D_anim(unsigned int objNum, unsigned int var, int var2, nf3d* obj);
	void renderNF3D(nf3d* obj);

	void setupFadeEffect(const float &speed, const float &r, const float& g, const float& b,const FADE_EFFECT_TYPE& type);
	void doFadeEffect();

	bool isInFade() const;
private:

	GLuint textureUnit;
	GLuint utilsTexture;
	GLuint utilsVBO;

	render *m_Render;

	modelObj fontSet;

	fadeEffect fade;
	modelObj fadeTexture;

	glm::mat4 modelMtx;

	FONT_TYPE font;
};

#endif