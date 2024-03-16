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


void make(BarArray* me, InputState& input) {
	cout << "?" << endl;
	for(int i=0;i<10;i++){
		me->resetColor(i);
	}
	for (int i = 0; i < 10; i++) {
		if (input.key_down['0' + i]) {
			me->setColor("blue", i);
		}
	}
}

void hightlight(Bar* me, InputState& input) {
	if (me->isClickedByMouse) {
		me->setWidth(20);
	} else if (me->isTouchedByMouse) {
		me->setWidth(90);
	} else {
		me->setWidth(50);
	}
}

int main() {
	Scene scn(1920, 1080, 100);
	int n = 9;
	auto Bs = new BarArray(Vector2(0, 0), n, 50,
	                       100, 100,Color("red")); // 输入起码包括长度+绑定指针
	scn.addObject(*Bs);
	n = 10;
	float array[n] = {0.3f, -0.6f, -0.7f, 0.2f, 0.8f
	                  , 0.1f, 0.9f, 0.4f, 2.0f, 1.0f
	                 };
	Bs->setBind(array, n);
	Bs->autoScale(500);
	Bs->setCallBack(make);
	Bs->setBarsCallBack(hightlight);
	for (int i = n - 1; i >= 0; i--) {
		for (int j = 0; j < i; j++) {
			if (array[j] < array[j + 1]) {
				swap(array[j], array[j + 1]);

				Bs->animSwap(j, j + 1);
			}
			scn.run(100);
		};
		Bs->setDefaultColor(Color("green"),i);
//		Bs->setColor(Color("green"),i);
		scn.run(100);
	};

	scn.run(5000);
}
