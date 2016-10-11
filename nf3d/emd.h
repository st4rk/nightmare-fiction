/*
 * EMD Loader
 */
#ifndef EMD_H
#define EMD_H

#include <iostream>
#include <cstdlib>
#include <sstream>
#include <cstdio>
#include <cstring>
#include <list>
#include <vector>

enum EMD_SECTION_LIST {
   EMD_SECTION_2 = 0,
   EMD_SECTION_4 = 1
};

enum STANDARD_SEC2_ANIMATION {
   STAND_SEC2_ANIM_BACKWARD  = 0,
   STAND_SEC2_ANIM_SBACKWARD = 1,
   STAND_SEC2_ANIM_DEATH     = 2,
   STAND_SEC2_ANIM_HIT       = 3,
   STAND_SEC2_ANIM_BACK_HIT  = 4,
   STAND_SEC2_ANIM_HIT_2     = 5,
   STAND_SEC2_ANIM_GET_ITEM  = 6,
   STAND_SEC2_ANIM_PUSH      = 7,
   STAND_SEC2_ANIM_PUSHING   = 8,
   STAND_SEC2_ANIM_INJU_WALK = 9
};

enum STANDARD_SEC4_ANIMATION {
   STAND_SEC4_ANIM_WALK      = 0,
   STAND_SEC4_ANIM_RUNNING   = 1,
   STAND_SEC4_ANIM_IDLE      = 2,
   STAND_SEC4_ANIM_INJU_WALK = 3,
   STAND_SEC4_ANIM_INJU_RUNN = 4,
   STAND_SEC4_ANIM_INJU_IDLE = 5,
   STAND_SEC4_ANIM_TINJ_WALK = 6,
   STAND_SEC4_ANIM_TINJ_RUNN = 7,
   STAND_SEC4_ANIM_TINJ_IDLE = 8,
   STAND_SEC4_ANIM_S_SHOOT   = 9,
   STAND_SEC4_ANIM_SHOOTING  = 10,
   STAND_SEC4_ANIM_AIM       = 11,
   STAND_SEC4_ANIM_USHOOTING = 12,
   STAND_SEC4_ANIM_UAIM      = 13,
   STAND_SEC4_ANIM_DSHOOTING = 14,
   STAND_SEC4_ANIM_DAIM      = 15,
   STAND_SEC4_ANIM_AMMO      = 16
};

struct EMD_HEADER_DIRECTORY {
	unsigned int dirOffset;
	unsigned int dirCount;
};

struct EMD_SECTION_1_HEADER {
	unsigned short dataCount;
	unsigned short dataOffset;
};

struct EMD_SECTION_2_HEADER {
	unsigned short relposOffset;
	unsigned short lenght;
	unsigned short count;
	unsigned short size;
};

struct EMD_SEC2_RELPOS_T {
	short x;
	short y;
	short z;
};

struct EMD_SEC2_ARMATURE_T {
	unsigned short meshCount;
	unsigned short offSet;
};

struct EMD_SEC2_VECTOR {
	float x;
	float y;
	float z;
};

struct EMD_SEC2_DATA_T {
	short xOffset;
	short yOffset;
	short zOffset;

	short xSpeed;
	short ySpeed;
	short zSpeed;

	std::vector<unsigned char> angles;
	std::vector<EMD_SEC2_VECTOR> vector;
};

struct EMD_SECTION_7_HEADER {
	unsigned int lenght; 
	unsigned int unk32; 
	unsigned int objCount; 
};

struct EMD_MODEL_TRIANGLES_T {
	unsigned int vertexOffset;
	unsigned int vertexCount;
	unsigned int normalOffset; 
	unsigned int normalCount;
	unsigned int triOffset;
	unsigned int triCount;
	unsigned int triTextureOffset;
};

struct EMD_MODEL_QUADS_T {
	unsigned int vertexOffset;
	unsigned int vertexCount;
	unsigned int normalOffset; 
	unsigned int normalCount;
	unsigned int quadOffset;
	unsigned int quadCount;
	unsigned int quadTextureOffset;
};

struct EMD_MODEL_OBJECT_T {
	EMD_MODEL_TRIANGLES_T triangles;
	EMD_MODEL_QUADS_T     quads;
};

struct EMD_VERTEX_T {
	signed short x;
	signed short y;
	signed short z;
	signed short zero;
};

struct EMD_NORMAL_T {
	signed short x;
	signed short y;
	signed short z;
	signed short zero;
};

struct EMD_TRIANGLE_T {
	unsigned short n0;
	unsigned short v0;
	unsigned short n1;
	unsigned short v1;
	unsigned short n2;
	unsigned short v2;	
};

struct EMD_QUAD_T {
	unsigned short n0;
	unsigned short v0;
	unsigned short n1;
	unsigned short v1;
	unsigned short n2;
	unsigned short v2;	
	unsigned short n3;
	unsigned short v3;	
};

struct EMD_TRITEXTURE_T {
	unsigned char u0;
	unsigned char v0;
	unsigned short clutid;
	unsigned char u1;
	unsigned char v1;
	unsigned short page;
	unsigned char u2;
	unsigned char v2;
	unsigned short zero;
};

struct EMD_QUADTEXTURE_T {
	unsigned char u0;
	unsigned char v0;
	unsigned short clutid;
	unsigned char u1;
	unsigned char v1;
	unsigned short page;
	unsigned char u2;
	unsigned char v2;
	unsigned short zero;
	unsigned char u3;
	unsigned char v3;
	unsigned short zero2;
};

struct EMD_ANIM_INFO {
   unsigned int animStart;
   unsigned int animCount;
};

class EMD {
public:
	EMD(const std::string& dir);

	~EMD();

	std::vector<EMD_MODEL_OBJECT_T> emdObjectBuffer;
	std::vector<std::vector<EMD_VERTEX_T>>  emdVertex;
	std::vector<std::vector<EMD_VERTEX_T>>  emdquadVertex;
	std::vector<std::vector<EMD_NORMAL_T>>  emdNormal;
	std::vector<std::vector<EMD_NORMAL_T>>  emdquadNormal;
	std::vector<std::vector<EMD_TRIANGLE_T>>  emdTriangle;
	std::vector<std::vector<EMD_QUAD_T>>  emdQuad;
	std::vector<std::vector<EMD_QUADTEXTURE_T>>  emdQuadTexture;
	std::vector<std::vector<EMD_TRITEXTURE_T>>  emdTritexture;
	// Section 2
	std::vector<EMD_SEC2_RELPOS_T>  emdSec2RelPos;
	std::vector<EMD_SEC2_ARMATURE_T> emdSec2Armature;

	EMD_SECTION_2_HEADER         emdSec2Header;
	std::vector<EMD_SEC2_DATA_T> emdSec2Data;
	std::vector<EMD_ANIM_INFO>   emdSec2AnimInfo;

	// Section 3 and Section 4
	EMD_SECTION_2_HEADER         emdSec4Header;
	std::vector<EMD_SEC2_DATA_T> emdSec4Data;
	std::vector<EMD_ANIM_INFO>   emdSec4AnimInfo;
	
	std::vector<EMD_SECTION_1_HEADER> emdSec3Header;
	unsigned int                 emdSec3AnimSkelT[100][500];
	unsigned short               sizeSec3Header;

	// Section 1
	std::vector<EMD_SECTION_1_HEADER>  emdSec1Header;
	std::vector<std::vector<unsigned char>> emdSec2Mesh;

	unsigned int                emdSize;
	unsigned int                totalAnim;
	unsigned int                emdTotalObj;
	unsigned int                emdSec1AnimSkelT[100][500];
	unsigned short              sizeSec1Header;

private:
	unsigned char              *emdBufferData;
	std::vector<unsigned int>   emdFileSection;

	EMD_HEADER_DIRECTORY        emdHeader;
	EMD_SECTION_7_HEADER        emdSec7Header;
};



#endif