/*====================================
 * loader
 * Here is written the shader loader function
 * TODO: don't be lazy and write my own shader loader
 * source: http://www.opengl-tutorial.org/beginners-tutorials/tutorial-2-the-first-triangle/
 * written by St4rk
 *====================================
 */

#ifndef _LOADER_H_
#define _LOADER_H_

#include <iostream>
#include <vector>
#include <fstream>
#include <cstdio>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

extern GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);

#endif