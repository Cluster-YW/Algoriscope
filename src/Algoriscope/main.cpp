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
#include "Shader.h"
#include "algoriscope.h"
using namespace Algoriscope;

int LOOP(Scene* scene, Render* render) {
	auto col = Color("#FFFF00");
	auto b = Vector2(100.0f, 600.0f);
	auto size = Vector2(200.0f, 100.0f);

	render->drawRect(b, size, col);

	auto tcol = Color("#FFFF00");
	auto t = 0.0f;
	auto a = Vector2(500 + 100 * cos(2 * t), 600);
	render->drawText(a, 1.0, "Text Test.", tcol);
	// 文字

}

int main() {
	Algoriscope::Scene a(1920, 1080);
	a.debug_function = LOOP;
	a.setTitle("Test window");
	a.run(1000);
	a.run(1000);
	a.run(1000);
}
