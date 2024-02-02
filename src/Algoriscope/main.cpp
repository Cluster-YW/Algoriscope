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
	//use Scene:
	//Algoriscope::Scene a(600, 800);
	//a.setTitle("Test window");
	//a.run("#005500",1000);
	//a.run("#550000",1000);
	

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
		auto b = Vector2(100.0f, 600.0f);
		auto size = Vector2(200.0f, 100.0f);
		
		//要先绘制图形再绘制文字
		
		render.drawRect(b, size, col);
	
		auto a = Vector2(500 + 100 * cos(2 * t), 600);
		render.drawText(a, 1.0, "Text Test.", tcolor);
		// 文字
		
		t += 1.0f / FPS;
	}	
}
