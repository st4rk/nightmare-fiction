/*======================================
 * generic menu class
 * this class is used as a base to create
 * the another game menus, like start
 * written by St4rk
 *======================================
 */

#ifndef _MENU_H_
#define _MENU_H_

#include "../utils.h"
#include "../render.h"
#include "../input.h"

class menu {
public:
	menu();
   ~menu();

	virtual void stateMachine();

	void setState(unsigned int state);

	unsigned int getState();

private:

	unsigned int state;
};


#endif