// Std. Includes
#include "render.h"
#include <iostream>
#include <map>
#include <string>
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>
// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
// FreeType
#include <ft2build.h>
#include FT_FREETYPE_H
// Timer
#include <time.h>
// GL includes
#include "algoriscope.h"

using namespace Algoriscope;

int main() {
	Algoriscope::Scene a(600, 800);
	a.run(1000);
	a.run(500);
	a.run(250);
	a.run(250);
	a.run(250);
	a.run(250);
	a.run(100);
	a.run(100);
	a.run(100);
	a.run(100);
	a.run(100);
	a.run(100);
	return 0;
}

