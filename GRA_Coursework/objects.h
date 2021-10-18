#pragma once
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>
#include <iostream>

#define NUM_EVALUATIONS     30
#define NUM_CTRL_POINTS     7

void bench(bool mesh);
void lamppost(int aS, bool light, bool mesh, bool flicker = false);
void stands(bool mesh);
void spotlight(float tilt, bool mesh, bool light = false);
void colourful_ball(float radius);
void cage_square(float x, float y, float z, float unit, bool mesh);
void stands_with_seats(bool mesh);
void entrance(bool mesh);
void flag(float aS, int numOfStages, bool mesh);