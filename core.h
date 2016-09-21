/*====================================
 * core 
 * - insert a good description here -
 * - insert a good description here -
 * - insert a good description here -
 * written by St4rk
 *====================================
 */

#ifndef _CORE_H_
#define _CORE_H_

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sstream>

#include "render.h"
#include "input.h"
#include "utils.h"
#include "sceneSchedule.h"

class core {
public:
	core();
   ~core();

    void start();
    void mainLoop();

private:
	render m_Render;
	input  m_Input;
	utils  m_Utils;
	schedule m_Schedule;

	bool coreLoop;

};

#endif