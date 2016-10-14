#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "entity.h"

class player: public entity {
public:
	player();
	~player();


	void setMap(const unsigned int& map);
	void setCam(const unsigned int& cam);
	void setStage(const unsigned int& stage);
	
	const unsigned int& getMap();
	const unsigned int& getCam();
	const unsigned int& getStage();

private:
	unsigned int stage;
	unsigned int map;
	unsigned int cam;
};


#endif