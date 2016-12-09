#include "tyrant.h"

void (*ai_tyrant_custom[])(entity *e, player *p, RDT *r, nf3d *m) = {
	ai_tyrant_custom_idle, ai_tyrant_custom_walk, ai_tyrant_custom_hit,
	ai_tyrant_custom_death
};

void ai_tyrant_custom_hit(entity *e, player *p, RDT *r, nf3d *m) {
	if (m->getSec2Animation() != STAND_SEC2_ANIM_HIT_2) m->setSec2Animation(STAND_SEC2_ANIM_HIT_2);

	if (m->getAnimCnt() >= 39) {
		e->setAction(ENTITY_ACTION_WALK);
		m->setSec2Animation(STAND_SEC2_ANIM_SBACKWARD);
		e->aFactor = 0.0f;
	}
}

void ai_tyrant_custom_idle(entity *e, player *p, RDT *r, nf3d *m) {
	e->setXYZ(glm::vec3(e->getXYZ().x, 2010 + m->animFrame.yOffset, e->getXYZ().z));

	if (m->getAnimCnt() >= 254) {
		e->setAction(ENTITY_ACTION_WALK);
		m->setSec2Animation(STAND_SEC2_ANIM_SBACKWARD);
		e->aFactor = 0.0f;
	}
}

void ai_tyrant_custom_walk(entity *e, player *p, RDT *r, nf3d *m) {
	float fX = p->getXYZ().x - e->getXYZ().x;
	float fZ = p->getXYZ().z - e->getXYZ().z;

	float a = (atan2(fX, fZ) * 180 / M_PI) - 90.0f;
	/** angle with player */
	if (e->aFactor < 1.0f) {
		e->setAngle(physics::interpolation::lerpAngle(e->getAngle(), a, e->aFactor));
		e->aFactor += 0.001f;
	} else {
		e->setAngle(a);
	}

	/** check the distance between player and entity */
	if (glm::distance(e->getXYZ(), p->getXYZ()) > 1000.0f) {
		if (m->getSec2Animation() != STAND_SEC2_ANIM_SBACKWARD) m->setSec2Animation(STAND_SEC2_ANIM_SBACKWARD);
		checkRoomCollision(r, e, 40.0f);
		e->entityTmr.enable = false;
		e->entityTmr.tick = glfwGetTime() + 2.0f;
		e->entityTmr.tmr  = 1.2f;
	} else {

		if (p->getAction() != ENTITY_ACTION_DEATH) {
			if (m->getSec2Animation() != STAND_SEC2_ANIM_DEATH) m->setSec2Animation(STAND_SEC2_ANIM_DEATH);
			
			if (m->getAnimCnt() == 15) {
				p->setAction(ENTITY_ACTION_HIT);
				if ((int)(p->getHP() - 4) > 0) {
					p->setHP(p->getHP() - 4);
				} else {
					p->setHP(0);
				}
			}

			if ((m->getAnimCnt() >= 33) && (m->getSec2Animation() == STAND_SEC2_ANIM_DEATH)) {
				if (m->getSec2Animation() != STAND_SEC2_ANIM_SBACKWARD) m->setSec2Animation(STAND_SEC2_ANIM_SBACKWARD);
				e->entityTmr.enable = true;
				e->entityTmr.tick = glfwGetTime() + 10.0f;
				e->entityTmr.tmr  = 1.2f;
			} else {
				e->entityTmr.run();

				if (e->entityTmr.enable) {
					m->setSec2Animation(STAND_SEC2_ANIM_DEATH);
				}
			}
		}
	}

}

void ai_tyrant_custom_death(entity *e, player *p, RDT *r, nf3d *m) {

}