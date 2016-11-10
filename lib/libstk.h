/*====================================
 * libstk 
 * - don't be lazy and write something here
 * - please
 * written by St4rk
 *====================================
 */

#ifndef _LIBSTK_H_
#define _LIBSTK_H_

#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>

#include "lodepng.h"


struct color {
	float r;
	float g;
	float b;
	float a;
};

enum IMAGE_FORMAT {
	IMAGE_FORMAT_BMP = 0,
	IMAGE_FORMAT_TIM = 1,
	IMAGE_FORMAT_PNG = 2,
};

class libstk {
public:
	libstk();
   ~libstk();

    void destroy();

	bool loadIMG(const std::string& dir, bool remove = false, color rColor = {1.0f, 1.0f, 1.0f, 1.0f});


	unsigned int getWidth() const;
	unsigned int getHeight() const;
	unsigned char *getTexture() const;


	IMAGE_FORMAT getFormat() const;

private:
	bool loadBMP(const std::string& dir, bool remove = false, color rColor = {1.0f, 1.0f, 1.0f, 1.0f});
	bool loadPNG(const std::string& dir);
	bool loadTIM(const std::string& dir);
	
	unsigned int width;
	unsigned int height;
	std::vector<unsigned char> texture;

	IMAGE_FORMAT format;
};

#endif