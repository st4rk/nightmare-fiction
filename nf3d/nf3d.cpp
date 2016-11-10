#include "nf3d.h"

nf3d::nf3d(const std::string& dir, nTexture* tex, const NF3D_TYPE& type) {
	isAnimSet = 0;

	// TODO: Improve this, single format to all 3D model
	switch (type) {
		case NF3D_TYPE_EMD: {
			/* create model object */
			this->model.reset(new EMD(dir));
			/* set texture */
			this->tex = tex;

			/* create a new vbo */
			glGenBuffers(1, &vbo);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);

			/* build vertex object buffer and send to GPU */
			std::vector<GLfloat> objectBuffer;
			unsigned short uPage;

			float width_t = static_cast<float>(tex->texture.getWidth() * 2);
			float height_t = static_cast<float>(tex->texture.getHeight());

			vertexCnt node {0,0};
			for (unsigned int i = 0; i < model->emdTotalObj; i++) {
				node.begin += node.total;
				node.total = 0;

				for (unsigned int j = 0; j < model->emdObjectBuffer[i].triangles.triCount; j++) {
					/* texture page */
					uPage = ((model->emdTritexture[i][j].page & 0b00111111) * 128);
					/* vertex 1 */
					/* xyz */
					objectBuffer.push_back(static_cast<GLfloat>(model->emdVertex[i][model->emdTriangle[i][j].v0].x));
					objectBuffer.push_back(static_cast<GLfloat>(model->emdVertex[i][model->emdTriangle[i][j].v0].y));
					objectBuffer.push_back(static_cast<GLfloat>(model->emdVertex[i][model->emdTriangle[i][j].v0].z));
					/* uv */
					objectBuffer.push_back(static_cast<GLfloat>((model->emdTritexture[i][j].u0 + uPage) / width_t));
					objectBuffer.push_back(static_cast<GLfloat>((model->emdTritexture[i][j].v0) / height_t));
					/* normal to xyz */
					objectBuffer.push_back(static_cast<GLfloat>(model->emdNormal[i][model->emdTriangle[i][j].n0].x));
					objectBuffer.push_back(static_cast<GLfloat>(model->emdNormal[i][model->emdTriangle[i][j].n0].y));
					objectBuffer.push_back(static_cast<GLfloat>(model->emdNormal[i][model->emdTriangle[i][j].n0].z));
					/* vertex 1 */
					/* xyz */
					objectBuffer.push_back(static_cast<GLfloat>(model->emdVertex[i][model->emdTriangle[i][j].v1].x));
					objectBuffer.push_back(static_cast<GLfloat>(model->emdVertex[i][model->emdTriangle[i][j].v1].y));
					objectBuffer.push_back(static_cast<GLfloat>(model->emdVertex[i][model->emdTriangle[i][j].v1].z));
					/* uv */
					objectBuffer.push_back(static_cast<GLfloat>((model->emdTritexture[i][j].u1 + uPage) / width_t));
					objectBuffer.push_back(static_cast<GLfloat>((model->emdTritexture[i][j].v1) / height_t));
					/* normal to xyz */
					objectBuffer.push_back(static_cast<GLfloat>(model->emdNormal[i][model->emdTriangle[i][j].n1].x));
					objectBuffer.push_back(static_cast<GLfloat>(model->emdNormal[i][model->emdTriangle[i][j].n1].y));
					objectBuffer.push_back(static_cast<GLfloat>(model->emdNormal[i][model->emdTriangle[i][j].n1].z));
					/* xyz */
					objectBuffer.push_back(static_cast<GLfloat>(model->emdVertex[i][model->emdTriangle[i][j].v2].x));
					objectBuffer.push_back(static_cast<GLfloat>(model->emdVertex[i][model->emdTriangle[i][j].v2].y));
					objectBuffer.push_back(static_cast<GLfloat>(model->emdVertex[i][model->emdTriangle[i][j].v2].z));
					/* uv */
					objectBuffer.push_back(static_cast<GLfloat>((model->emdTritexture[i][j].u2 + uPage) / width_t));
					objectBuffer.push_back(static_cast<GLfloat>((model->emdTritexture[i][j].v2) / height_t));
					/* normal to xyz */
					objectBuffer.push_back(static_cast<GLfloat>(model->emdNormal[i][model->emdTriangle[i][j].n2].x));
					objectBuffer.push_back(static_cast<GLfloat>(model->emdNormal[i][model->emdTriangle[i][j].n2].y));
					objectBuffer.push_back(static_cast<GLfloat>(model->emdNormal[i][model->emdTriangle[i][j].n2].z));

					node.total += 3;
				}

				
				for (unsigned int j = 0; j < model->emdObjectBuffer[i].quads.quadCount; j++) {
					uPage = ((model->emdQuadTexture[i][j].page & 0b00111111) * 128);

					/* TRIANGLE 1 */
					objectBuffer.push_back(static_cast<GLfloat>(model->emdquadVertex[i][model->emdQuad[i][j].v0].x));
					objectBuffer.push_back(static_cast<GLfloat>(model->emdquadVertex[i][model->emdQuad[i][j].v0].y));
					objectBuffer.push_back(static_cast<GLfloat>(model->emdquadVertex[i][model->emdQuad[i][j].v0].z));

					objectBuffer.push_back(static_cast<GLfloat>((model->emdQuadTexture[i][j].u0 + uPage) / width_t));
					objectBuffer.push_back(static_cast<GLfloat>((model->emdQuadTexture[i][j].v0) / height_t));

					objectBuffer.push_back(static_cast<GLfloat>(model->emdNormal[i][model->emdQuad[i][j].n0].x));
					objectBuffer.push_back(static_cast<GLfloat>(model->emdNormal[i][model->emdQuad[i][j].n0].y));
					objectBuffer.push_back(static_cast<GLfloat>(model->emdNormal[i][model->emdQuad[i][j].n0].z));


					objectBuffer.push_back(static_cast<GLfloat>(model->emdquadVertex[i][model->emdQuad[i][j].v1].x));
					objectBuffer.push_back(static_cast<GLfloat>(model->emdquadVertex[i][model->emdQuad[i][j].v1].y));
					objectBuffer.push_back(static_cast<GLfloat>(model->emdquadVertex[i][model->emdQuad[i][j].v1].z));
		 
					objectBuffer.push_back(static_cast<GLfloat>((model->emdQuadTexture[i][j].u1 + uPage) / width_t));
					objectBuffer.push_back(static_cast<GLfloat>((model->emdQuadTexture[i][j].v1) / height_t));;

					objectBuffer.push_back(static_cast<GLfloat>(model->emdNormal[i][model->emdQuad[i][j].n1].x));
					objectBuffer.push_back(static_cast<GLfloat>(model->emdNormal[i][model->emdQuad[i][j].n1].y));
					objectBuffer.push_back(static_cast<GLfloat>(model->emdNormal[i][model->emdQuad[i][j].n1].z));


					objectBuffer.push_back(static_cast<GLfloat>(model->emdquadVertex[i][model->emdQuad[i][j].v2].x));
					objectBuffer.push_back(static_cast<GLfloat>(model->emdquadVertex[i][model->emdQuad[i][j].v2].y));
					objectBuffer.push_back(static_cast<GLfloat>(model->emdquadVertex[i][model->emdQuad[i][j].v2].z));

					objectBuffer.push_back(static_cast<GLfloat>((model->emdQuadTexture[i][j].u2 + uPage) / width_t));
					objectBuffer.push_back(static_cast<GLfloat>((model->emdQuadTexture[i][j].v2) / height_t));

					objectBuffer.push_back(static_cast<GLfloat>(model->emdNormal[i][model->emdQuad[i][j].n2].x));
					objectBuffer.push_back(static_cast<GLfloat>(model->emdNormal[i][model->emdQuad[i][j].n2].y));
					objectBuffer.push_back(static_cast<GLfloat>(model->emdNormal[i][model->emdQuad[i][j].n2].z));


					/* TRIANGLE 2 */
					objectBuffer.push_back(static_cast<GLfloat>(model->emdquadVertex[i][model->emdQuad[i][j].v1].x));
					objectBuffer.push_back(static_cast<GLfloat>(model->emdquadVertex[i][model->emdQuad[i][j].v1].y));
					objectBuffer.push_back(static_cast<GLfloat>(model->emdquadVertex[i][model->emdQuad[i][j].v1].z));
		 
					objectBuffer.push_back(static_cast<GLfloat>((model->emdQuadTexture[i][j].u1 + uPage) / width_t));
					objectBuffer.push_back(static_cast<GLfloat>((model->emdQuadTexture[i][j].v1) / height_t));;

					objectBuffer.push_back(static_cast<GLfloat>(model->emdNormal[i][model->emdQuad[i][j].n1].x));
					objectBuffer.push_back(static_cast<GLfloat>(model->emdNormal[i][model->emdQuad[i][j].n1].y));
					objectBuffer.push_back(static_cast<GLfloat>(model->emdNormal[i][model->emdQuad[i][j].n1].z));


					objectBuffer.push_back(static_cast<GLfloat>(model->emdquadVertex[i][model->emdQuad[i][j].v2].x));
					objectBuffer.push_back(static_cast<GLfloat>(model->emdquadVertex[i][model->emdQuad[i][j].v2].y));
					objectBuffer.push_back(static_cast<GLfloat>(model->emdquadVertex[i][model->emdQuad[i][j].v2].z));

					objectBuffer.push_back(static_cast<GLfloat>((model->emdQuadTexture[i][j].u2 + uPage) / width_t));
					objectBuffer.push_back(static_cast<GLfloat>((model->emdQuadTexture[i][j].v2) / height_t));

					objectBuffer.push_back(static_cast<GLfloat>(model->emdNormal[i][model->emdQuad[i][j].n2].x));
					objectBuffer.push_back(static_cast<GLfloat>(model->emdNormal[i][model->emdQuad[i][j].n2].y));
					objectBuffer.push_back(static_cast<GLfloat>(model->emdNormal[i][model->emdQuad[i][j].n2].z));


					objectBuffer.push_back(static_cast<GLfloat>(model->emdquadVertex[i][model->emdQuad[i][j].v3].x));
					objectBuffer.push_back(static_cast<GLfloat>(model->emdquadVertex[i][model->emdQuad[i][j].v3].y));
					objectBuffer.push_back(static_cast<GLfloat>(model->emdquadVertex[i][model->emdQuad[i][j].v3].z));

					objectBuffer.push_back(static_cast<GLfloat>((model->emdQuadTexture[i][j].u3 + uPage) / width_t));
					objectBuffer.push_back(static_cast<GLfloat>((model->emdQuadTexture[i][j].v3) / height_t));

					objectBuffer.push_back(static_cast<GLfloat>(model->emdNormal[i][model->emdQuad[i][j].n2].x));
					objectBuffer.push_back(static_cast<GLfloat>(model->emdNormal[i][model->emdQuad[i][j].n2].y));
					objectBuffer.push_back(static_cast<GLfloat>(model->emdNormal[i][model->emdQuad[i][j].n2].z));


					node.total += 6;
				} 
			
				vCnt.push_back(node);
			}
			glBufferData(GL_ARRAY_BUFFER, objectBuffer.size() * sizeof(GLfloat), &objectBuffer[0], GL_STATIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			animCnt = 0;

			isInterpolation = false;
			interTotal = 0.0f;
			interStep = 0.0f;

			emdSection = EMD_SECTION_4;
			emdSec4Animation = STAND_SEC4_ANIM_IDLE;
		}
		break;

		case NF3D_TYPE_PLW: {
			weapon.readFile(dir);
		}
		break;

		default:
			std::cout << "File format not found !" << std::endl;
		break;
	}

}


nf3d::~nf3d() {
	/* destroy vbo */
	glDeleteBuffers(1, &vbo);

	if (tex != nullptr) {
		delete tex;
		tex = nullptr;
	}
}

void nf3d::setAnimSection(const EMD_SECTION_LIST& emdSection) {
	this->emdSection = emdSection;
}

void nf3d::setSec2Animation(const STANDARD_SEC2_ANIMATION& emdSec2Animation) {
	if (this->emdSec2Animation != emdSec2Animation) {
		isInterpolation = true;

		interStep = 1.0f/8;
		interTotal = 0.0f;

		oldFrame = animFrame;
	}

	this->emdSec2Animation = emdSec2Animation;
}

void nf3d::setSec4Animation(const STANDARD_SEC4_ANIMATION& emdSec4Animation) {

	if (this->emdSec4Animation != emdSec4Animation) {
		isInterpolation = true;

		interStep = 1.0f/8;
		interTotal = 0.0f;

		oldFrame = animFrame;
	}

	this->emdSec4Animation = emdSec4Animation;
}

void nf3d::setAnimCnt(const unsigned int& animCnt) {
	this->animCnt = animCnt;
}


/*
 * run
 * run current animation frame
 * no return
 */
void nf3d::run() {
	static std::vector<EMD_SEC2_DATA_T> cAnimSet;
	static std::vector<EMD_ANIM_INFO> cAnimSetInfo;

	/**
	 * TODO: I wouldn't say again, you know
	 */
	switch (emdSection) {
		
		case EMD_SECTION_2:{
			cAnimSet = model->emdSec2Data;
			cAnimSetInfo = model->emdSec2AnimInfo;
		}
		break;

		case EMD_SECTION_4:{
			cAnimSet = model->emdSec4Data;
			cAnimSetInfo = model->emdSec4AnimInfo;
		}
		break;
	}

	if (isAnimSet) {
		cAnimSet = animSet;
		cAnimSetInfo = animSetInfo;
	}



	if (isInterpolation) {

		animCnt < cAnimSetInfo[emdSec4Animation].animCount - 1 ? animCnt++ : animCnt = 0;
		animFrame = animSet[animCnt + cAnimSetInfo[emdSec4Animation].animStart];

		for (unsigned int i = 0; i < animFrame.vector.size(); i++) {
			if (i > oldFrame.vector.size()) break;

			animFrame.vector[i].x = physics::interpolation::lerpAngle(oldFrame.vector[i].x, animFrame.vector[i].x, interTotal);
			animFrame.vector[i].y = physics::interpolation::lerpAngle(oldFrame.vector[i].y, animFrame.vector[i].y, interTotal);
			animFrame.vector[i].z = physics::interpolation::lerpAngle(oldFrame.vector[i].z, animFrame.vector[i].z, interTotal);
		}

		interTotal < 1.0f ? interTotal += interStep : isInterpolation = false;

	} else { 
		if (animCnt < cAnimSetInfo[emdSec4Animation].animCount - 1) {
			animCnt++;
		} else {
			animCnt = 0;
		}
		
		animFrame = cAnimSet[animCnt + cAnimSetInfo[emdSec4Animation].animStart];

	}	
}


/**
 * TODO: Remove this ridiculous macgyver
 */
void nf3d::setAnimSet(std::vector<EMD_SEC2_DATA_T> animSet, std::vector<EMD_ANIM_INFO> animSetInfo) {
	this->animSet = animSet;
	this->animSetInfo = animSetInfo;
	isAnimSet = true;
}

void nf3d::removeAnimSet() {
	isAnimSet = false;
}

const GLuint& nf3d::getVBO() { return vbo; }
const GLuint& nf3d::getTexId() { return tex->id; }
const EMD_SEC2_DATA_T& nf3d::getanimFrame() { return animFrame; }
const EMD_SECTION_LIST& nf3d::getAnimSection() { return emdSection; }
const STANDARD_SEC2_ANIMATION& nf3d::getSec2Animation() { return emdSec2Animation; }
const STANDARD_SEC4_ANIMATION& nf3d::getSec4Animation() { return emdSec4Animation; }
const unsigned int& nf3d::getAnimCnt() { return animCnt; }
