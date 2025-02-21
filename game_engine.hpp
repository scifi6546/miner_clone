#ifndef game_engine_H
#define game_engine_H

#include <SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
int init();
void draw();
void draw_temps();//temporary delete not
glm::vec3 engineKeyboardEvent(char key,bool is_down);
void engineMouseEvent(int x_rel, int y_rel);
int getHeight();
int getWidth();
#endif
