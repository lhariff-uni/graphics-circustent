#pragma once
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "shapes.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>
#include <iostream>

void stage(bool mesh);
void tent_walls(bool mesh);
void tent_roof(bool mesh);
void tent_roof_mini(bool mesh);