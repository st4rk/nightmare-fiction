#ifndef _ENTITY_H_
#define _ENTITY_H_


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "../../nf3d/nf3d.h"

enum ENTITY_ACTION {
	ENTITY_ACTION_IDLE,
	ENTITY_ACTION_WALK
};

class entity {
public:
	entity();
	~entity();

	void setModel(const unsigned int& model);
	void setXYZ(const glm::vec3& xyz);
	void setAngle(const float& angle);
	void setAction(const ENTITY_ACTION& entityAction);

	const unsigned int& getModel();
	const glm::vec3& getXYZ();
	const float& getAngle();
	const ENTITY_ACTION& getAction();
private:
	ENTITY_ACTION entityAction;

	glm::vec3 xyz;
	unsigned int model;
	float angle;
};


#endif