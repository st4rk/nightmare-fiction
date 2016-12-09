#ifndef _TYRANT_H_
#define _TYRANT_H_

#include "../entity.h"
#include "../player.h"
#include "../room.h"
#include "../rdt.h"

#include "../../../physics.h"
#include "../../../nf3d/nf3d.h"

extern void ai_tyrant_custom_hit(entity *e, player *p, RDT *r, nf3d *m);
extern void ai_tyrant_custom_idle(entity *e, player *p, RDT *r, nf3d *m);
extern void ai_tyrant_custom_walk(entity *e, player *p, RDT *r, nf3d *m);
extern void ai_tyrant_custom_death(entity *e, player *p, RDT *r, nf3d *m);
extern void (*ai_tyrant_custom[])(entity *e, player *p, RDT *r, nf3d *m);


#endif