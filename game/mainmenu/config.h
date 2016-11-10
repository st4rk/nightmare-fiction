#ifndef _CONFIG_H_

#include "../../scene.h"

enum CONFIG_LAYERS {
	CONFIG_LAYER_INIT,
	CONFIG_LAYER_RUN,
	CONFIG_LAYER_END
};

#define TOTAL_ENTRY 3

class menuConfig : public scene {
public:

	menuConfig();
	~menuConfig();

	virtual void stateMachine();
	virtual void start();

private:
	void checkInput();

	CONFIG_LAYERS layers;
	
	unsigned char arrow;
	bool pressed;
	
	std::unique_ptr<nTexture> bg;
};

#endif