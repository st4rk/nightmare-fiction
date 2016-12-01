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
			e->setAction(ENTITY_ACTION_WALK);
			m->setAnimSection(EMD_SECTION_2);
			m->setSec2Animation(STAND_SEC2_ANIM_HIT);
			e->aFactor = 0.0f;
		}
	}
}

void ai_zombie_custom_walk(entity *e, player *p, RDT *r, nf3d *m) {
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
		p->entityTmr.enable = false;
		p->entityTmr.tick = glfwGetTime() + 2.0f;
		p->entityTmr.tmr  = 1.2f;
	} else {
		p->setAction(ENTITY_ACTION_HIT);


		p->entityTmr.run();


		if (!p->entityTmr.enable) {
			if (m->getAnimSection() != EMD_SECTION_4) m->setAnimSection(EMD_SECTION_4);		
			if (m->getSec4Animation() != STAND_SEC4_ANIM_RUNNING) m->setSec4Animation(STAND_SEC4_ANIM_RUNNING);
		} else {
			if (m->getSec4Animation() != STAND_SEC4_ANIM_AMMO) m->setSec4Animation(STAND_SEC4_ANIM_AMMO);
			if (glm::distance(e->getXYZ(), p->getXYZ()) < 1000.0f) {
				glm::vec3 dir = glm::vec3(cos(glm::radians(e->getAngle())), 
					                      0.0f,
					                     -sin(glm::radians(e->getAngle())));
				dir = dir * 1200.0f;		
				e->setXYZ(e->getXYZ() - dir);
				e->setAction(ENTITY_ACTION_IDLE);
			} 
		}
	}
}	


