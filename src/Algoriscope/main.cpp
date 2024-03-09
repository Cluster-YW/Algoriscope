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


int main() {
	
	auto render = Render(1200, 900);
	render.setTitle("Hello OpenGL");

	float t = 0;
	clock_t last, now;
	last = now = clock();
	
	auto tcolor = Color("#FF6611");
	
	while (1) {
		now = clock();
		if (now - last < CLOCKS_PER_SEC / FPS) {
			continue;
		}
		last = now;// 稳定帧率
		
		tcolor.SetR(255 * sin(t));
		
		render.update("#000000");
		
		auto col = Color("#FFFF00");
		auto b = Vector2(-580.0f, -400.0f);
		auto size1 = Vector2(200.0f, 100.0f);
		auto size2 = Vector2(300.0f,250.0f);
		auto c = Vector2(0.0f, 0.0f);
		auto d = Vector2(300,300);
		
		render.drawTextInit();
		auto a = Vector2(-100 + 100 * cos(2 * t), 0);
		render.drawText(a,1.0, "Text Test.", tcolor);
		auto a2 = Vector2(110,-100);
		render.drawText(a2,1.0, "aaa.", tcolor);
		
		auto a1 = Vector2(200 + 100 * cos(2 * t), 0);
		render.drawChinese(a1,1.0, L"宋体", tcolor);
		
		render.drawRect(b, size1, col);
		render.drawRectBorder(c, size2, col,10);
		render.drawLine(b, c, col ,10);
		render.drawPoints(d,col,5);

		t += 1.0f / FPS;
	}	
}
