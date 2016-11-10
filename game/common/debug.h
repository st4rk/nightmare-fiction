#ifndef _DEBUG_H_
#define _DEBUG_H_

#include "../../scene.h"

#include <iostream>
#include <cstring>


#define DEBUG_TYPE_BH2_BETA2 0
#define DEBUG_TYPE_BH2_PROTO 1

struct JUMP_ENTRY {
	float x;
	float z;
	std::string roomName;
};

static JUMP_ENTRY bh2_proto[] = {
	{-16221.0f, -22346.0f, "              "},
	{-16221.0f, -22346.0f, "              "},
	{-26000.0f, -8700.0f, "OFFICE B      "},
	{-8200.0f, -22500.0f, "LOBBY         "},
	{-22000.0f, -3200.0f, "LOBBY ROUKA   "},
	{-16221.0f, -22346.0f, "              "},
	{-26378.0f, -25630.0f, "KAIDAN 1      "},
	{850.0f, 3600.0f, "OFFICE A      "},
	{-16221.0f, -22346.0f, "              "},
	{-10200.0f, 1400.0f, "SOTO B        "},
	{-16221.0f, -22346.0f, "KAIDAN 2     -"},
	{17164.0f, -7892.0f, "SOTO A        "},
	{-16221.0f, -22346.0f, "              "},
	{-16221.0f, -22346.0f, "              "},
	{-16221.0f, -22346.0f, "              "},
	{-16221.0f, -22346.0f, "              "},
	{-18000.0f, -25000.0f, "SIRYOUSITU MAE"},
	{-16221.0f, -22346.0f, "              "},
	{-16221.0f, -22346.0f, "              "},
	{-16221.0f, -22346.0f, "              "},
	{-16221.0f, -22346.0f, "              "},
	{-17370.0f, -11900.0f, "SHOCHO ROOM   "},
	{-26000.0f, -19220.0f, "HELI PORT MAE "},
	{3940.0f, 14167.0f, "OKUJYOU       "},
	{-21889.0f, -25508.0f, "B1 ROUKA      "},
	{3050.0f, -11650.0f, "SHOOTING RANGE"},
	{-22487.0f, -16764.0f, "BUKI  SOUKO   "},
	{-26130.0f, -18455.0f, "CHIKA CYUU B  "},
	{-22604.0f, 14455.0f, "CHIKA CYUU A  "},
	{-16221.0f, -22346.0f, "              "},
	{10000.0f, 10000.0f, "B2 ROUKA      "},
	{-24901.0f, -8038.0f, "BOIRA SHITSU  "},
	{-19894.0f, -25139.0f, "SHITAI OKIBA  "},
	{-26420.0f, -2400.0f, "RYUUCHI SYO   "},
	{-22176.0f, -6664.0f, "DOKUBOU 1     "},
	{-16596.0f, -9870.0f, "DOKUBOU 2     "},
	{-22202.0f, -14073.0f, "DOKUBOU 3     "},
	{-17012.0f, -17784.0f, "DOKUBOU 4     "},
	{-16796.0f, -25105.0f, "DOKUBOU 5     "},
};

static JUMP_ENTRY bh2_beta2[] = {
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

static JUMP_ENTRY re1_sample[] = {
	{3800.0f, 2700.0f, "    SAVE ROOM    "},
	{19000.0f, 20500.0f, " 1F LEFT STAIRS  "},
	{3400.0f, 8800.0f, "   VACANT ROOM   "},
	{3000.0f, 3000.0f, "    F PASSAGE    "},
	{11600.0f, 2500.0f, "    TEA ROOM     "},
	{31900.0f, 8600.0f, "   DINING ROOM   "},
	{17000.0f, 2800.0f, "      HALL       "},
	{2700.0f, 6600.0f, "     GALLERY     "},
	{3400.0f, 4000.0f, "    L PASSAGE    "},
	{24400.0f, 2700.0f, "  TRAP PASSAGE   "},
	{15200.0f, 3900.0f, "  BACK PASSAGE   "},
	{3300.0f, 6600.0f, " 1F RIGHT STAIRS "},
	{13600.0f, 7400.0f, "   GREEN HOUSE   "},
	{5600.0f, 3000.0f, "TIGER STATUE ROOM"},
	{7400.0f, 10700.0f, "  EMPLOYEE ROOM  "},
	{15200.0f, 2550.0f, "       BAR       "},
	{2800.0f, 10400.0f, "   1F ELEVATOR   "},
	{2800.0f, 4600.0f, "  DRESSING ROOM  "},
	{2900.0f, 15300.0f, "    WARDROBE     "},
	{2800.0f, 2400.0f, "    BATH ROOM    "},
	{10030.0f, 23449.0f, "     BOILER      "},
	{2500.0f, 4900.0f, "   TRAP ROOM     "},
	{4850.0f, 10250.0f, "  LIVING ROOM    "},
	{2900.0f, 10600.0f, " LARGE GALLERY   "},
	{6000.0f, 7600.0f, "STAIRS UNDER ROOM"},
	{6300.0f, 2700.0f, "      STUDY      "},
	{4500.0f, 4100.0f, " ROOFED PASSAGE  "},
	{2700.0f, 6000.0f, "   STORE ROOM    "},
	{3500.0f, 4500.0f, "   WARDROBE S    "}
};

struct debug {
	/* TODO: is it really necessary :| ? */
	_menu menu[2];
     
	unsigned int currMap;
	unsigned int type;

	void nextMap() {
		char jump_name[0xFF];
		if (currMap < 0x1C) {
			currMap++;
			memset(jump_name, 0, 0xFF);
			sprintf(jump_name, "JUMP %d%02X %s", 1, currMap, re1_sample[currMap].roomName.c_str());
			menu[1].text = jump_name;
		}
	}

	void priorMap() {
		char jump_name[0xFF];
		if (currMap > 0) {
			currMap--;
			memset(jump_name, 0, 0xFF);
			sprintf(jump_name, "JUMP %d%02X %s", 1, currMap, re1_sample[currMap].roomName.c_str());
			menu[1].text = jump_name;
		}
	}

	void update(const unsigned int& map) {
		menu[0] = {"- DEBUG MENU - ", -0.40f, 0.10f, 0.0f, 0, false};
		menu[1] = {"JUMP", -0.60f, -0.05f, 0.0f, 0, false};
		
		currMap = map;

		char jump_name[0xFF];
		memset(jump_name, 0, 0xFF);
		sprintf(jump_name, "JUMP %d%02X %s", 1, currMap, re1_sample[currMap].roomName.c_str());
		menu[1].text = jump_name;
	}

	const float& getMapX() { return re1_sample[currMap].x; }
	const float& getMapZ() { return re1_sample[currMap].z; }

};

#endif