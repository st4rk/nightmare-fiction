#include "rdt.h"


/**
 * Resident Evil 1 Script Interpreter
 * opcodes
 */

void NOP(RDT *obj, unsigned int *len) {
	*len += 2;
}

void IF(RDT *obj, unsigned int *len) {
	*len += 2;
}

void ELSE(RDT *obj, unsigned int *len) {
	*len += 2;
}

void ENDIF(RDT *obj, unsigned int *len) {
	*len += 2;
}

void BIT_TEST(RDT *obj, unsigned int *len) {
	*len += 4;
}

void BIT_OP(RDT *obj, unsigned int *len) {
	*len += 4;
}

void OBJ06_TEST(RDT *obj, unsigned int *len) {
	*len += 4;
}

void OBJ07_TEST(RDT *obj, unsigned int *len) {
	*len += 6;
}

void STAGEROOMCAM_SET(RDT *obj, unsigned int *len) {
	*len += 4;
}

void CUT_SET(RDT *obj, unsigned int *len) {
	*len += 2;
}

void CUT_SET_2(RDT *obj, unsigned int *len) {
	*len += 2;
}

void UNK_OP_0x0B(RDT *obj, unsigned int *len) {
	*len += 4;
}

void DOOR_SET(RDT *obj, unsigned int *len) {
	SCD_DOOR node;

	node.nStage    = STAGE(*(unsigned char*)(&obj->SCD_DATA[0] + *len + 15));
	node.nRoom     = *(unsigned char*)(&obj->SCD_DATA[0] + *len + 15) & 0x1F;

	node.x         = *(short*)(&obj->SCD_DATA[0] + *len + 2);
	node.y         = *(short*)(&obj->SCD_DATA[0] + *len + 4);
	node.w         = *(short*)(&obj->SCD_DATA[0] + *len + 6);
	node.h         = *(short*)(&obj->SCD_DATA[0] + *len + 8);

	node.next_x   = *(short*)(&obj->SCD_DATA[0] + *len + 16);
	node.next_y   = *(short*)(&obj->SCD_DATA[0] + *len + 18);
	node.next_z   = *(short*)(&obj->SCD_DATA[0] + *len + 20);
	node.next_dir = *(short*)(&obj->SCD_DATA[0] + *len + 22);

	obj->doorList.push_back(node);
	*len += 26;
}

void ITEM_SET(RDT *obj, unsigned int *len) {
	*len += 18;
}

void UNK_OP_0x0F(RDT *obj, unsigned int *len) {
	*len += 8;
}

void OBJ10_TEST(RDT *obj, unsigned int *len) {
	*len += 2;
}

void OBJ11_TEST(RDT *obj, unsigned int *len) {
	*len += 2;
}

void ITEM_0x12(RDT *obj, unsigned int *len) {
	*len += 10;
}

void ITEM_0x13(RDT *obj, unsigned int *len) {
	*len += 4;
}

void UNK_OP_0x14(RDT *obj, unsigned int *len) {
	*len += 4;
}

void UNK_OP_0x15(RDT *obj, unsigned int *len) {
	*len += 2;
}

void UNK_OP_0x16(RDT *obj, unsigned int *len) {
	*len += 2;
}

void UNK_OP_0x17(RDT *obj, unsigned int *len) {
	*len += 10;
}

void ITEM_MODEL_SET(RDT *obj, unsigned int *len) {
	*len += 26;
}

void OBJ19_SET(RDT *obj, unsigned int *len) {
	*len += 4;
}

void UNK_OP_0x1A(RDT *obj, unsigned int *len) {
	*len += 2;
}

void EM_SET(RDT *obj, unsigned int *len) {
	*len += 22;
}

void UNK_OP_0x1C(RDT *obj, unsigned int *len) {
	*len += 6;
}

void UNK_OP_0x1D(RDT *obj, unsigned int *len) {
	*len += 2;
}

void UNK_OP_0x1E(RDT *obj, unsigned int *len) {
	*len += 4;
}

void OM_SET(RDT *obj, unsigned int *len) {
	*len += 28;
}

void PLAYER_POS_SET(RDT *obj, unsigned int *len) {
	*len += 14;
}

void EM_POS_SET(RDT *obj, unsigned int *len) {
	*len += 14;
}

void UNK_OP_0x22(RDT *obj, unsigned int *len) {
	*len += 4;
}

void UNK_OP_0x23(RDT *obj, unsigned int *len) {
	*len += 2;
}

void UNK_OP_0x24(RDT *obj, unsigned int *len) {
	*len += 4;
}

void UNK_OP_0x25(RDT *obj, unsigned int *len) {
	*len += 4;
}

void UNK_OP_0x26(RDT *obj, unsigned int *len) {
	*len += 2;
}

void UNK_OP_0x27(RDT *obj, unsigned int *len) {
	*len += 2;
}

void UNK_OP_0x28(RDT *obj, unsigned int *len) {
	*len += 2;
}

void UNK_OP_0x29(RDT *obj, unsigned int *len) {
	*len += 2;
}

void UNK_OP_0x2A(RDT *obj, unsigned int *len) {
	*len += 12;
}

void UNK_OP_0x2B(RDT *obj, unsigned int *len) {
	*len += 4;
}

void UNK_OP_0x2C(RDT *obj, unsigned int *len) {
	*len += 2;
}

void UNK_OP_0x2D(RDT *obj, unsigned int *len) {
	*len += 4;
}

void UNK_OP_0x2E(RDT *obj, unsigned int *len) {
	*len += 4;
}

void UNK_OP_0x2F(RDT *obj, unsigned int *len) {
	*len += 4;
}

void UNK_OP_0x30(RDT *obj, unsigned int *len) {
	*len += 12;
}

void UNK_OP_0x31(RDT *obj, unsigned int *len) {
	*len += 4;
}

void UNK_OP_0x32(RDT *obj, unsigned int *len) {
	*len += 4;
}

void UNK_OP_0x33(RDT *obj, unsigned int *len) {
	*len += 2;
}

void UNK_OP_0x34(RDT *obj, unsigned int *len) {
	*len += 8;
}

void UNK_OP_0x35(RDT *obj, unsigned int *len) {
	*len += 4;
}

void UNK_OP_0x36(RDT *obj, unsigned int *len) {
	*len += 4;
}

void UNK_OP_0x37(RDT *obj, unsigned int *len) {
	*len += 4;
}

void UNK_OP_0x38(RDT *obj, unsigned int *len) {
	*len += 4;
}

void UNK_OP_0x39(RDT *obj, unsigned int *len) {
	*len += 2;
}

void UNK_OP_0x3A(RDT *obj, unsigned int *len) {
	*len += 4;
}

void UNK_OP_0x3B(RDT *obj, unsigned int *len) {
	*len += 6;
}

void UNK_OP_0x3C(RDT *obj, unsigned int *len) {
	*len += 6;
}

void UNK_OP_0x3D(RDT *obj, unsigned int *len) {
	*len += 12;
}

void UNK_OP_0x3E(RDT *obj, unsigned int *len) {
	*len += 2;
}

void UNK_OP_0x3F(RDT *obj, unsigned int *len) {
	*len += 6;
}

void UNK_OP_0x40(RDT *obj, unsigned int *len) {
	*len += 16;
}

void UNK_OP_0x41(RDT *obj, unsigned int *len) {
	*len += 4;
}

void UNK_OP_0x42(RDT *obj, unsigned int *len) {
	*len += 4;
}

void UNK_OP_0x43(RDT *obj, unsigned int *len) {
	*len += 4;
}

void UNK_OP_0x44(RDT *obj, unsigned int *len) {
	*len += 2;
}

void UNK_OP_0x45(RDT *obj, unsigned int *len) {
	*len += 2;
}

void UNK_OP_0x46(RDT *obj, unsigned int *len) {
	*len += 44;
}

void UNK_OP_0x47(RDT *obj, unsigned int *len) {
	*len += 14;
}

void UNK_OP_0x48(RDT *obj, unsigned int *len) {
	*len += 2;
}

void UNK_OP_0x49(RDT *obj, unsigned int *len) {
	*len += 2;
}

void UNK_OP_0x4A(RDT *obj, unsigned int *len) {
	*len += 2;
}

void UNK_OP_0x4B(RDT *obj, unsigned int *len) {
	*len += 2;
}

void UNK_OP_0x4C(RDT *obj, unsigned int *len) {
	*len += 4;
}

void UNK_OP_0x4D(RDT *obj, unsigned int *len) {
	*len += 2;
}

void UNK_OP_0x4E(RDT *obj, unsigned int *len) {
	*len += 4;
}

void UNK_OP_0x4F(RDT *obj, unsigned int *len) {
	*len += 2;
}

void UNK_OP_0x50(RDT *obj, unsigned int *len) {
	*len += 2;
}

/* Not an Instruction aka macgyver */
void NaI(RDT *obj, unsigned int *len) {
	*len += 0x4000;
}

/**
 * Resident Evil 1 Interpreter opcode table 
 * base: http://rewiki.regengedanken.de/wiki/.RDT_%28Resident_Evil%29
 * TODO: Reverse RE1 and look for all opcodes
 */
static void (*re1_opcode_table[])(RDT *obj, unsigned int *len) = 
{

	NOP,            IF,          ELSE,             ENDIF,       BIT_TEST,    BIT_OP, 
	OBJ06_TEST,     OBJ07_TEST,  STAGEROOMCAM_SET, CUT_SET,     CUT_SET_2,   UNK_OP_0x0B,
	DOOR_SET,       ITEM_SET,    NOP,              UNK_OP_0x0F, OBJ10_TEST,  OBJ11_TEST,
	ITEM_0x12,      ITEM_0x13,   UNK_OP_0x14,      UNK_OP_0x15, UNK_OP_0x16, UNK_OP_0x17, 
	ITEM_MODEL_SET, OBJ19_SET,   UNK_OP_0x1A,      EM_SET,      UNK_OP_0x1C, UNK_OP_0x1D, 
	UNK_OP_0x1E,    OM_SET,      PLAYER_POS_SET,   EM_POS_SET,  UNK_OP_0x22, UNK_OP_0x23, 
	UNK_OP_0x24,    UNK_OP_0x25, UNK_OP_0x26,      UNK_OP_0x27, UNK_OP_0x28, UNK_OP_0x29,
	UNK_OP_0x2A,    UNK_OP_0x2B, UNK_OP_0x2C,      UNK_OP_0x2D, UNK_OP_0x2F, UNK_OP_0x30, 
	UNK_OP_0x31,    UNK_OP_0x32, UNK_OP_0x33,      UNK_OP_0x34, UNK_OP_0x35, UNK_OP_0x36, 
	UNK_OP_0x37,    UNK_OP_0x38, UNK_OP_0x39,      UNK_OP_0x3A, UNK_OP_0x3B, UNK_OP_0x3C,
	UNK_OP_0x3D,    UNK_OP_0x3E, UNK_OP_0x3F,      UNK_OP_0x40, UNK_OP_0x41, UNK_OP_0x42, 
	UNK_OP_0x43,    UNK_OP_0x44, UNK_OP_0x45,      UNK_OP_0x46, UNK_OP_0x47, UNK_OP_0x48, 
	UNK_OP_0x49,    UNK_OP_0x4A, UNK_OP_0x4B,      UNK_OP_0x4C, UNK_OP_0x4D, UNK_OP_0x4E,
	UNK_OP_0x4F,    UNK_OP_0x50, NaI,              NaI,         NaI,         NaI,             
	NaI,            NaI,         NaI,              NaI,         NaI,         NaI,             
	NaI,            NaI,         NaI,              NaI,         NaI,         NaI,             
	NaI,            NaI,         NaI,              NaI,         NaI,         NaI,             
	NaI,            NaI,         NaI,              NaI,         NaI,         NaI,             
	NaI,            NaI,         NaI,              NaI,         NaI,         NaI,             
	NaI,            NaI,         NaI,              NaI,         NaI,         NaI,             
	NaI,            NaI,         NaI,              NaI,         NaI,         NaI,             
	NaI,            NaI,         NaI,              NaI,         NaI,         NaI,             
	NaI,            NaI,         NaI,              NaI,         NaI,         NaI,             
	NaI,            NaI,         NaI,              NaI,         NaI,         NaI,             
	NaI,            NaI,         NaI,              NaI,         NaI,         NaI,             
	NaI,            NaI,         NaI,              NaI,         NaI,         NaI,             
	NaI,            NaI,         NaI,              NaI,         NaI,         NaI,             
	NaI,            NaI,         NaI,              NaI,         NaI,         NaI,             
	NaI,            NaI,         NaI,              NaI,         NaI,         NaI,      	
	NaI,            NaI,         NaI,              NaI,         NaI,         NaI,             
	NaI,            NaI,         NaI,              NaI,         NaI,         NaI,             
	NaI,            NaI,         NaI,              NaI,         NaI,         NaI,             
	NaI,            NaI,         NaI,              NaI,         NaI,         NaI,             
	NaI,            NaI,         NaI,              NaI,         NaI,         NaI,             
	NaI,            NaI,         NaI,              NaI,         NaI,         NaI,             
	NaI,            NaI,         NaI,              NaI,         NaI,         NaI,             
	NaI,            NaI,         NaI,              NaI,         NaI,         NaI,             
	NaI,            NaI,         NaI,              NaI,         NaI,         NaI,             
	NaI,            NaI,         NaI,              NaI,         NaI,         NaI,             
	NaI,            NaI,         NaI,              NaI,         NaI,         NaI,             
	NaI,            NaI,         NaI,              NaI,         NaI,         NaI,             
	NaI,            NaI,         NaI,              NaI,         NaI,         NaI,      	
	NaI,            NaI,         NaI,              NaI,         NaI,         NaI,             
	NaI,            NaI,         NaI,              NaI,         NaI,         NaI,             
	NaI,            NaI,         NaI,              NaI,         NaI,         NaI,             
	NaI,            NaI,         NaI,              NaI,         NaI,         NaI,             
	NaI,            NaI,         NaI,              NaI,         NaI,         NaI,             
	NaI,            NaI,         NaI,              NaI,         NaI,         NaI,             
	NaI,            NaI,         NaI,              NaI,         NaI,         NaI,             
	NaI,            NaI,         NaI,              NaI,         NaI,         NaI,             
	NaI,            NaI,         NaI,              NaI,         NaI,         NaI,             
	NaI,            NaI,         NaI,              NaI,         NaI,         NaI,             
	NaI,            NaI,         NaI,              NaI,         NaI,         NaI,             
	NaI,            NaI,         NaI,              NaI,         NaI,         NaI,             
	NaI,            NaI,         NaI,              NaI,         NaI,         NaI,      	
	NaI,            NaI,         NaI,              NaI,         NaI,         NaI,             
	NaI,            NaI,         NaI,              NaI,         NaI,         NaI,             
	NaI,            NaI,         NaI,              NaI,         NaI,         NaI,             
	NaI,            NaI,         NaI,              NaI,         NaI,         NaI,             
	NaI,            NaI,         NaI,              NaI,         NaI,         NaI,             
	NaI,            NaI,         NaI,              NaI,         NaI,         NaI,             
	NaI,            NaI,         NaI,              NaI,         NaI,         NaI,             
	NaI,            NaI,         NaI,              NaI,         NaI,         NaI,             
	NaI,            NaI,         NaI,              NaI,         NaI,         NaI,             
	NaI,            NaI,         NaI,              NaI,         NaI,         NaI,             
	NaI,            NaI,         NaI,              NaI,         NaI,         NaI,             
	NaI,            NaI,         NaI,              NaI,         NaI,         NaI,             
	NaI,            NaI,         NaI,              NaI,         NaI,         NaI,      	
};


RDT::RDT() {
	rdtBuffer = nullptr;
}


RDT::~RDT() {
	if (rdtBuffer != nullptr) {
		delete [] rdtBuffer;
	}

	rdtBuffer = nullptr;
	rdtSize = 0;
}

/**
 * table with step id
 * TODO: improve it
 */
unsigned short RDT::stepTable(const unsigned short& id) {
	switch (id) {
		case 39:
			return 2;
		break;

		case 42:
			return 0;
		break;

		case 45:
			return 4;
		break;

		default:
			std::cout << "step not found: " << id << std::endl;
			return 0;
		break;
	}
}

bool RDT::load(const std::string& dir, const RDT_TYPE_LIST& rdtType) {
	FILE *rdtFile = nullptr;
	rdtFile = fopen(dir.c_str(), "rb");

	if (rdtFile == nullptr) {
		std::cout << "File " << dir << " not found!" << std::endl;
		return false;
	}

	fseek(rdtFile, 0, SEEK_END);
	rdtSize = ftell(rdtFile);
	rewind(rdtFile);

	rdtBuffer = new unsigned char [rdtSize];
	fread(rdtBuffer, 1, rdtSize, rdtFile);

	this->rdtType = rdtType;

	switch (rdtType) {

		/* Resident Evil 1 RDT Files */
		case RDT_TYPE_RE1: {

		    rdtRE1Header = *(RDT_RE1_HEADER_T*)(&rdtBuffer[0]);
		    
		    std::memcpy(&rdtObjectList, (rdtBuffer + sizeof(RDT_RE1_HEADER_T)), 76);

		    /* load cameras */
		    rdtRE1CameraPos.clear();
		    rdtRE1CameraPos.resize(rdtRE1Header.num_cameras);
		    rdtRE1MaskList.clear();
		    for (int i = 0; i < rdtRE1Header.num_cameras; i++) {
		    	rdtRE1CameraPos[i] = *(RDT_RE1_CAMERA_POS_T*)(&rdtBuffer[0x94] + (sizeof(RDT_RE1_CAMERA_POS_T) * i));
		    }

		    /* load switch zone */
			RDT_RE1_CAMERA_SWITCH_T nodeSwitch;
			rdtRE1CameraSwitch.clear();
			unsigned int cont = 0;
			unsigned int checkInt = 0;
			while (true) {

				checkInt = *(unsigned int*)(rdtBuffer+rdtObjectList[0]+(cont*(sizeof(RDT_RE1_CAMERA_SWITCH_T))));
				
				if (checkInt == 0xFFFFFFFF) 
					break;

				nodeSwitch = *(RDT_RE1_CAMERA_SWITCH_T*)(rdtBuffer+rdtObjectList[0]+(cont*(sizeof(RDT_RE1_CAMERA_SWITCH_T))));

				rdtRE1CameraSwitch.push_back(nodeSwitch);
				cont++;
			}



			/* load collision boundaries */
		    rdtRE1CollisionHeader = *(RDT_RE1_SCA_HEADER_T*)(rdtBuffer+rdtObjectList[1]);

		    rdtRE1CollisionArray.clear();
		    RDT_RE1_SCA_OBJ_T *nodeSCA = (RDT_RE1_SCA_OBJ_T*)(rdtBuffer+rdtObjectList[1]+sizeof(RDT_RE1_SCA_HEADER_T));

		    unsigned short fX = 0;
		    unsigned short fZ = 0;


		    for (int i = 0; i < 5; i++) {
		        for (unsigned int j = 0; j < rdtRE1CollisionHeader.counts[i]; j++, nodeSCA++) {
		        	if (nodeSCA->type == 1) {
			            fX = abs(nodeSCA->x1 - nodeSCA->x2);
			            fZ = abs(nodeSCA->z1 - nodeSCA->z2);

			            nodeSCA->x1 = nodeSCA->x1 < nodeSCA->x2 ? nodeSCA->x1 : nodeSCA->x2;
			            nodeSCA->z1 = nodeSCA->z1 < nodeSCA->z2 ? nodeSCA->z1 : nodeSCA->z2;
			            nodeSCA->x2 = fX;
			            nodeSCA->z2 = fZ;
		        	}
			        rdtRE1CollisionArray.push_back(*nodeSCA);
		        }
		    }

		    /* foot step */
		    unsigned short tStep = *(unsigned short*)(rdtBuffer+rdtObjectList[5]);
		    rdtRE1StepList.clear();

		    RDT_RE1_FLR_STEEP node_step;
		    for (auto i = 0; i < tStep; i++) {
		    	node_step = *(RDT_RE1_FLR_STEEP*)(rdtBuffer+rdtObjectList[5] + 2 + (i*sizeof(RDT_RE1_FLR_STEEP)));
		    	node_step.id = stepTable(node_step.id);
		    	rdtRE1StepList.push_back(node_step);
		    }

		    /* Scenario Data */
		    SCD_DATA.clear();
		    SCD_DATA.resize(*(unsigned short*)(rdtBuffer+rdtObjectList[6]));
		    /* copy SCD data */
		    std::memcpy(&SCD_DATA[0], rdtBuffer+2+rdtObjectList[6], SCD_DATA.size());
		    doorList.clear();
		    /* decode scenario data */

		    unsigned int pc = 0;
		    while(pc < SCD_DATA.size()) {
		    	(*re1_opcode_table[SCD_DATA[pc]])(this, &pc);
		    }
		}
		break;

		/* Resident Evil 2 Prototype, aka, 1.5 RDT Files */
		case RDT_TYPE_RE2_PROTO: {

			rdtHeader = *(RDT_HEADER_T*)(&rdtBuffer[0]);

			std::memcpy(rdtObjectList, (rdtBuffer+0x8), 92);

			/*
			 * Load RDT Cameras
			 */
			rdtCameraPos.clear();
			rdtCameraPos.resize(rdtHeader.nCut);

			for (unsigned char i = 0; i < rdtHeader.nCut; i++) {
				rdtCameraPos[i] = *(RDT_CAMERA_POS_T*)(rdtBuffer + rdtObjectList[7] + (i * sizeof(RDT_CAMERA_POS_T)));
			}

			/*
			 * Load Camera switch zone
			 */
			RDT_CAMERA_SWITCH_T node;
			unsigned int checkEnd = 0;
			unsigned int cnt = 0;
			rdtCameraSwitch.clear();
			while (true) {
				/* check end of camera switch zone list */
				checkEnd = *(unsigned int*)(rdtBuffer+rdtObjectList[8]+(cnt * (sizeof(RDT_CAMERA_SWITCH_T))));
				if (checkEnd == 0xFFFFFFFF) break;

				node = *(RDT_CAMERA_SWITCH_T*)(rdtBuffer+rdtObjectList[8] + (cnt * (sizeof(RDT_CAMERA_SWITCH_T))));
				
				rdtCameraSwitch.push_back(node);
				cnt++;
			}

			/*
			 * Load Collision Boundaries
			 */
			rdtCollisionHeader = *(RDT_COLI_HEADER_T*)(rdtBuffer+rdtObjectList[6]);
			rdtCollisionArray.clear();
			rdtCollisionArray.resize(rdtCollisionHeader.amount - 1);

			for(unsigned int i = 0; i < rdtCollisionHeader.amount - 1; i++) {
				rdtCollisionArray[i] = *(RDT_OFFSET6ELT_T*)(rdtBuffer+rdtObjectList[6]+sizeof(RDT_COLI_HEADER_T)+i*sizeof(RDT_OFFSET6ELT_T));
			}

		}

		break;

		/* Resident Evil 2 RDT Files */
		case RDT_TYPE_RE2: {

			rdtHeader = *(RDT_HEADER_T*)(&rdtBuffer[0]);

			std::memcpy(rdtObjectList, (rdtBuffer+0x8), 92);

			/*
			 * Load RDT Cameras
			 */
			rdtCameraPos.resize(rdtHeader.nCut);

			for (unsigned char i = 0; i < rdtHeader.nCut; i++) {
				rdtCameraPos[i] = *(RDT_CAMERA_POS_T*)(rdtBuffer + rdtObjectList[7] + (i * sizeof(RDT_CAMERA_POS_T)));
			}

			/*
			 * Load Camera switch zone
			 */
			RDT_CAMERA_SWITCH_T node;
			unsigned int checkEnd = 0;
			unsigned int cnt = 0;
			while (true) {
				/* check end of camera switch zone list */
				checkEnd = *(unsigned int*)(rdtBuffer+rdtObjectList[8]+(cnt * (sizeof(RDT_CAMERA_SWITCH_T))));
				if (checkEnd == 0xFFFFFFFF) break;

				node = *(RDT_CAMERA_SWITCH_T*)(rdtBuffer+rdtObjectList[8] + (cnt * (sizeof(RDT_CAMERA_SWITCH_T))));
				
				rdtCameraSwitch.push_back(node);
				cnt++;
			}

			/*
			 * Load Collision Boundaries
			 */
			rdtCollisionHeader = *(RDT_COLI_HEADER_T*)(rdtBuffer+rdtObjectList[6]);

			rdtCollisionArray.resize(rdtCollisionHeader.amount - 1);

			for(unsigned int i = 0; i < rdtCollisionHeader.amount - 1; i++) {
				rdtCollisionArray[i] = *(RDT_OFFSET6ELT_T*)(rdtBuffer+rdtObjectList[6]+sizeof(RDT_COLI_HEADER_T)+i*sizeof(RDT_OFFSET6ELT_T));
			}



		}
		break;

		/* Resident Evil 3 RDT Files */
		case RDT_TYPE_RE3:

		break;

		default:
			std::cout << "RDT type not found !" << std::endl;
			return false;
		break;
	}

	delete [] rdtBuffer;
	rdtBuffer = nullptr;
	return true;
}


