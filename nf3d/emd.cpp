#include "emd.h"

EMD::EMD(const std::string& dir) {
    FILE *emdFile = nullptr;

    emdFile = fopen(dir.c_str(), "rb");

    // verify if it open the file
    if (emdFile == nullptr) {
        std::cout << "EMD file couldn't be loaded - " << dir << std::endl;
        return;
    }

    // get file size
    fseek(emdFile, 0, SEEK_END);
    emdSize = ftell(emdFile);
    rewind(emdFile);

    emdBufferData = new unsigned char [emdSize];

    fread(emdBufferData, emdSize, 1, emdFile);


    // load emd file tree
    emdHeader = *(EMD_HEADER_DIRECTORY*)(&emdBufferData[0]);

    // load each dir offset
    for (unsigned int i = 0; i < (emdHeader.dirCount); i++) {
        emdFileSection.push_back(*(unsigned int*)(emdBufferData+emdHeader.dirOffset+(i*4)));
        printf("Section %d Offset: 0x%X\n", i, emdFileSection[i]);
    }

    /*
     * section 1 - animation steps
     */
 
    sizeSec1Header = *(unsigned short*)((emdBufferData+emdFileSection[1] + 2));

    unsigned short sizeSec1_f = (sizeSec1Header / 4);

    for (unsigned short i = 0; i < sizeSec1_f; i++) {
        emdSec1Header.push_back(*(EMD_SECTION_1_HEADER*)(emdBufferData+emdFileSection[1]+(i*sizeof(EMD_SECTION_1_HEADER))));
    }

    // TODO: Remove this macgyver and do the things in a proper way
    for (unsigned short i = 0; i < sizeSec1_f; i++) {
        for(unsigned short j = 0; j < emdSec1Header[i].dataCount; j++) {
            memcpy(&emdSec1AnimSkelT[i][j], (emdBufferData+emdFileSection[1]+emdSec1Header[i].dataOffset+(j*sizeof(unsigned int))), sizeof(unsigned int));
        }
    }

    /*
     * Section 3 - animation steps
     */
    sizeSec3Header = *(unsigned short*)(emdBufferData+emdFileSection[3] + 2);

    unsigned short sizeSec3_f = (sizeSec3Header / 4);

    for (unsigned short i = 0; i < sizeSec3_f; i++) {
        emdSec3Header.push_back(*(EMD_SECTION_1_HEADER*)(emdBufferData+emdFileSection[3]+(i*sizeof(EMD_SECTION_1_HEADER))));
    }

    for (unsigned short i = 0; i < sizeSec3_f; i++) {
        for(unsigned short j = 0; j < emdSec3Header[i].dataCount; j++) {
            memcpy(&emdSec3AnimSkelT[i][j], (emdBufferData+emdFileSection[3]+emdSec3Header[i].dataOffset+(j*sizeof(unsigned int))), sizeof(unsigned int));
         }
    }

    /*
     *  Section 2 - skeleton
     */
    emdSec2Header = *(EMD_SECTION_2_HEADER*)(emdBufferData+emdFileSection[2]);

    for (unsigned int i = 0; i < emdSec2Header.count; i++) {
        emdSec2RelPos.push_back(*(EMD_SEC2_RELPOS_T*)(emdBufferData+emdFileSection[2]+8+(i*sizeof(EMD_SEC2_RELPOS_T))));
    }

    int relOffset = (emdFileSection[2]+emdSec2Header.relposOffset);

    for (unsigned int i = 0; i < emdSec2Header.count; i++ ) {
        emdSec2Armature.push_back(*(EMD_SEC2_ARMATURE_T*)((emdBufferData+relOffset + (i*sizeof(EMD_SEC2_ARMATURE_T)))));
    }

    emdSec2Mesh.resize(emdSec2Header.count);

    for (unsigned int i = 0; i < emdSec2Header.count; i++) {
        emdSec2Mesh[i].resize(emdSec2Armature[i].meshCount);
    }

    for (unsigned int i = 0; i < emdSec2Header.count; i++ ) {
        for (unsigned int a = 0; a < emdSec2Armature[i].meshCount; a++) { 
            emdSec2Mesh[i][a] = *(unsigned char*)(emdBufferData + relOffset + emdSec2Armature[i].offSet + a);
        }
    }
     
    /*
     * Section 4 - Skeleton 2
     */
    emdSec4Header = *(EMD_SECTION_2_HEADER*)((emdBufferData+emdFileSection[4]));
    
    /*
     * Section 7 - Mesh
     */
    emdSec7Header = *(EMD_SECTION_7_HEADER*)(emdBufferData+emdFileSection[7]);

    int totalObj = (emdSec7Header.objCount / 2);
    emdTotalObj = totalObj;

    unsigned int s7ModelOffset = (emdFileSection[7]+12);

    totalAnim = (sizeSec1Header/4);

    emdSec2AnimInfo.resize(totalAnim);

    unsigned int aux = 0;
    for (unsigned short i = 0; i < totalAnim; i++) {
        for(unsigned short j = 0; j < emdSec1Header[i].dataCount; j++) {
            aux = 0;
            EMD_SEC2_DATA_T emdSec2Node;
            emdSec2Node.xOffset = *(short*)(emdBufferData+emdFileSection[2]+emdSec2Header.lenght+((emdSec1AnimSkelT[i][j]& 0x0FFF) * emdSec2Header.size));
            emdSec2Node.yOffset = *(short*)(emdBufferData+emdFileSection[2]+emdSec2Header.lenght+2+((emdSec1AnimSkelT[i][j]& 0x0FFF) * emdSec2Header.size));
            emdSec2Node.zOffset = *(short*)(emdBufferData+emdFileSection[2]+emdSec2Header.lenght+4+((emdSec1AnimSkelT[i][j]& 0x0FFF) * emdSec2Header.size));
            emdSec2Node.xSpeed = *(short*)(emdBufferData+emdFileSection[2]+emdSec2Header.lenght+6+((emdSec1AnimSkelT[i][j]& 0x0FFF) * emdSec2Header.size));
            emdSec2Node.ySpeed = *(short*)(emdBufferData+emdFileSection[2]+emdSec2Header.lenght+8+((emdSec1AnimSkelT[i][j]& 0x0FFF) * emdSec2Header.size));
            emdSec2Node.zSpeed = *(short*)(emdBufferData+emdFileSection[2]+emdSec2Header.lenght+10+((emdSec1AnimSkelT[i][j]& 0x0FFF) * emdSec2Header.size));



            for (unsigned short a = 0; a < (emdSec2Header.size-12); a++) {
                emdSec2Node.angles.push_back(*(unsigned char*)(emdBufferData+emdFileSection[2]+emdSec2Header.lenght+12+a+((emdSec1AnimSkelT[i][j] & 0x0FFF) * emdSec2Header.size)));
            }
            
            EMD_SEC2_VECTOR vec;
            /*
             * Convert to float
             */

            for (unsigned short i = 0; i < emdTotalObj; i++) {
                if ((i % 2) == 0) {
                    vec.x = (emdSec2Node.angles[aux] | ((emdSec2Node.angles[aux+1] & 0b00001111) << 8));
                    vec.x = ((vec.x / 4096) * 360);
                    vec.y = ((emdSec2Node.angles[aux+1] & 0b11110000) >> 4) | (emdSec2Node.angles[aux+2] << 4);
                    vec.y = ((vec.y / 4096) * 360);                 
                    vec.z = (emdSec2Node.angles[aux+3] | ((emdSec2Node.angles[aux+4] & 0b00001111) << 8));
                    vec.z = ((vec.z / 4096) * 360);
                    aux += 4;
                } else {
                    vec.x = ((emdSec2Node.angles[aux] & 0b11110000) >> 4) | (emdSec2Node.angles[aux+1] << 4);
                    vec.x = ((vec.x / 4096) * 360);      
                    vec.y = (emdSec2Node.angles[aux+2] | ((emdSec2Node.angles[aux+3] & 0b00001111) << 8));
                    vec.y = ((vec.y / 4096) * 360);
                    vec.z = ((emdSec2Node.angles[aux+3] & 0b11110000) >> 4) | (emdSec2Node.angles[aux+4] << 4);
                    vec.z = ((vec.z / 4096) * 360);
                    aux += 5;                    
                }

            emdSec2Node.vector.push_back(vec);
           }

           emdSec2Data.push_back(emdSec2Node);
        }

        emdSec2AnimInfo[i].animCount = emdSec1Header[i].dataCount;

    }
    
    int animStart = 0;
    for (unsigned int i = 0; i < totalAnim; i++) {
        emdSec2AnimInfo[i].animStart = animStart;
        animStart += (emdSec2AnimInfo[i].animCount);
    }



    totalAnim = (sizeSec3Header/4);
    emdSec4AnimInfo.resize(totalAnim);

    for (unsigned short i = 0; i < totalAnim; i++) {
        for(unsigned short j = 0; j < emdSec3Header[i].dataCount; j++) {
            aux = 0;
            EMD_SEC2_DATA_T emdSec4Node;
            emdSec4Node.xOffset = *(short*)(emdBufferData+emdFileSection[4]+emdSec4Header.lenght+((emdSec3AnimSkelT[i][j]& 0x0FFF) * emdSec4Header.size));
            emdSec4Node.yOffset = *(short*)(emdBufferData+emdFileSection[4]+emdSec4Header.lenght+2+((emdSec3AnimSkelT[i][j]& 0x0FFF) * emdSec4Header.size));
            emdSec4Node.zOffset = *(short*)(emdBufferData+emdFileSection[4]+emdSec4Header.lenght+4+((emdSec3AnimSkelT[i][j]& 0x0FFF) * emdSec4Header.size));
            emdSec4Node.xSpeed = *(short*)(emdBufferData+emdFileSection[4]+emdSec4Header.lenght+6+((emdSec3AnimSkelT[i][j]& 0x0FFF) * emdSec4Header.size));
            emdSec4Node.ySpeed = *(short*)(emdBufferData+emdFileSection[4]+emdSec4Header.lenght+8+((emdSec3AnimSkelT[i][j]& 0x0FFF) * emdSec4Header.size));
            emdSec4Node.zSpeed = *(short*)(emdBufferData+emdFileSection[4]+emdSec4Header.lenght+10+((emdSec3AnimSkelT[i][j]& 0x0FFF) * emdSec4Header.size));

            for (unsigned short a = 0; a < (emdSec4Header.size-12); a++) {
                emdSec4Node.angles.push_back(*(unsigned char*)(emdBufferData+emdFileSection[4]+emdSec4Header.lenght+12+a+((emdSec3AnimSkelT[i][j] & 0x0FFF) * emdSec4Header.size)));
            }
            
            /* Temos 12 bits por coordenada temos que fazer agora a transformação do
            angles para as nossas coordenadas */
            EMD_SEC2_VECTOR vec;
            for (unsigned short i = 0; i < emdTotalObj; i++) {
                if ((i % 2) == 0) {
                    vec.x = (emdSec4Node.angles[aux] | ((emdSec4Node.angles[aux+1] & 0b00001111) << 8));
                    vec.x = ((vec.x / 4096) * 360);
                    vec.y = ((emdSec4Node.angles[aux+1] & 0b11110000) >> 4) | (emdSec4Node.angles[aux+2] << 4);
                    vec.y = ((vec.y / 4096) * 360);                 
                    vec.z = (emdSec4Node.angles[aux+3] | ((emdSec4Node.angles[aux+4] & 0b00001111) << 8));
                    vec.z = ((vec.z / 4096) * 360);
                    aux += 4;
                } else {
                    vec.x = ((emdSec4Node.angles[aux] & 0b11110000) >> 4) | (emdSec4Node.angles[aux+1] << 4);
                    vec.x = ((vec.x / 4096) * 360);      
                    vec.y = (emdSec4Node.angles[aux+2] | ((emdSec4Node.angles[aux+3] & 0b00001111) << 8));
                    vec.y = ((vec.y / 4096) * 360);
                    vec.z = ((emdSec4Node.angles[aux+3] & 0b11110000) >> 4) | (emdSec4Node.angles[aux+4] << 4);
                    vec.z = ((vec.z / 4096) * 360);
                    aux += 5;                    
                }
             emdSec4Node.vector.push_back(vec);
           }

           emdSec4Data.push_back(emdSec4Node);
        }

        emdSec4AnimInfo[i].animCount = emdSec3Header[i].dataCount;

    }
    
    animStart = 0;
    for (unsigned int i = 0; i < totalAnim; i++) {
        emdSec4AnimInfo[i].animStart = animStart;
        animStart += (emdSec4AnimInfo[i].animCount);
    }

    unsigned int index = 0; 
    int offset = s7ModelOffset;
    emdObjectBuffer.resize(emdTotalObj);

    for (index = 0; index < emdTotalObj; index++) {
        memcpy(&emdObjectBuffer[index].triangles, (emdBufferData + offset), sizeof(EMD_MODEL_TRIANGLES_T));
        offset += 28;
        memcpy(&emdObjectBuffer[index].quads, (emdBufferData + offset), sizeof(EMD_MODEL_QUADS_T));
        offset += 28;
    }

    emdVertex.resize(emdTotalObj);
    emdquadVertex.resize(emdTotalObj);
    emdNormal.resize(emdTotalObj);
    emdTriangle.resize(emdTotalObj);
    emdQuad.resize(emdTotalObj);
    emdquadNormal.resize(emdTotalObj);
    emdQuadTexture.resize(emdTotalObj);
    emdTritexture.resize(emdTotalObj);


    for (unsigned int i = 0; i < emdTotalObj; i++) {
        emdVertex[i].resize(emdObjectBuffer[i].triangles.vertexCount);
        emdquadVertex[i].resize(emdObjectBuffer[i].quads.vertexCount);
        emdNormal[i].resize(emdObjectBuffer[i].triangles.normalCount);
        emdquadNormal[i].resize(emdObjectBuffer[i].quads.normalCount);
        emdTriangle[i].resize(emdObjectBuffer[i].triangles.triCount);
        emdQuad[i].resize(emdObjectBuffer[i].quads.quadCount);
        emdQuadTexture[i].resize(emdObjectBuffer[i].quads.quadCount);
        emdTritexture[i].resize(emdObjectBuffer[i].triangles.triCount);
    }
    
    for (unsigned int x = 0; x < emdTotalObj; x++) {
        for (unsigned int y = 0; y < emdObjectBuffer[x].triangles.vertexCount; y++) {
            emdVertex[x][y] = *(EMD_VERTEX_T*)(emdBufferData + (s7ModelOffset + emdObjectBuffer[x].triangles.vertexOffset+(y*8)));
        }

        for (unsigned int y = 0; y < emdObjectBuffer[x].quads.vertexCount; y++) {
            emdquadVertex[x][y] = *(EMD_VERTEX_T*)(emdBufferData + (s7ModelOffset + emdObjectBuffer[x].quads.vertexOffset+(y*8)));
        }
        
        for (unsigned int y = 0; y < emdObjectBuffer[x].triangles.normalCount; y++) {
            emdNormal[x][y] = *(EMD_NORMAL_T*)(emdBufferData + (s7ModelOffset + emdObjectBuffer[x].triangles.normalOffset+(y*8)));
        }
 
        for (unsigned int y = 0; y < emdObjectBuffer[x].quads.normalCount; y++) {
            emdquadNormal[x][y] = *(EMD_NORMAL_T*)(emdBufferData + (s7ModelOffset + emdObjectBuffer[x].quads.normalOffset+(y*8)));
        }

        for (unsigned int y = 0; y < emdObjectBuffer[x].triangles.triCount; y++) {
            emdTriangle[x][y] = *(EMD_TRIANGLE_T*)(emdBufferData + (s7ModelOffset + emdObjectBuffer[x].triangles.triOffset+(y*sizeof(EMD_TRIANGLE_T))));
            emdTritexture[x][y] = *(EMD_TRITEXTURE_T*)(emdBufferData + (s7ModelOffset + emdObjectBuffer[x].triangles.triTextureOffset+(y*sizeof(EMD_TRITEXTURE_T))));
        }

        for (unsigned int y = 0; y < emdObjectBuffer[x].quads.quadCount; y++) {
            emdQuad[x][y] = *(EMD_QUAD_T*)(emdBufferData + (s7ModelOffset + emdObjectBuffer[x].quads.quadOffset+(y*sizeof(EMD_QUAD_T))));
            emdQuadTexture[x][y] = *(EMD_QUADTEXTURE_T*)(emdBufferData + (s7ModelOffset + emdObjectBuffer[x].quads.quadTextureOffset+(y*sizeof(EMD_QUADTEXTURE_T))));
        }
    } 
    
    fclose(emdFile);
}


EMD::~EMD() {
    if (emdBufferData != nullptr) {
        delete [] emdBufferData;
        emdBufferData = nullptr;
    }
}

