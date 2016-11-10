#ifndef _ROOM_H_
#define _ROOM_H_

#include "rdt.h"
#include "player.h"
#include "../../physics.h"


extern bool loadRoom(render *m_Render, player* m_Player, std::vector<std::unique_ptr<nTexture>> *pRDT_tex, RDT *pRDT, const RDT_TYPE_LIST& rdtType);
extern void checkRoomCollision(RDT *pRDT, player *m_Player, const float& speed);
extern void checkSwitchZone(RDT *pRDT, player *m_Player);
extern void checkDoor(render *m_Render, player* m_Player, std::vector<std::unique_ptr<nTexture>> *pRDT_tex, RDT *pRDT, const RDT_TYPE_LIST& rdtType);
extern unsigned int checkStepZone(player *m_Player, RDT *pRDT);
#endif