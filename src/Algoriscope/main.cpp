#include "render.h"
#include "time.h"
#include "dynamics.h"
using namespace Algoriscope;

const float FPS = 60;

int main() {
	auto render = Render();
	int t = 0;
	clock_t last, now;
	last = now = clock();
	Dynamics d(0,5.0f,0.25f,1.0f);
	Color color("#66CCFF");
	Vector2 a(0,0);
	while (1) {
		now = clock();
		if (now - last > CLOCKS_PER_SEC / FPS) {
			if(t/((int)FPS*1)%2){
				d=1.0f;
				color=Color("#66CCFF");
			}
			else{
				d=0.0f;
				color=Color("#FF0000");
			}
			render.drawLine(a, Vector2(0.5f,d()), color);
			t+=1;
			
			d.update(1.0/FPS);
			render.update();
			
			last = now;
		}
	}
}
