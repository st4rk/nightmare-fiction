#ifndef _DEBUG_H_
#define _DEBUG_H_

#include "../../scene.h"

#include <iostream>
#include <cstring>


struct RE2_JUMP_ENTRY {
	float x;
	float z;
	std::string roomName;
};

static RE2_JUMP_ENTRY bh2_beta2[] = {
	{18802.0f, -3164.0f, "URADOURI WEST "},
	{-15047.0f, -11799.0f, "GUN SHOP      "},
	{-25059.0f, 20944.0f, "ROJI          "},
	{-24302.0f, -20765.0f, "SHIKICHI HALL "},
	{-18136.0f, -21867.0f, "URADOURI EAST "},
	{12210.0f, -11899.0f, "SHIKICHI URA  "},
	{-25843.0f, -479.0f, "KOYA          "},
	{-14938.0f, 31.0f, "SHIKICHI EAST "},
	{-4847.0f, -2702.0f, "OKUJYOU       "},
	{-4563.0f, -1171.0f, "2F URAGUCHI   "},
	{-25000.0f, -25500.0f, "HERI ROUKA    "},
	{-18337.0f, -13460.0f, "BIJYUTSU SOUKO"},
	{6722.0f, 953.0f, "2F KAIDAN     "},
	{-11360.0f, -10600.0f, "SYOCHOU ROUKA "},
	{-25000.0f, -25000.0f, "OUSETSUSHITSU "},
	{-15091.0f, -18319.0f, "2F SAVE ROOM  "},
	{-1814.0f, -23470.0f, "HALL 2F       "},
	{-20000.0f, -20000.0f, "TOKEI DAI     "},
	{-8122.0f, -18830.0f, "TOSYOSHITU    "},
	{-23000.0f, -23000.0f, "T ROUKA       "},
	{-14308.0f, -25963.0f, "GYAKU KO ROUKA"},
	{-18444.0f, -12335.0f, "STARS ROOM    "},
	{-20772.0f, -25169.0f, "MIGI KAIDAN   "},
	{-26349.0f, -1137.0f, "HALL 3F       "},
	{-10353.0f, 2930.0f, "TUIKA 2       "},
	{-6168.0f, -15445.0f, "TUIKA 3       "},
	{-7250.0f, -550.0f, "TUIKA 4       "},
	{-8353.0f, -20638.0f, "TUIKA 5       "},
	{-4847.0f, -2702.0f, "OMAKE OKUJYOU "},
	{-25059.0f, 20944.0f, "ROJI BAK      "}
};


struct debug {
	/* TODO: is it really necessary :| ? */
	_menu menu[2];
     
	unsigned int currMap;

	void nextMap() {
		char jump_name[0xFF];
		if (currMap < 29) {
			currMap++;
			memset(jump_name, 0, 0xFF);
			sprintf(jump_name, "JUMP %d%02X %s", 1, currMap, bh2_beta2[currMap].roomName.c_str());
			menu[1].text = jump_name;
		}
	}

	void priorMap() {
		char jump_name[0xFF];
		if (currMap > 0) {
			currMap--;
			memset(jump_name, 0, 0xFF);
			sprintf(jump_name, "JUMP %d%02X %s", 1, currMap, bh2_beta2[currMap].roomName.c_str());
			menu[1].text = jump_name;
		}
	}

	void update(const unsigned int& map) {
		menu[0] = {"- DEBUG MENU - ", -0.40f, 0.10f, 0.0f, 0, false};
		menu[1] = {"JUMP", -0.50f, -0.05f, 0.0f, 0, false};
		
		currMap = map;

		char jump_name[0xFF];
		memset(jump_name, 0, 0xFF);
		sprintf(jump_name, "JUMP %d%02X %s", 1, currMap, bh2_beta2[currMap].roomName.c_str());
		menu[1].text = jump_name;
	}

	const float& getMapX() { return bh2_beta2[currMap].x; }
	const float& getMapZ() { return bh2_beta2[currMap].z; }

};

#endif