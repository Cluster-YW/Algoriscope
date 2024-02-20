#include "render.h"
#include "object.h"
#include <iostream>
using namespace Algoriscope;
int main() {
<<<<<<< HEAD
	Render render(1500,1500);
	int arr[10]={1,2,3,4,5,8,7,8,9,10};
	Bar a(10);
	while (1) {
		a.Draw(render);
	}
=======
	//use Scene:
	//Algoriscope::Scene a(1200, 800);
	//a.setTitle("Test window");
	//a.run(1000);
	//a.run(1000);
	

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
		
		render.drawRect(b, size1, col);
		render.drawRectBorder(c, size2, col,10);
		render.drawLine(b, c, col ,10);
		render.drawPoints(d,col,5);
	
		
		// 文字
		auto a = Vector2(-100 + 100 * cos(2 * t), 0);
		render.drawText(a,1.0, "Text Test.", tcolor);
		
		t += 1.0f / FPS;
	}	
>>>>>>> 840ed39b2fbc8c7a772eb5af67975486e45b7dab
}
