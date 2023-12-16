#include "render.h"

using namespace Algoriscope;


int main() {
	auto render = Render();
	float t = 0;
	while (1) {
		auto a = Vector2(cos(t), sin(t));
		auto c = Vector2(-cos(t), sin(t));
		auto b = Vector2(0.0, 0.0);
		auto color = Color("#FF0000");
		render.drawLine(a, b, color);
		render.drawLine(c, b, color);
		render.update();
		t += 0.01f;
	}
}
