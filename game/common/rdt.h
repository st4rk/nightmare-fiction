#ifndef _RDT_H_
#define _RDT_H_

#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <vector>

/*
 * Resident Evil 1 
 * RDT Information
 */ 

#define STAGE(x) (x >> 5)
#define ROOM(x)  (x & 0x1F)

struct RDT_RE1_PART_T {
	int unk_pos_x;
	int unk_pos_y;
	int unk_pos_z;
	unsigned int unk0[2];
};

struct RDT_RE1_HEADER_T {
	char unk0;
	char num_cameras;
	char num_sound_banks;
	char unk1[3];
	unsigned short unk2[3];

	RDT_RE1_PART_T unk3[3];
};

struct RDT_RE1_CAMERA_POS_T {
	signed int mask_offset;
	signed int tim_mask_offset;

	signed int positionX;
	signed int positionY;
	signed int positionZ;
	signed int targetX;
	signed int targetY;
	signed int targetZ;
	signed int unk[3];
};

struct RDT_RE1_CAMERA_SWITCH_T {
	unsigned short to;
	unsigned short from;
	signed short x1;
	signed short z1;
	signed short x2;
	signed short z2;
	signed short x3;
	signed short z3;
	signed short x4;
	signed short z4;
};

struct RDT_RE1_SCA_HEADER_T {
	unsigned short cx;
	unsigned short cy;
	unsigned int   counts[5];
};

struct RDT_RE1_SCA_OBJ_T {
	unsigned short x1; 
	unsigned short z1; 
	unsigned short x2; // W
	unsigned short z2; // D
	unsigned char  type;
	unsigned char  id;
	unsigned short floor;
};

struct script_door_set_re1 {
	unsigned char opcode;
	unsigned char id;
	unsigned short x;
	unsigned short y;
	unsigned short w;
	unsigned short h;
	unsigned char unk0[5];
	unsigned char next_stage_and_room;
	unsigned short next_x;
	unsigned short next_y;
	unsigned short next_z;
	unsigned short next_dir;
	unsigned short unk1;
};


/*
 * Resident Evil 2 prototype 
 * Resident Evil 2 
 * RDT Information
 */
struct RDT_HEADER_T {
	unsigned char nSprite;
	unsigned char nCut; // Quantidade de cameras 
	unsigned char nOmodel; 
	unsigned char nItem;
	unsigned char nDoor;
	unsigned char nRoom_at;
	unsigned char Reverb_lv;
	unsigned char nSprite_max;
};


struct RDT_CAMERA_POS_T {
	unsigned short endFlag;
	unsigned short viewR;
	signed int positionX;
	signed int positionY;
	signed int positionZ;
	signed int targetX;
	signed int targetY;
	signed int targetZ;
	unsigned int pSprite;
};


struct RDT_COLI_HEADER_T {
	signed short cx;
	signed short cz;
	unsigned int amount; // five 4 bytes will be plus, the total is the total of
						   // collision, the total of colission will be (arraySum - 1)
	signed int ceiling;
	unsigned int dummy; 
};

struct RDT_OFFSET6ELT_T {
	signed short x;
	signed short z;
	unsigned short w;
	unsigned short h;
	unsigned short id;
	unsigned short type;
	unsigned int floor;
};

struct RDT_LIGHT_COLOR_T {
	unsigned char R;
	unsigned char G;
	unsigned char B;
};

struct RDT_LIGHT_POS_T {
	short X;
	short Y;
	short Z;
};

struct RDT_LIGHT_T {
	unsigned short    lightType[2];
	RDT_LIGHT_COLOR_T colorLight[3];
	RDT_LIGHT_COLOR_T colorAmbient;
	RDT_LIGHT_POS_T   lightPos[3];
	unsigned short    brightNess[3];
};

struct RDT_coli_1_5 {
	unsigned short W;
	unsigned short D;
	signed short X;
	signed short Z;
	unsigned short id;
	unsigned short Floor;
};


struct RDT_CAMERA_SWITCH_T {
	unsigned char beFlag;
	unsigned char nFloor;
	unsigned char cam0;
	unsigned char cam1;
	signed short x1;
	signed short z1;
	signed short x2;
	signed short z2;
	signed short x3;
	signed short z3;
	signed short x4;
	signed short z4;
};

enum RDT_TYPE_LIST {
	RDT_TYPE_RE1,
	RDT_TYPE_RE2_PROTO,
	RDT_TYPE_RE2,
	RDT_TYPE_RE3
};


class RDT {
public:
	RDT(const std::string& dir, const RDT_TYPE_LIST& rdtType);
	~RDT();

	std::vector<RDT_CAMERA_POS_T>          rdtCameraPos;
	RDT_HEADER_T                           rdtHeader;
	std::vector<RDT_LIGHT_T>               rdtLight;
	RDT_COLI_HEADER_T                      rdtCollisionHeader;
	std::vector<RDT_OFFSET6ELT_T>          rdtCollisionArray;
	std::vector<RDT_CAMERA_SWITCH_T>       rdtCameraSwitch;

	RDT_RE1_HEADER_T                       rdtRE1Header;
	std::vector<RDT_RE1_CAMERA_POS_T>      rdtRE1CameraPos;
	RDT_RE1_SCA_HEADER_T                   rdtRE1ColisionHeader;
	std::vector<RDT_RE1_SCA_OBJ_T>         rdtRE1ColissionArray;
	std::vector<RDT_RE1_CAMERA_SWITCH_T>   rdtRE1CameraSwitch;

	std::vector<unsigned char> RDT_RE1_SCD_DATA;
	unsigned short scdSize;
	unsigned int door_set_len;
//	script_door_set_re1 door_set_re1[0x10];

private:
	unsigned char      *rdtBuffer;
	unsigned int        rdtObjectList[23];
	unsigned int        rdtSize;

	std::vector<unsigned short> rdtSCD;

	RDT_TYPE_LIST rdtType;


};

#endif