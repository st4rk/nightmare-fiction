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
 * setPerspective
 * modify the game perspective
 * no return
 */
void render::setPerspective(const float& angle, const int& width, const int& height) {
	// TODO: arbitrary values to NEAR and FAR
	p_Matrix = glm::perspective(glm::radians(angle), (float) width / (float) height, 0.1f, 100.0f);
}

/*
 * setCam
 * modify the game camera using lookAt
 * no return
 */
void render::setCam(const glm::vec3& eye, const glm::vec3& center, const glm::vec3& up) {
	v_Matrix = glm::lookAt(eye, center, up);
}


/*
 * swapBuffers
 * update mvp matrix, rendering scene and poll events
 */
void render::swapBuffers() {	
	glm::mat4 mvp = p_Matrix * v_Matrix * m_Matrix;
	glUniformMatrix4fv(mvpID, 1, GL_FALSE, &mvp[0][0]);

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

	window = glfwCreateWindow(RENDER_RES_WIDTH, RENDER_RES_HEIGHT, "NF Framework - 0.02a", NULL, NULL);

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

	// load shader
	programID = LoadShaders( "shaders/vertexShader.glsl", "shaders/fragmentShader.glsl" );

	// get texture unit 
	texUnit = glGetUniformLocation(programID, "myTextureSampler");

	// MODEL VIEW PROJECTION matrix shader
	mvpID = glGetUniformLocation(programID, "MVP");
	
	// using the standard shader
	glUseProgram(programID);

	// enable alpha
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, nTex->texture.getWidth(), nTex->texture.getHeight(), 0, GL_BGR, GL_UNSIGNED_BYTE, nTex->texture.getTexture());
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
GLuint render::getTexUnit() const { return texUnit; }

/*
 * getProgramId
 * return current program id
 */
GLuint render::getProgramId() const { return programID; }