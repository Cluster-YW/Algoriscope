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

//int LOOP(Scene* scn, Render* render){
//	TextUre a("123随便来点中文");
//	render->drawText(Vector2(0,-100),20,a,"red","l");
//}

void make(BarArray* me, InputState& input) {
//	cout << "?" << endl;
	for (int i = 0; i < 10; i++) {
		if (input.key_change['0' + i] == 1) {
			me->setColor("yellow", i);
		}
		if (input.key_change['0' + i] == -1) {
			me->resetColor(i);
		}
	}
	me->setAlign("c");
	if (input.key_down['A']) {
		me->setAlign("l");
	} else if (input.key_down['D']) {
		me->setAlign("r");
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
//	scn.debug_function = LOOP;
	int n = 9;
	auto Bs = new BarArray(Vector2(0, -60.0f), n, 50,
	                       100, 100); // 输入起码包括长度+绑定指针
	scn.addObject(*Bs);
	n = 10;
	float array[n] = {0.3f, -0.6f, -0.7f, 0.2f, 0.8f
	                  , 0.1f, 0.9f, 0.4f, 2.0f, 1.0f
	                 };
	Bs->setBind(array, n);
	Bs->setAlign("right");
	Bs->autoScale(500);
	Bs->setCallBack(make);
	Bs->setBarsCallBack(hightlight);
	auto Title = new Text("冒泡排序演示：",Vector2(-800,400),15,"white");
	auto Subtitle = new Text("此时进行：",Vector2(-800,300),10,"white","ld");
	scn.addObject(*Title);
	scn.addObject(*Subtitle);
	for (int i = n - 1; i >= 0; i--) {
		for (int j = 0; j < i; j++) {
			Bs->getBar(j)->setDefaultColor("blue");
			Bs->getBar(j+1)->setDefaultColor("blue");
			Bs->getBar(j)->resetColor();
			Bs->getBar(j+1)->resetColor();
			Subtitle->setContent("比较");
			scn.run(1000);
			Subtitle->setContent("无需交换");
			if (array[j] < array[j + 1]) {
				swap(array[j], array[j + 1]);

				Bs->animSwap(j, j + 1);
			Subtitle->setContent("进行交换！");
			}
			scn.run(1000);
			Bs->getBar(j)->setDefaultColor("red");
			Bs->getBar(j+1)->setDefaultColor("red");
			Bs->getBar(j)->resetColor();
			Bs->getBar(j+1)->resetColor();
		}
		Bs->getBar(i)->setDefaultColor("green");
		Bs->getBar(i)->resetColor();
	}
	scn.run(5000);
}
