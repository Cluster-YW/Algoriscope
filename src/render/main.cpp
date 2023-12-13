#include "render.h"

using namespace Algoriscope;

int main(){
	auto render=Render();
	while(1){
		render.update();
		render.drawLine(Vector2(1,0),Vector2(0,1),Color(255,255,255));
	}
}
