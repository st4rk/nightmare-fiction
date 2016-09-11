#include "utils.h"

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

utils::utils() {
	window = NULL;
}

utils::~utils() {
	window = NULL;

	glDeleteBuffers(1, &utilsVBO);
}

/*
 * setContext
 * this function get glfw context and create the VBO used to draw the rectangles
 * and font stuff
 * no return
 */
void utils::setContext(GLFWwindow* window) {
	this->window = window;

	/*
	 * setup rectangle VBO
	 */
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
void utils::renderRectangle(GLuint texID, GLuint textureUnit) {
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texID);
	glUniform1i(textureUnit, 0);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, utilsVBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, utilsTexture);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}