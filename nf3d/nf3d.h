#ifndef _NF3D_H_
#define _NF3D_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>
#include "emd.h"
#include "../render.h"
#include "../physics.h"

struct vertexCnt {
	unsigned int begin;
	unsigned int total;
};

class nf3d {
public:
	nf3d(const std::string& dir, nTexture* tex);
	~nf3d();

	const GLuint& getVBO();
	const GLuint& getTexId();
	const EMD_SEC2_DATA_T& getanimFrame();
	const EMD_SECTION_LIST& getAnimSection();
	const STANDARD_SEC2_ANIMATION& getSec2Animation();
	const STANDARD_SEC4_ANIMATION& getSec4Animation();
	const unsigned int& getAnimCnt();

	void run();

	void setAnimSection(const EMD_SECTION_LIST& emdSection);
	void setSec2Animation(const STANDARD_SEC2_ANIMATION& emdSec2Animation);
	void setSec4Animation(const STANDARD_SEC4_ANIMATION& emdSec4Animation);
	void setAnimCnt(const unsigned int& animCnt);

	std::unique_ptr<EMD> model;
	std::vector<vertexCnt> vCnt;
	EMD_SEC2_DATA_T animFrame;

private:
	nTexture* tex;
	GLuint vbo;
	
	bool isInterpolation;

	float interTotal;
	float interStep;
	EMD_SEC2_DATA_T oldFrame;

	EMD_SECTION_LIST emdSection;
	STANDARD_SEC2_ANIMATION emdSec2Animation;
	STANDARD_SEC4_ANIMATION emdSec4Animation;


	unsigned int animCnt;
};

#endif