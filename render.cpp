#include "render.h"


render::render() {
	window = NULL;
	vaoID  = 0;
}

render::~render() {
	glDeleteVertexArrays(1, &vaoID);
	vaoID  = 0;
}

/*
 * setProjectionMtx
 * change projection matrix to a new one
 * no return
 */
void render::setProjectionMtx(const glm::mat4& p_Matrix) {
	this->p_Matrix = p_Matrix;
	updateMVP();
}

/*
 * setViewMtx
 * change view matrix to a new one
 * no return
 */
void render::setViewMtx(const glm::mat4& v_Matrix) {
	this->v_Matrix = v_Matrix;
	updateMVP();
}

/*
 * setModelMtx
 * change model matrix to a new one
 * no return
 */
void render::setModelMtx(const glm::mat4& m_Matrix) {
	this->m_Matrix = m_Matrix;
	updateMVP();
}

/*
 * setShaderId
 * set a new shader id
 * update the textureUnit and MVP
 * no return
 */
void render::setShaderId(const GLuint& currentShader) {
	this->currentShader = currentShader;
	glUseProgram(currentShader);
	// get texture unit 
	texUnit = glGetUniformLocation(currentShader, "texUnit");
	// MODEL VIEW PROJECTION matrix shader
	mvpID = glGetUniformLocation(currentShader, "MVP");
}

/*
 * PRIVATE FUNCTION
 * updateMVP
 * update model, view, projection matrix 
 * no return
 */
void render::updateMVP() {
	glm::mat4 mvp = p_Matrix * v_Matrix * m_Matrix;
	glUniformMatrix4fv(mvpID, 1, GL_FALSE, &mvp[0][0]);
}

/*
 * swapBuffers
 * rendering scene and poll events
 */
void render::swapBuffers() {	
	glfwSwapBuffers(window);
	glfwPollEvents();
}

/*
 * clearScene
 * clear color and depth buffers and set new clear color
 */
void render::clearScene() {
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}
/*
 * initGL
 * deal with OpenGL initialization
 * return true if success to initialize all OpenGL stuff
 * return false if failed to initialize OpenGL stuff
 */
bool render::initGL() {

	// initialize GLFW context
	if ( !glfwInit() ) {
		std::cout << "Couldn't initialize glfw3 !" << std::endl;
		return false;
	}

	glfwWindowHint(GLFW_SAMPLES, RENDER_SAMPLES);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GL_CTX_MAJOR_VERSION);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GL_CTX_MINOR_VERSION); // using OpenGL 3.3

	window = glfwCreateWindow(RENDER_RES_WIDTH, RENDER_RES_HEIGHT, "NF Framework - 0.05a", NULL, NULL);

	if (window == NULL) {
		std::cout << "Error while creating a window, verify if your GPU support GL Version: " <<
		GL_CTX_MAJOR_VERSION << "." << GL_CTX_MINOR_VERSION << std::endl;
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = true;

	if ( glewInit() != GLEW_OK ) {
		std::cout << "Failed to initialize GLEW" << std::endl;
		return false;
	}


	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);

	// enable alpha
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
	// enable depth test
	glEnable(GL_DEPTH_TEST);

	// enable the three location used in code		
	glEnableVertexAttribArray(0); // XYZ
	glEnableVertexAttribArray(1); // UV
	glEnableVertexAttribArray(2); // Normal
	
	return true;
}


/*
 * getContext
 * this function get the window context created by the glfw initialization
 * return GLFWindow context
 */
GLFWwindow* render::getContext() { return window; }

/*
 * loadTexture
 * this function is used to load textures
 * return texture ID
 */
nTexture* render::loadTexture(const std::string& dir, bool remove, color rColor) {
	nTexture *nTex = new nTexture();

	if (!nTex->texture.loadIMG(dir, remove, rColor)) {
		std::cout << "Failed while loading texture " << dir << std::endl;
		return nullptr;
	}

	glGenTextures(1, &nTex->id);
	glBindTexture(GL_TEXTURE_2D, nTex->id);

	switch (nTex->texture.getFormat()) {
		case IMAGE_FORMAT_PNG:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, nTex->texture.getWidth(), nTex->texture.getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, nTex->texture.getTexture());
		break;

		case IMAGE_FORMAT_BMP:
			if (!remove)
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, nTex->texture.getWidth(), nTex->texture.getHeight(), 0, GL_BGR, GL_UNSIGNED_BYTE, nTex->texture.getTexture());
			else
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, nTex->texture.getWidth(), nTex->texture.getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, nTex->texture.getTexture());
		break;

		case IMAGE_FORMAT_TIM:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, nTex->texture.getWidth() * 2, nTex->texture.getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, nTex->texture.getTexture());
		break;

		default:
			std::cout << "format not found" << std::endl;
		break;
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	return nTex;
}

/*
 * getTexUnit
 * return texture unit
 */
const GLuint& render::getTexUnit() const { return texUnit; }

/*
 * getCurrentShader
 * return current program id
 */
const GLuint& render::getCurrentShader() const { return currentShader; }