#ifndef _ENTITY_H_
#define _ENTITY_H_


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/vector_angle.hpp>
#include "../../nf3d/nf3d.h"
#include "../../utils.h"

enum ENTITY_ACTION {
	ENTITY_ACTION_IDLE,
	ENTITY_ACTION_WALK,
	ENTITY_ACTION_HIT,
	ENTITY_ACTION_DEATH
};

class entity {
public:
	entity();
	~entity();

	void setModel(const unsigned int& model);
	void setXYZ(const glm::vec3& xyz);
	void setAngle(const float& angle);
	void setAction(const ENTITY_ACTION& entityAction);
	void setHP(const unsigned int &hp);

	const unsigned int& getModel();
	const unsigned int& getHP();
	const glm::vec3& getXYZ();
	const float& getAngle();
	const ENTITY_ACTION& getAction();

	float aFactor;
	timer entityTmr;
private:
	ENTITY_ACTION entityAction;

	glm::vec3 xyz;
	unsigned int model;
	unsigned int hp;
	unsigned int status;
	float angle;
};


#endif