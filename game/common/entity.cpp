#include "entity.h"


entity::entity() {
	xyz = glm::vec3(0.0f, 0.0f, 0.0f);
	angle = 0.0f;
	entityAction = ENTITY_ACTION_IDLE;
	model = 0;
}


entity::~entity() {
	xyz = glm::vec3(0.0f, 0.0f, 0.0f);
	angle = 0.0f;
	entityAction = ENTITY_ACTION_IDLE;
	model = 0;
}

/*
 * setModel
 * set current model 
 * no return
 */
void entity::setModel(const unsigned int& model) {
	this->model = model;
}

/*
 * setXYZ
 * set current entity xyz coordinates
 * no return
 */
void entity::setXYZ(const glm::vec3& xyz) {
	this->xyz = xyz;
}

/*
 * setAngle
 * set current entity angle
 * no return
 */
void entity::setAngle(const float& angle) {
	this->angle = angle;
}

/*
 * setAction
 * set new action
 * no return
 */
void entity::setAction(const ENTITY_ACTION& entityAction) {
	this->entityAction = entityAction;
}

/*
 * getModel
 * get current model
 * return model object
 */
const unsigned int& entity::getModel() { return model; }

/*
 * getXYZ
 * get current xyz coordinates
 * return vec3 object
 */
const glm::vec3& entity::getXYZ() { return xyz; }

/*
 * getAngle
 * get current angle
 * return angle in float
 */
const float& entity::getAngle() { return angle; }

/*
 * getAction
 * get current entity action
 * return current action
 */
const ENTITY_ACTION& entity::getAction() { return entityAction; }



