#include "render.h"

using namespace Algoriscope;


int main() {
	auto render = Render();
	float t = 0;
	while (1) {
		auto a = Vector2(cos(t), sin(t));
		auto c = Vector2(-cos(t), sin(t));
		auto b = Vector2(0.0, 0.0);
		auto d = Vector2(1.0,0.0);
		auto e = Vector2(-0.5,-0.5);
		auto color = Color("#FF0000");
		render.drawLine(a, b, color);
		auto sizea=Vector2(0.5,0.6);
		render.drawRect(e,sizea,color);
		render.drawTri(b,d,e,color);
		render.update();
		t += 0.01f;
	}
}
