#include "core.h"


/*
static void (MyClass::*const s_functions[3])() = { &MyClass::function1, &MyClass::function2, &MyClass::function3 };
...
(this->*(s_functions[x]))(); */

int main(int argc, char **argv) {
	core m_Core;

	m_Core.start();
	return 0;
}