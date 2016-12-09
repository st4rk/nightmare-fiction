#include "room.h"



/**
 * shoot
 * verify and update entities after a shoot
 * TODO: Better code
 */
void shoot(player *p, std::vector<entity>& e) {
	int id = -1;
	float dist = 1100.0f;
	printf("Ohay!\n");

	glm::vec3 dir = glm::vec3(cos(glm::radians(p->getAngle())), 
		                      0.0f,
		                     -sin(glm::radians(p->getAngle())));

	for (unsigned int i = 0; i < e.size(); i++) {
		if (e[i].getAction() != ENTITY_ACTION_DEATH) {
			float D = glm::distance(p->getXYZ(), e[i].getXYZ());
			
			glm::vec3 fdir = p->getXYZ() + dir * D;

			D = glm::distance(e[i].getXYZ(), fdir);

			if (D < 1000.0f) {
				if (D < dist) {
					D = dist;
					id = i;
				}
			}
		}
	}

	if (id >= 0) {
		printf("ID: %d\n", id);
		if (e[id].getHP() > 0) {

			unsigned int dmg = 0;

			switch (p->getWeapon()) {
				case 0:
					dmg = 1;
				break;

				case 1:
					dmg = 3;
				break;

				case 2:
					dmg = 2;
				break;
			}
			
			

			if ((int)(e[id].getHP() - dmg) <= 0) {
				e[id].setAction(ENTITY_ACTION_DEATH);
			} else {
				e[id].setAction(ENTITY_ACTION_HIT);
				e[id].setHP(e[id].getHP() - dmg);
			}

			printf("EHP: %d\n", e[id].getHP());
		}  
	}
}

/*
 * loadRoom
 * will load room information
 * returns nothing
 */
bool loadRoom(render *m_Render, player* m_Player, std::vector<std::unique_ptr<nTexture>> *pRDT_tex, RDT *pRDT, const RDT_TYPE_LIST& rdtType) {
	/* Load RDT File */
	char fileName[0xFF];
	memset (fileName, 0, 0xFF);

	/* TODO: improve it, remove the switch and use the type with sprintf */
	switch (rdtType) {
		case RDT_TYPE_RE1:
			sprintf(fileName, "resource/stages/RE1/STAGE%X/RDT/ROOM%d%02X0.RDT", m_Player->getStage(), m_Player->getStage(), m_Player->getMap());
		break;

		case RDT_TYPE_RE2_PROTO:
			sprintf(fileName, "resource/stages/BH15/RDT/ROOM%d%02X0.RDT", m_Player->getStage(), m_Player->getMap());
		break;

		case RDT_TYPE_RE2:
			return false;
		break;

		case RDT_TYPE_RE3:
			return false;
		break;

		default:
			return false;
		break;
	}

	pRDT->load(fileName, rdtType);

	/* Load Backgrounds */
	pRDT_tex->clear();
	std::unique_ptr<nTexture> tex;

	/**
	 * TODO:
	 * Create a single format to handle the scenarios informatios
	 */
	
	unsigned int nBackground = 0;

	switch (rdtType) {
		case RDT_TYPE_RE1:
			nBackground = pRDT->rdtRE1Header.num_cameras;
		break;

		case RDT_TYPE_RE2:
		case RDT_TYPE_RE2_PROTO:
		case RDT_TYPE_RE3:
			nBackground = pRDT->rdtHeader.nCut;
		break;	
	}

	pRDT_tex->clear();
	for (unsigned int i = 0; i < nBackground; i++) {
		memset (fileName, 0, 0xFF);

		/* TODO: improve it, remove the switch and use the type with sprintf */
		switch (rdtType) {
			case RDT_TYPE_RE1:
				sprintf(fileName, "resource/stages/RE1/STAGE%X/PAK/ROOM%X%02X/%d.PNG", m_Player->getStage(), m_Player->getStage(), m_Player->getMap(), i);
			break;

			case RDT_TYPE_RE2_PROTO:
				sprintf(fileName, "resource/stages/BH15/PAK/ROOM%d%02X/%d.PNG", m_Player->getStage(), m_Player->getMap(), i);
			break;

			case RDT_TYPE_RE2:
				return false;
			break;

			case RDT_TYPE_RE3:
				return false;
			break;

			default:
				return false;
			break;
		}


		tex.reset(m_Render->loadTexture(fileName));

		pRDT_tex->push_back(std::move(tex));	
	}

	return true;
}

/**
 * checkSwitchZone
 * 
 * 
 */
void checkSwitchZone(RDT *pRDT, player *m_Player) {
	switch (pRDT->rdtType) {
		case RDT_TYPE_RE1:
			for (unsigned int i = 0; i < pRDT->rdtRE1CameraSwitch.size(); i++) {
				if (pRDT->rdtRE1CameraSwitch[i].from == m_Player->getCam() && pRDT->rdtRE1CameraSwitch[i].to == 9) {
					i++;
					for (unsigned int n = i; n < pRDT->rdtRE1CameraSwitch.size(); n++) {
						if (physics::collision::triangle(m_Player->getXYZ(),
												 glm::vec3(pRDT->rdtRE1CameraSwitch[n].x1, 0, pRDT->rdtRE1CameraSwitch[n].z1),
												 glm::vec3(pRDT->rdtRE1CameraSwitch[n].x2, 0, pRDT->rdtRE1CameraSwitch[n].z2),
												 glm::vec3(pRDT->rdtRE1CameraSwitch[n].x3, 0, pRDT->rdtRE1CameraSwitch[n].z3)) || 
						
							physics::collision::triangle(m_Player->getXYZ(),
													 glm::vec3(pRDT->rdtRE1CameraSwitch[n].x2, 0, pRDT->rdtRE1CameraSwitch[n].z2),
													 glm::vec3(pRDT->rdtRE1CameraSwitch[n].x3, 0, pRDT->rdtRE1CameraSwitch[n].z3),
													 glm::vec3(pRDT->rdtRE1CameraSwitch[n].x4, 0, pRDT->rdtRE1CameraSwitch[n].z4))) {
							
							if (pRDT->rdtRE1CameraSwitch[n].to == 9)
								return;

							m_Player->setCam(pRDT->rdtRE1CameraSwitch[n].to);
							return;
						}
					}
				}		
			}
		break;

		case RDT_TYPE_RE2_PROTO:
		case RDT_TYPE_RE2:
		case RDT_TYPE_RE3: {
			for (unsigned int i = 0; i < pRDT->rdtCameraSwitch.size(); i++) {
				if (pRDT->rdtCameraSwitch[i].cam1 != 0) {
					if (physics::collision::triangle(m_Player->getXYZ(),
												 glm::vec3(pRDT->rdtCameraSwitch[i].x1, 0, pRDT->rdtCameraSwitch[i].z1),
												 glm::vec3(pRDT->rdtCameraSwitch[i].x2, 0, pRDT->rdtCameraSwitch[i].z2),
												 glm::vec3(pRDT->rdtCameraSwitch[i].x4, 0, pRDT->rdtCameraSwitch[i].z4)) || 
						
						physics::collision::triangle(m_Player->getXYZ(),
												 glm::vec3(pRDT->rdtCameraSwitch[i].x2, 0, pRDT->rdtCameraSwitch[i].z2),
												 glm::vec3(pRDT->rdtCameraSwitch[i].x3, 0, pRDT->rdtCameraSwitch[i].z3),
												 glm::vec3(pRDT->rdtCameraSwitch[i].x4, 0, pRDT->rdtCameraSwitch[i].z4))) {
						
						m_Player->setCam(pRDT->rdtCameraSwitch[i].cam1);	
						break;	
					}
				}								
			}
		}
	}
}


/**
 * checkRoomCollision
 * 
 * 
 */
void checkRoomCollision(RDT *pRDT, entity *m_Player, const float& speed) {
	/**
	 * TODO: Use float to collision boundaries
	 * TODO2: don't use isRectangle macgyver, fix it to ellipse too
	 */
	int tCollision = 0;
	static glm::vec3 norm = glm::vec3(0.0f, 0.0f, 0.0f);
	static glm::vec3 dir;
	static glm::vec3 projected;

	dir = glm::vec3(cos(glm::radians(m_Player->getAngle())) * speed, 
		  0.0f,
		 -sin(glm::radians(m_Player->getAngle())) * speed);

	switch (pRDT->rdtType) {
		case RDT_TYPE_RE1:
			for (unsigned int i = 0; i < pRDT->rdtRE1CollisionArray.size(); i++) {
				switch (pRDT->rdtRE1CollisionArray[i].type) {
					case 0:

					break;

					case 1:
						if (physics::collision::rectangle2(m_Player->getXYZ() + dir - glm::vec3(32.0f, 0.0f, 32.0f),
							glm::vec3(64.0f, 0.0f, 64.0f),
							glm::vec3(pRDT->rdtRE1CollisionArray[i].x1, 0.0f, pRDT->rdtRE1CollisionArray[i].z1),
							glm::vec3(pRDT->rdtRE1CollisionArray[i].x2, 0.0f, pRDT->rdtRE1CollisionArray[i].z2), 
							norm)) {
								std::cout << "ColNum: " << i << std::endl;
								std::cout << "floor:" << pRDT->rdtRE1CollisionArray[i].floor << std::endl;
								std::cout << "Norm(" << norm.x << "," << norm.y << "," << norm.z << std::endl;
								tCollision++;
							
							break;
						}
					break;

					case 2:

					break;

					case 3:
						if (physics::collision::ellipse(m_Player->getXYZ() + dir,
							glm::vec3(pRDT->rdtRE1CollisionArray[i].x1, 0.0f, pRDT->rdtRE1CollisionArray[i].z1),
							glm::vec3(pRDT->rdtRE1CollisionArray[i].x2, 0.0f, pRDT->rdtRE1CollisionArray[i].z2))) {
							std::cout << "Circle" << std::endl;
							tCollision = 3;
							break;
						}
					break;
				}
			}
		break;

		case RDT_TYPE_RE2_PROTO:
		case RDT_TYPE_RE2:
		case RDT_TYPE_RE3: {
		
		for (unsigned int i = 0; i < pRDT->rdtCollisionHeader.amount - 1; i++) {
				switch(pRDT->rdtCollisionArray[i].type & 0x7) {
					case 0:
						if (physics::collision::rectangle(m_Player->getXYZ(),
														 glm::vec3(pRDT->rdtCollisionArray[i].x, 0.0f, pRDT->rdtCollisionArray[i].z),
														 glm::vec3(pRDT->rdtCollisionArray[i].x + pRDT->rdtCollisionArray[i].w, 0.0f, pRDT->rdtCollisionArray[i].z + pRDT->rdtCollisionArray[i].h))) {
							tCollision++;
						}
					case 6:

					break;

					case 5:
						if (physics::collision::ellipse(m_Player->getXYZ(),
														 glm::vec3(pRDT->rdtCollisionArray[i].x, 0.0f, pRDT->rdtCollisionArray[i].z),
														 glm::vec3(pRDT->rdtCollisionArray[i].x + pRDT->rdtCollisionArray[i].w, 0.0f, pRDT->rdtCollisionArray[i].z + pRDT->rdtCollisionArray[i].h))) {
							tCollision++;
						}
					break;

					case 7:

					break;

					case 1:
						if (physics::collision::triangle(m_Player->getXYZ(),
														 glm::vec3(pRDT->rdtCollisionArray[i].x + pRDT->rdtCollisionArray[i].w, 0.0f, pRDT->rdtCollisionArray[i].z),
														 glm::vec3(pRDT->rdtCollisionArray[i].x + pRDT->rdtCollisionArray[i].w, 0.0f, pRDT->rdtCollisionArray[i].z + pRDT->rdtCollisionArray[i].h),
														 glm::vec3(pRDT->rdtCollisionArray[i].x, 0.0f, pRDT->rdtCollisionArray[i].z + pRDT->rdtCollisionArray[i].h)
														 )) {

							tCollision++;
						}
					break;

					case 2:
						if (physics::collision::triangle(m_Player->getXYZ(),
														 glm::vec3(pRDT->rdtCollisionArray[i].x, 0.0f, pRDT->rdtCollisionArray[i].z),
														 glm::vec3(pRDT->rdtCollisionArray[i].x + pRDT->rdtCollisionArray[i].w, 0.0f, pRDT->rdtCollisionArray[i].z + pRDT->rdtCollisionArray[i].h),
														 glm::vec3(pRDT->rdtCollisionArray[i].x, 0.0f, pRDT->rdtCollisionArray[i].z + pRDT->rdtCollisionArray[i].h)
														 )) {

							tCollision++;
						}
					break;

					case 3:
						if (physics::collision::triangle(m_Player->getXYZ(),
														 glm::vec3(pRDT->rdtCollisionArray[i].x, 0.0f, pRDT->rdtCollisionArray[i].z),
														 glm::vec3(pRDT->rdtCollisionArray[i].x + pRDT->rdtCollisionArray[i].w, 0.0f, pRDT->rdtCollisionArray[i].z),
														 glm::vec3(pRDT->rdtCollisionArray[i].x + pRDT->rdtCollisionArray[i].w, 0.0f, pRDT->rdtCollisionArray[i].z + pRDT->rdtCollisionArray[i].h)
														 )) {

							tCollision++;
						}
					break;

					case 4:
						if (physics::collision::triangle(m_Player->getXYZ(),
														 glm::vec3(pRDT->rdtCollisionArray[i].x, 0.0f, pRDT->rdtCollisionArray[i].z),
														 glm::vec3(pRDT->rdtCollisionArray[i].x + pRDT->rdtCollisionArray[i].w, 0.0f, pRDT->rdtCollisionArray[i].z),
														 glm::vec3(pRDT->rdtCollisionArray[i].x, 0.0f, pRDT->rdtCollisionArray[i].z + pRDT->rdtCollisionArray[i].h)
														 )) {

							tCollision++;
						}
					break;
				} 
			}

		}
		break;
	}

	
	if ((tCollision == 2) || (tCollision == 1)) {
		projected = norm * glm::dot(dir, norm);
		dir = dir - projected;
		m_Player->setXYZ(m_Player->getXYZ() + dir);
	} else if(tCollision == 0) {
		m_Player->setXYZ(m_Player->getXYZ() + dir);
	}
}

/**
 * checkDoor
 */
bool checkDoor(render *m_Render, player* m_Player, std::vector<std::unique_ptr<nTexture>> *pRDT_tex, RDT *pRDT, const RDT_TYPE_LIST& rdtType) {
	for (unsigned int i = 0; i < pRDT->doorList.size(); i++) {
		if (physics::collision::rectangle(m_Player->getXYZ(),
										 glm::vec3(pRDT->doorList[i].x, 0.0f, pRDT->doorList[i].y),
										 glm::vec3(pRDT->doorList[i].w, 0.0f, pRDT->doorList[i].h))) {
			

			if (pRDT->doorList[i].nStage != 0)
				m_Player->setStage(pRDT->doorList[i].nStage);

			m_Player->setMap(pRDT->doorList[i].nRoom);
			m_Player->setCam(0);
			m_Player->setXYZ(glm::vec3(pRDT->doorList[i].next_x, pRDT->doorList[i].next_y, pRDT->doorList[i].next_z));
			loadRoom(m_Render, m_Player, pRDT_tex, pRDT, RDT_TYPE_RE1);
			return true;
		}
	}

	return false;
}

/**
 * verify current step zone
 */
unsigned int checkStepZone(player *m_Player, RDT *pRDT) {
	for (unsigned int i = 0; i < pRDT->rdtRE1StepList.size(); i++) {
		if (physics::collision::rectangle(m_Player->getXYZ(),
										  glm::vec3(pRDT->rdtRE1StepList[i].x, 0, pRDT->rdtRE1StepList[i].y),
										  glm::vec3(pRDT->rdtRE1StepList[i].w, 0, pRDT->rdtRE1StepList[i].h))) {
			return pRDT->rdtRE1StepList[i].id;
		}
	}

	return 0;
}