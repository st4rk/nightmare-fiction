#include "zombie.h"

void (*ai_zombie_custom[])(entity *e, player *p, RDT *r, nf3d *m) = {
	ai_zombie_custom_idle, ai_zombie_custom_walk, ai_zombie_custom_hit,
	ai_zombie_custom_death
};

void ai_zombie_custom_death(entity *e, player *p, RDT *r, nf3d *m) {
	if (m->getAnimSection() != EMD_SECTION_4) m->setAnimSection(EMD_SECTION_4);

	if (m->getSec4Animation() != STAND_SEC4_ANIM_USHOOTING) {
		/** such macgyver ew */
		e->setXYZ(glm::vec3(e->getXYZ().x, 2000 + m->animFrame.yOffset, e->getXYZ().z));
		if (m->getSec4Animation() != STAND_SEC4_ANIM_AIM) {
			m->setSec4Animation(STAND_SEC4_ANIM_AIM);
			m->isInterpolation = true;
			m->oldFrame = m->animFrame;
			m->interStep = 1.0f/8;
			m->interTotal = 0.0f;
		}

		if (m->getAnimCnt() >= 54) m->setSec4Animation(STAND_SEC4_ANIM_USHOOTING);
	}
}

void ai_zombie_custom_hit(entity *e, player *p, RDT *r, nf3d *m) {
	if (m->getAnimSection() != EMD_SECTION_4) m->setAnimSection(EMD_SECTION_4);
	
	if (m->getSec4Animation() != STAND_SEC4_ANIM_DUMMY_1) {
		m->isInterpolation = true;
		m->oldFrame = m->animFrame;
		m->interStep = 1.0f/8;
		m->interTotal = 0.0f;
 		m->setSec4Animation(STAND_SEC4_ANIM_DUMMY_1);
	}


	if (m->getAnimCnt() >= 59) {
		e->setAction(ENTITY_ACTION_WALK);
		m->isInterpolation = true;
		m->oldFrame = m->animFrame;
		m->interStep = 1.0f/8;
		m->interTotal = 0.0f;
		m->setAnimSection(EMD_SECTION_2);
		m->setSec2Animation(STAND_SEC2_ANIM_HIT);
		e->aFactor = 0.0f;

		p->entityTmr.enable = false;
		p->entityTmr.tick = glfwGetTime() + 1.0f;
		p->entityTmr.tmr  = 1.2f;
	}

}

void ai_zombie_custom_idle(entity *e, player *p, RDT *r, nf3d *m) {
	/** check distance between player and entity */

	if (e->getStatus() == 1) {
		e->setXYZ(glm::vec3(e->getXYZ().x, 2000 + m->animFrame.yOffset, e->getXYZ().z));
	}

	if (glm::distance(e->getXYZ(), p->getXYZ()) <= 3520.0f) {

		if (m->getSec4Animation() == STAND_SEC4_ANIM_AMMO) {
			if (m->getAnimCnt() >= 29) {
				m->isInterpolation = true;
				m->oldFrame = m->animFrame;
				m->interStep = 1.0f/8;
				m->interTotal = 0.0f;
				goto _walk;
			}
		} else {
_walk:
		if (m->getAnimSection() == EMD_SECTION_4) {
			m->setSec4Animation(STAND_SEC4_ANIM_DUMMY_2);
		} else {
			m->setSec2Animation(STAND_SEC2_ANIM_HIT);
		}
			e->setAction(ENTITY_ACTION_WALK);
			e->aFactor = 0.0f;
		}
	}
}

void ai_zombie_custom_walk(entity *e, player *p, RDT *r, nf3d *m) {


	if (e->getStatus() == 1) {
		e->setXYZ(glm::vec3(e->getXYZ().x, 2000 + m->animFrame.yOffset, e->getXYZ().z));
		if (m->getAnimCnt() >= 97) {
			m->isInterpolation = true;
			m->oldFrame = m->animFrame;
			m->interStep = 1.0f/8;
			m->interTotal = 0.0f;
			m->setAnimSection(EMD_SECTION_2);
			m->setSec2Animation(STAND_SEC2_ANIM_HIT);
			e->setStatus(0);
		}
	} else {
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
			checkRoomCollision(r, e, 10.0f);
			e->entityTmr.enable = false;
			e->entityTmr.tick = glfwGetTime() + 2.0f;
			e->entityTmr.tmr  = 1.2f;
		} else {
			if ((p->getAction() != ENTITY_ACTION_HIT) && (p->getAction() != ENTITY_ACTION_DEATH)) {
				p->setAction(ENTITY_ACTION_HIT);
				if (m->getAnimSection() != EMD_SECTION_4) m->setAnimSection(EMD_SECTION_4);		
				if (m->getSec4Animation() != STAND_SEC4_ANIM_RUNNING) m->setSec4Animation(STAND_SEC4_ANIM_RUNNING);

				e->entityTmr.run();

				if (e->entityTmr.enable) {
					if (m->getSec4Animation() != STAND_SEC4_ANIM_AMMO) m->setSec4Animation(STAND_SEC4_ANIM_AMMO);
					if (glm::distance(e->getXYZ(), p->getXYZ()) < 1000.0f) {
						glm::vec3 dir = glm::vec3(cos(glm::radians(e->getAngle())), 
							                      0.0f,
							                     -sin(glm::radians(e->getAngle())));
						dir = dir * 1200.0f;		
						e->setXYZ(e->getXYZ() - dir);
						e->setAction(ENTITY_ACTION_IDLE);
						m->setAnimSection(EMD_SECTION_2);
						m->setSec2Animation(STAND_SEC2_ANIM_DEATH);

					} 

					if ((int)(p->getHP() - 1) > 0) {
						p->setHP(p->getHP() - 1);
					} else {
						p->setHP(0);
					}

					e->entityTmr.enable = false;
					e->entityTmr.tick = glfwGetTime() + 2.0f;
					e->entityTmr.tmr  = 1.2f;
				}
			}
		}
	}
}	


