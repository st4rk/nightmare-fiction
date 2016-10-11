#include "nf3d.h"

nf3d::nf3d(const std::string& dir, nTexture* tex) {
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
			/* normal to xyz */
			//objectBuffer.push_back(static_cast<GLfloat>(model->emdNormal[i][model->emdTriangle[i][j].n0].x));
			//objectBuffer.push_back(static_cast<GLfloat>(model->emdNormal[i][model->emdTriangle[i][j].n0].y));
			//objectBuffer.push_back(static_cast<GLfloat>(model->emdNormal[i][model->emdTriangle[i][j].n0].z));
			/* uv */
			objectBuffer.push_back(static_cast<GLfloat>((model->emdTritexture[i][j].u0 + uPage) / width_t));
			objectBuffer.push_back(static_cast<GLfloat>((model->emdTritexture[i][j].v0) / height_t));
			/* vertex 1 */
			/* xyz */
			objectBuffer.push_back(static_cast<GLfloat>(model->emdVertex[i][model->emdTriangle[i][j].v1].x));
			objectBuffer.push_back(static_cast<GLfloat>(model->emdVertex[i][model->emdTriangle[i][j].v1].y));
			objectBuffer.push_back(static_cast<GLfloat>(model->emdVertex[i][model->emdTriangle[i][j].v1].z));
			/* normal to xyz */
			//objectBuffer.push_back(static_cast<GLfloat>(model->emdNormal[i][model->emdTriangle[i][j].n1].x));
			//objectBuffer.push_back(static_cast<GLfloat>(model->emdNormal[i][model->emdTriangle[i][j].n1].y));
			//objectBuffer.push_back(static_cast<GLfloat>(model->emdNormal[i][model->emdTriangle[i][j].n1].z));
			/* uv */
			objectBuffer.push_back(static_cast<GLfloat>((model->emdTritexture[i][j].u1 + uPage) / width_t));
			objectBuffer.push_back(static_cast<GLfloat>((model->emdTritexture[i][j].v1) / height_t));
			/* vertex 1 */
			/* xyz */
			objectBuffer.push_back(static_cast<GLfloat>(model->emdVertex[i][model->emdTriangle[i][j].v2].x));
			objectBuffer.push_back(static_cast<GLfloat>(model->emdVertex[i][model->emdTriangle[i][j].v2].y));
			objectBuffer.push_back(static_cast<GLfloat>(model->emdVertex[i][model->emdTriangle[i][j].v2].z));
			/* normal to xyz */
			//objectBuffer.push_back(static_cast<GLfloat>(model->emdNormal[i][model->emdTriangle[i][j].n2].x));
			//objectBuffer.push_back(static_cast<GLfloat>(model->emdNormal[i][model->emdTriangle[i][j].n2].y));
			//objectBuffer.push_back(static_cast<GLfloat>(model->emdNormal[i][model->emdTriangle[i][j].n2].z));
			/* uv */
			objectBuffer.push_back(static_cast<GLfloat>((model->emdTritexture[i][j].u2 + uPage) / width_t));
			objectBuffer.push_back(static_cast<GLfloat>((model->emdTritexture[i][j].v2) / height_t));

			node.total++;
		}

		
		for (unsigned int j = 0; j < model->emdObjectBuffer[i].quads.quadCount; j++) {

			uPage = ((model->emdQuadTexture[i][j].page & 0b00111111) * 128);

			/* TRIANGLE 1 */
			objectBuffer.push_back(static_cast<GLfloat>(model->emdquadVertex[i][model->emdQuad[i][j].v0].x));
			objectBuffer.push_back(static_cast<GLfloat>(model->emdquadVertex[i][model->emdQuad[i][j].v0].y));
			objectBuffer.push_back(static_cast<GLfloat>(model->emdquadVertex[i][model->emdQuad[i][j].v0].z));

			//objectBuffer.push_back(static_cast<GLfloat>(model->emdNormal[i][model->emdQuad[i][j].n0].x));
			//objectBuffer.push_back(static_cast<GLfloat>(model->emdNormal[i][model->emdQuad[i][j].n0].y));
			//objectBuffer.push_back(static_cast<GLfloat>(model->emdNormal[i][model->emdQuad[i][j].n0].z));

			objectBuffer.push_back(static_cast<GLfloat>((model->emdQuadTexture[i][j].u0 + uPage) / width_t));
			objectBuffer.push_back(static_cast<GLfloat>((model->emdQuadTexture[i][j].v0) / height_t));

			objectBuffer.push_back(static_cast<GLfloat>(model->emdquadVertex[i][model->emdQuad[i][j].v1].x));
			objectBuffer.push_back(static_cast<GLfloat>(model->emdquadVertex[i][model->emdQuad[i][j].v1].y));
			objectBuffer.push_back(static_cast<GLfloat>(model->emdquadVertex[i][model->emdQuad[i][j].v1].z));

			//objectBuffer.push_back(static_cast<GLfloat>(model->emdNormal[i][model->emdQuad[i][j].n1].x));
			//objectBuffer.push_back(static_cast<GLfloat>(model->emdNormal[i][model->emdQuad[i][j].n1].y));
			//objectBuffer.push_back(static_cast<GLfloat>(model->emdNormal[i][model->emdQuad[i][j].n1].z));
 
			objectBuffer.push_back(static_cast<GLfloat>((model->emdQuadTexture[i][j].u1 + uPage) / width_t));
			objectBuffer.push_back(static_cast<GLfloat>((model->emdQuadTexture[i][j].v1) / height_t));;

			objectBuffer.push_back(static_cast<GLfloat>(model->emdquadVertex[i][model->emdQuad[i][j].v2].x));
			objectBuffer.push_back(static_cast<GLfloat>(model->emdquadVertex[i][model->emdQuad[i][j].v2].y));
			objectBuffer.push_back(static_cast<GLfloat>(model->emdquadVertex[i][model->emdQuad[i][j].v2].z));

			//objectBuffer.push_back(static_cast<GLfloat>(model->emdNormal[i][model->emdQuad[i][j].n2].x));
			//objectBuffer.push_back(static_cast<GLfloat>(model->emdNormal[i][model->emdQuad[i][j].n2].y));
			//objectBuffer.push_back(static_cast<GLfloat>(model->emdNormal[i][model->emdQuad[i][j].n2].z));

			objectBuffer.push_back(static_cast<GLfloat>((model->emdQuadTexture[i][j].u2 + uPage) / width_t));
			objectBuffer.push_back(static_cast<GLfloat>((model->emdQuadTexture[i][j].v2) / height_t));

			/* TRIANGLE 2 */
			objectBuffer.push_back(static_cast<GLfloat>(model->emdquadVertex[i][model->emdQuad[i][j].v1].x));
			objectBuffer.push_back(static_cast<GLfloat>(model->emdquadVertex[i][model->emdQuad[i][j].v1].y));
			objectBuffer.push_back(static_cast<GLfloat>(model->emdquadVertex[i][model->emdQuad[i][j].v1].z));

			//objectBuffer.push_back(static_cast<GLfloat>(model->emdNormal[i][model->emdQuad[i][j].n1].x));
			//objectBuffer.push_back(static_cast<GLfloat>(model->emdNormal[i][model->emdQuad[i][j].n1].y));
			//objectBuffer.push_back(static_cast<GLfloat>(model->emdNormal[i][model->emdQuad[i][j].n1].z));
 
			objectBuffer.push_back(static_cast<GLfloat>((model->emdQuadTexture[i][j].u1 + uPage) / width_t));
			objectBuffer.push_back(static_cast<GLfloat>((model->emdQuadTexture[i][j].v1) / height_t));;

			objectBuffer.push_back(static_cast<GLfloat>(model->emdquadVertex[i][model->emdQuad[i][j].v2].x));
			objectBuffer.push_back(static_cast<GLfloat>(model->emdquadVertex[i][model->emdQuad[i][j].v2].y));
			objectBuffer.push_back(static_cast<GLfloat>(model->emdquadVertex[i][model->emdQuad[i][j].v2].z));

			//objectBuffer.push_back(static_cast<GLfloat>(model->emdNormal[i][model->emdQuad[i][j].n2].x));
			//objectBuffer.push_back(static_cast<GLfloat>(model->emdNormal[i][model->emdQuad[i][j].n2].y));
			//objectBuffer.push_back(static_cast<GLfloat>(model->emdNormal[i][model->emdQuad[i][j].n2].z));

			objectBuffer.push_back(static_cast<GLfloat>((model->emdQuadTexture[i][j].u2 + uPage) / width_t));
			objectBuffer.push_back(static_cast<GLfloat>((model->emdQuadTexture[i][j].v2) / height_t));

			objectBuffer.push_back(static_cast<GLfloat>(model->emdquadVertex[i][model->emdQuad[i][j].v3].x));
			objectBuffer.push_back(static_cast<GLfloat>(model->emdquadVertex[i][model->emdQuad[i][j].v3].y));
			objectBuffer.push_back(static_cast<GLfloat>(model->emdquadVertex[i][model->emdQuad[i][j].v3].z));

			//objectBuffer.push_back(static_cast<GLfloat>(model->emdNormal[i][model->emdQuad[i][j].n2].x));
			//objectBuffer.push_back(static_cast<GLfloat>(model->emdNormal[i][model->emdQuad[i][j].n2].y));
			//objectBuffer.push_back(static_cast<GLfloat>(model->emdNormal[i][model->emdQuad[i][j].n2].z));

			objectBuffer.push_back(static_cast<GLfloat>((model->emdQuadTexture[i][j].u3 + uPage) / width_t));
			objectBuffer.push_back(static_cast<GLfloat>((model->emdQuadTexture[i][j].v3) / height_t));

			node.total += 2;
		} 
	
		node.total *= 3;
		vCnt.push_back(node);
	}
	glBufferData(GL_ARRAY_BUFFER, objectBuffer.size() * sizeof(GLfloat), &objectBuffer[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	animCnt = 0;
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
	this->emdSec2Animation = emdSec2Animation;
}

void nf3d::setSec4Animation(const STANDARD_SEC4_ANIMATION& emdSec4Animation) {
	this->emdSec4Animation = emdSec4Animation;
}

void nf3d::setAnimCnt(const unsigned int& animCnt) {
	this->animCnt = animCnt;
}


/*
 * runAnimation
 * run current animation frame
 * no return
 */
void nf3d::runAnimation() {
	switch (emdSection) {
		
		case EMD_SECTION_2:{

		}
		break;

		case EMD_SECTION_4:{
			if (animCnt < model->emdSec4AnimInfo[emdSec4Animation].animCount - 1) {
				animCnt++;
			} else {
				animCnt = 0;
			}
			
			animFrame = model->emdSec4Data[animCnt + model->emdSec4AnimInfo[emdSec4Animation].animStart];
		}
		break;
	}
}

const GLuint& nf3d::getVBO() { return vbo; }
const GLuint& nf3d::getTexId() { return tex->id; }
const EMD_SEC2_DATA_T& nf3d::getanimFrame() { return animFrame; }
const EMD_SECTION_LIST& nf3d::getAnimSection() { return emdSection; }
const STANDARD_SEC2_ANIMATION& nf3d::getSec2Animation() { return emdSec2Animation; }
const STANDARD_SEC4_ANIMATION& nf3d::getSec4Animation() { return emdSec4Animation; }
const unsigned int& nf3d::getAnimCnt() { return animCnt; }
