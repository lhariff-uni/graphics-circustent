#pragma once
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>
#include <iostream>

void subdivide(float ax, float ay, float az,
	float bx, float by, float bz,
	float cx, float cy, float cz, int level, float distance);
void subdivide_flat(float ax, float ay, float az,
	float bx, float by, float bz,
	float cx, float cy, float cz, int level, bool mesh);
void sphere(float radius);
void cone(float radius, int level, float height);
void cylinder(float radius, int level, float height, bool mesh, bool top = true, bool bottom = true);
void cuboid(float lengthx, float height, float lengthz, bool mesh);
void circle_outline(float radius);
void square(float ax, float ay, float az,
	float bx, float by, float bz,
	float cx, float cy, float cz,
	float dx, float dy, float dz,
	float midx, float midy, float midz, bool mesh);