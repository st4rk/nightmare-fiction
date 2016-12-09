#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "entity.h"
#include "item.h"

class player: public entity {
public:
	player();
	~player();


	void setMap(const unsigned int& map);
	void setCam(const unsigned int& cam);
	void setStage(const unsigned int& stage);
	void setWeapon(const unsigned int& weapon);

	const unsigned int& getMap();
	const unsigned int& getCam();
	const unsigned int& getStage();
	const unsigned int& getWeapon();

private:
	unsigned int itemList[10];
	unsigned int stage;
	unsigned int map;
	unsigned int cam;
	unsigned int weapon;
};


#endif