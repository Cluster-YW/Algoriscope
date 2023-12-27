#include "render.h"
#include "time.h"
#include "dynamics.h"
using namespace Algoriscope;

const float FPS = 60;

//int main() {
//	auto render = Render();
//	int t = 0;
//	clock_t last, now;
//	last = now = clock();
//	Dynamics d(0, 5.0f, 1.0f, 1.0f);
//	Dynamics2 d2(Vector2(-0.5f, 0.0f), 3.0f, 1.0f, 0.5f);
//	Color color("#66CCFF");
//	Vector2 a(0, 0);
//	while (1) {
//		now = clock();
//		if (now - last > CLOCKS_PER_SEC / FPS) {
//			if (t % (int)(FPS) == 0) {
//				if (t / ((int)FPS * 1) % 2) {
//					d = 1.0f;
//					color = Color("#66CCFF");
//				} else {
//					d = 0.0f;
//					color = Color("#FF0000");
//				}
//			}
//
//			if ((t+10) % (int)(FPS * 0.5f) == 0) {
//				auto temp = d2().y + 0.25f;
//				if (temp < 0.5f) {
//					d2 = Vector2(-0.5f, temp);
//				} else {
//					d2 = Vector2(-0.5f, -0.5f);
//				}
//				d.set(-1.0f);
//			}
//
//			render.drawLine(a, Vector2(0.5f, d()), color);
//			render.drawRect(d2(), Vector2(0.2f, 0.2f), color);
//			t += 1;
//
//			d.update(1.0 / FPS);
//			d2.update(1.0 / FPS);
//			render.update();
//
//			last = now;
//		}
//	}
//}

int main() {
	auto render = Render();
	int t = 0;
	clock_t last, now;
	last = now = clock();
<<<<<<< Updated upstream
	Dynamics d(0, 5.0f, 0.25f, 1.0f);
	Dynamics2 d2(Vector2(-0.5f, 0.0f), 3.0f, 1.0f, 0.5f);
	Color color("#66CCFF");
=======
	Color colorA("#FF0000");
	Color colorB("#00FF00");
	colorB.setA(0);
>>>>>>> Stashed changes
	Vector2 a(0, 0);
	while (1) {
		now = clock();
		if (now - last > CLOCKS_PER_SEC / FPS) {
<<<<<<< Updated upstream
			if (t / ((int)FPS * 1) % 2) {
				d = 1.0f;
				color = Color("#66CCFF");
			} else {
				d = 0.0f;
				color = Color("#FF0000");
			}

			if (t % (int)(FPS * 0.5f) == 0) {
				auto temp = d2().y + 0.25f;
				if (temp < 0.5f) {
					d2 = Vector2(-0.5f, temp);
				} else {
					d2 = Vector2(-0.5f, -0.5f);
					d.set(-1.0f);
				}
			}
			render.drawLine(a, Vector2(0.5f, d()), color);
			render.drawRect(d2(), Vector2(0.2f, 0.2f), color);
=======



			render.drawRect(Vector2(0.0f, 0.0f), Vector2(0.2f, 0.2f),
			                colorA.lerp(colorB, sin(t/10.0f)));
>>>>>>> Stashed changes
			t += 1;

			render.update();

			last = now;
		}
	}
}
