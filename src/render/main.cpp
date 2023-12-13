#include "render.h"

using namespace Algoriscope;

int main(){
	cout<<"0";
	auto render=Render();
	while(1){
		render.update();
		auto a=Vector2(1,0);
		auto b=Vector2(0,1);
		render.drawLine(a,b);
	}
}
