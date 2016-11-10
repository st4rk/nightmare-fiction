#include "utils.h"


utils::utils() {
	m_Render = nullptr;

	fade.speed   = 0.0f;
	fade.r_Color = {0.0f, 0.0f, 0.0f, 0.0f};
	fade.type    = FADE_NONE;
	fade.inFade  = false;
}

utils::~utils() {
	m_Render = nullptr;

	fade.speed   = 0.0f;
	fade.r_Color = {0.0f, 0.0f, 0.0f, 0.0f};
	fade.type    = FADE_NONE;
	fade.inFade  = false;

	glDeleteBuffers(1, &utilsVBO);
	glDeleteBuffers(1, &utilsTexture);
}

/*
 * start
 * this function start utils stuff, set the m_Render pointer
 * and load texture stuff
 * no return
 */
void utils::start(render *m_Render) {
	this->m_Render = m_Render;

	/* 
	 * load font set
	 */

	fontSet.tex.reset(m_Render->loadTexture("resource/font/1.BMP", true, {0.0f, 0.0f, 0.0f, 0.0f}));
	fadeTexture.tex.reset(m_Render->loadTexture("resource/ui/dummy.png"));

	glGenBuffers(1, &fontSet.vbo);
	glGenBuffers(1, &utilsVBO);

	glBindBuffer(GL_ARRAY_BUFFER, utilsVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_rectangle_data), vertex_rectangle_data, GL_STATIC_DRAW);

	glGenBuffers(1, &utilsTexture);
	glBindBuffer(GL_ARRAY_BUFFER, utilsTexture);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_rectangle_uv), vertex_rectangle_uv, GL_STATIC_DRAW);
}

/*
 * renderRectangle
 * this function render a rectangle
 * no return
 */
void utils::renderRectangle(const GLuint& texID, const color& r_Color) {
	glDisable(GL_DEPTH_TEST);
	GLuint m_Color = glGetUniformLocation(m_Render->getCurrentShader(), "m_Color");
	
	glUniform4f(m_Color, r_Color.r, r_Color.g, r_Color.b, r_Color.a);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texID);

	glBindBuffer(GL_ARRAY_BUFFER, utilsVBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	
	glBindBuffer(GL_ARRAY_BUFFER, utilsTexture);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	glEnable(GL_DEPTH_TEST);
}


/**
 * render3D_obj
 * render a static object
 * returns nothing
 */
void utils::render3D_Obj(const modelObj& obj) {
	GLuint m_Color = glGetUniformLocation(m_Render->getCurrentShader(), "m_Color");
	glUniform4f(m_Color, 1.0f, 1.0f, 1.0f, 1.0f);
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, obj.tex->id);

	glBindBuffer(GL_ARRAY_BUFFER, obj.vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5, (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5, (void*)0xC);

	glDrawArrays(GL_TRIANGLES, 0, 3 * obj.t_Triangles);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

/*
 * renderText
 * This function is used to render bitmap fonts
 * no return
 */
void utils::renderText(const std::string& text, const float& Xo, const float& Yo, const float& Zo, const FONT_TYPE& font,
   			     	   const color& r_Color) {
	
	glDisable(GL_DEPTH_TEST);
	static glm::mat4 pos = glm::mat4(1.0f);
	static glm::mat4 ui_ortho = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f);

	std::vector<GLfloat> vbo_buffer;

	GLuint m_Color = glGetUniformLocation(m_Render->getCurrentShader(), "m_Color");

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, fontSet.tex->id);
	glUniform4f(m_Color, r_Color.r, r_Color.g, r_Color.b, r_Color.a);
	
	m_Render->setProjectionMtx(ui_ortho);
	m_Render->setViewMtx(glm::mat4(1.0f));
	m_Render->setModelMtx(pos);

	float x = Xo;
	float y = Yo;
	unsigned int tCnt = 0;

	for (auto it = text.begin(); it != text.end(); ++it) {
		switch (font) {
			case FONT_TYPE_SMALL: {

				if (*it == '\n') {
					x = Xo;
					y -= 0.1f;
				} else if (*it == ' ') {
					x += 0.060f;
				} else {
					float u = 0.03125f * (*it % 32);
					float v = 0.03125f * ((*it - 32)/32);

					GLfloat xyz_uv_coord[] = {
					   -0.03f    + x, -0.03f    + y, 0.0f,
					    0.001f     + u,  0.97f   - v,

					    0.03f    + x, -0.03f    + y, 0.0f,
						0.03125f   + u,  0.97f   - v,

					   -0.03f    + x,  0.03f    + y, 0.0f,
						0.001f     + u,  0.999f  - v,

					    0.03f    + x,  0.03f    + y, 0.0f,
						0.03125f   + u,  0.999f  - v,

					   -0.03f    + x,  0.03f    + y, 0.0f,
						0.001f     + u,  0.999f  - v,

					    0.03f    + x, -0.03f    + y, 0.0f,
						0.03125f   + u,  0.97f   - v
					};

					vbo_buffer.insert (vbo_buffer.end(), xyz_uv_coord, xyz_uv_coord+30);
					x += 0.060f;
					tCnt++;
				}

			}
			break;

			case FONT_TYPE_BIG: {

				if (*it == '\n') {
					x = Xo;
					y -= 0.1f;
				} else if (*it == ' ') {
					x += 0.1f;
				} else {
					float u = 0.0545f  * (*it % 18);
					float v = 0.0543f  * ((*it - 36)/18) - 0.0545f;

					GLfloat xyz_uv_coord[] = {
					   -0.04f    + x, -0.05f    + y, 0.0f,
					    0.0f     + u,  0.78f   - v,

					    0.04f    + x, -0.05f    + y, 0.0f,
						0.054f   + u,  0.78f   - v,

					   -0.04f    + x,  0.05f    + y, 0.0f,
						0.0f     + u,  0.834f  - v,

					    0.04f    + x,  0.05f    + y, 0.0f,
						0.054f   + u,  0.834f  - v,

					   -0.04f    + x,  0.05f    + y, 0.0f,
						0.0f     + u,  0.834f  - v,

					    0.04f    + x, -0.05f    + y, 0.0f,
						0.054f   + u,  0.78f   - v
					};

					vbo_buffer.insert (vbo_buffer.end(), xyz_uv_coord, xyz_uv_coord+30);
					x += 0.1f;
					tCnt++;
				}
			}
			break;
		}
	}

	glBindBuffer(GL_ARRAY_BUFFER, fontSet.vbo);
	glBufferData(GL_ARRAY_BUFFER, vbo_buffer.size() * sizeof(GLfloat), &vbo_buffer[0], GL_STREAM_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5, (void*)0x0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5, (void*)0xC);

	glDrawArrays(GL_TRIANGLES, 0, 6 * tCnt);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glEnable(GL_DEPTH_TEST);
}

/*
 * setupFadeEffect
 * initialize fade effect
 * speed = speed of fade effect
 * r,g,b = color of fade effect
 * type  = FADE_IN, FADE_OUT, FADE_BLINK, FADE_IN_OUT
 * no return
 */
void utils::setupFadeEffect(const float& speed, const float& r, const float& g, const float& b, const FADE_EFFECT_TYPE& type) {
	this->fade.speed = speed;

	switch (type) {
		case FADE_IN: 		this->fade.r_Color = {r, g, b, 0.0f}; break;
		case FADE_OUT: 		this->fade.r_Color = {r, g, b, 1.0f}; break;
		case FADE_BLINK: 	this->fade.r_Color = {r, g, b, 0.0f}; break;
		case FADE_IN_OUT:  	this->fade.r_Color = {r, g, b, 1.0f}; this->fade.inOut = true; break;
		case FADE_NONE:     this->fade.r_Color = {0.0f, 0.0f, 0.0f, 0.0f}; break;
	}

	this->fade.type = type;
	this->fade.inFade = true;
}

/*
 * doFadeEffect
 * handle the fade effect to be rendered
 */
void utils::doFadeEffect() {
	static glm::mat4 pos = glm::mat4(1.0f);
	static glm::mat4 ui_ortho = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f);
	// check if fade effect is enable
	if (fade.inFade) {
		switch (fade.type) {
			case FADE_IN:
				if (fade.r_Color.a < 1.0f) {
					fade.r_Color.a += fade.speed;
				} else {
					fade.inFade = false;
				}
			break;

			case FADE_OUT: {
				if (fade.r_Color.a > 0.0f) {
					fade.r_Color.a -= fade.speed;
				} else {
					if (fade.inOut) {
						fade.inOut = false;
						fade.type = FADE_IN;
						fade.r_Color = {0.0f, 0.0f, 0.0f, 0.0f};
					} else {
						fade.inFade = false;
					}
				}
			}
			break;

			case FADE_BLINK:

			break;

			case FADE_IN_OUT:
				fade.type = FADE_OUT;
			break;

			default:
				std::cout << "effect not implemented" << std::endl;
			break;
		}

		
		m_Render->setProjectionMtx(ui_ortho);
		m_Render->setViewMtx(glm::mat4(1.0f));
		m_Render->setModelMtx(pos);
		renderRectangle(fadeTexture.tex->id, fade.r_Color);
	}

}

/*
 * isInFade
 * this function will return if the fade effect is running or no
 * return bool
 */
bool utils::isInFade() const { return fade.inFade; }


/*
 * renderNF3D_anim
 * when I written it I barely had idea about it, now only God knows.
 * no return
 */

void utils::renderNF3D_anim(unsigned int objNum, unsigned int var, int var2, nf3d* obj) {

    if (var == objNum) {
        modelMtx = glm::translate(modelMtx, glm::vec3(obj->model->emdSec2RelPos[var2].x,
													  obj->model->emdSec2RelPos[var2].y,
													  obj->model->emdSec2RelPos[var2].z));

        modelMtx = glm::rotate(modelMtx, glm::radians(obj->animFrame.vector[var2].x), glm::vec3(1.0f, 0.0f, 0.0f));
        modelMtx = glm::rotate(modelMtx, glm::radians(obj->animFrame.vector[var2].y), glm::vec3(0.0f, 1.0f, 0.0f));
        modelMtx = glm::rotate(modelMtx, glm::radians(obj->animFrame.vector[var2].z), glm::vec3(0.0f, 0.0f, 1.0f));
     	
        m_Render->setModelMtx(modelMtx);
    }
	
    for (unsigned int c = 0; c < obj->model->emdSec2Armature[var].meshCount; c++) {
        renderNF3D_anim(objNum, obj->model->emdSec2Mesh[var][c], var2, obj);
    }
}


/*
 * renderNF3D
 * this function will render Resident Evil 1.5 and 2 EMD files
 * no return
 */
void utils::renderNF3D(const glm::vec3& pos, const float& angle, nf3d* obj) {
	GLuint m_Color = glGetUniformLocation(m_Render->getCurrentShader(), "m_Color");
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, obj->getTexId());
	glUniform4f(m_Color, 1.0f, 1.0f, 1.0f, 1.0f);

	glBindBuffer(GL_ARRAY_BUFFER, obj->getVBO());

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (void*)0x0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (void*)0xC);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (void*)0x14);

	for (unsigned int i = 0; i < obj->model->emdTotalObj; i++) {
		modelMtx = glm::translate(glm::mat4(1.0f), pos);
	    modelMtx = glm::rotate(modelMtx, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));

		m_Render->setModelMtx(modelMtx);
		
		for (unsigned int j = 0; j < obj->model->emdTotalObj; j++) {
			renderNF3D_anim(i, j, j, obj);
		}

		glDrawArrays(GL_TRIANGLES, obj->vCnt[i].begin, obj->vCnt[i].total);
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}