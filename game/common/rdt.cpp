#include "rdt.h"

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

		    for (int i = 0; i < rdtRE1Header.num_cameras; i++) {
		    	rdtRE1CameraPos[i] = *(RDT_RE1_CAMERA_POS_T*)(&rdtBuffer[0x94] + (sizeof(RDT_RE1_CAMERA_POS_T) * i));
		    }

		    /* load switch zone */
			RDT_RE1_CAMERA_SWITCH_T nodeSwitch;
			rdtRE1CameraSwitch.clear();
			unsigned int cont = 0;
			while (true) {
				unsigned int checkInt = 0;

				checkInt = *(unsigned int*)(rdtBuffer+rdtObjectList[0]+(cont*(sizeof(RDT_RE1_CAMERA_SWITCH_T))));
				
				if (checkInt == 0xFFFFFFFF) 
					break;

				memcpy(&nodeSwitch, (rdtBuffer+rdtObjectList[0]+(cont*(sizeof(RDT_RE1_CAMERA_SWITCH_T)))), sizeof(RDT_RE1_CAMERA_SWITCH_T));

				rdtRE1CameraSwitch.push_back(nodeSwitch);
				cont++;
			}

			/* load collision boundaries */
		    rdtRE1CollisionHeader = *(RDT_RE1_SCA_HEADER_T*)(rdtBuffer+rdtObjectList[1]);

		    rdtRE1CollisionArray.clear();
		    RDT_RE1_SCA_OBJ_T *nodeSCA = (RDT_RE1_SCA_OBJ_T*)(rdtBuffer+rdtObjectList[1]+sizeof(RDT_RE1_SCA_HEADER_T));

		    unsigned short fX = 0;
		    unsigned short fZ = 0;

		    for (int i = 0; i < 4; i++) {
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
				
				/* 
				     TODO: check issues with switch zone
				std::cout << "X1: " << node.x1 << " Z1: " << node.z1 << std::endl;
				std::cout << "X2: " << node.x2 << " Z2: " << node.z2 << std::endl;
				std::cout << "X3: " << node.x3 << " Z3: " << node.z3 << std::endl;
				std::cout << "X4: " << node.x4 << " Z4: " << node.z4 << std::endl;
				*/
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