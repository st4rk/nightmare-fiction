#include "player.h"


player::player() {
	map = 0;
	cam = 0;
	stage = 0;
}

player::~player() {
	map = 0;
	cam = 0;
	stage = 0;
}

void player::setMap(const unsigned int& map) {
	this->map = map;
}

void player::setCam(const unsigned int& cam) {
	this->cam = cam;
}

void player::setStage(const unsigned int& stage) {
	this->stage = stage;
}


const unsigned int& player::getMap() { return map; }
const unsigned int& player::getCam() { return cam; }
const unsigned int& player::getStage() { return stage; }
