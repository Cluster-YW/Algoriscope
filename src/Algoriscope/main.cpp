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

int LOOP(Scene* scn, Render* render, InputState& input) {
//	TextUre a("123随便来点中文");
//	render->drawText(Vector2(0,-100),20,a,"red","l");
//	render->drawArrow(Vector2(0, -100), input.mousepos, "white", 5);
//	Node2->setPosition(input.mousepos);
}

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

struct Node {
	int data;
	Node* next;
} A, B, C, D;

int main_insert() {
	Scene scn(1920, 1080, 100);
//	scn.debug_function = LOOP;

	A.data = 10;
	B.data = 5;
	C.data = 20;
	A.next = &B;
	B.next = &C;


	auto Node = new NodeBox(Vector2(-400, -50), 100, "darkred");
	scn.addObject(*Node);
	Node->setBind(A.data);
	Node->setNext((A.next));

	auto Node2 = new NodeBox(Vector2(0, -50), 100, "darkred");
	scn.addObject(*Node2);
	Node2->setBind(B.data);
	Node2->setNext((B.next));

	auto Node3 = new NodeBox(Vector2(400, -50), 100, "darkred");
	scn.addObject(*Node3);
	Node3->setBind(C.data);
	Node3->setNext((C.next));

	scn.run(2000);

	D.data = 15;

	auto Node4 = new NodeBox(Vector2(200, 600), 100, "darkblue");
	scn.addObject(*Node4);
	Node4->setBind(D.data);
	Node4->setPosition(Vector2(200, 100));
	Node4->setNext(D.next);

	scn.run(2000);
	D.next = B.next;
	scn.run(2000);

	B.next = &D;
	scn.run(2000);
}
int main_sort() {
	Scene scn(1920, 1080, 100);
	int n = 9;
	n = 10;
	float array[n] = {0.3f, -0.6f, -0.7f, 0.2f, 0.8f
	                  , 0.1f, 0.9f, 0.4f, 2.0f, 1.0f
	                 };

	auto Bs = new BarArray(Vector2(0, -60.0f), n, 50,
	                       100, 100); // 创建一个条形图对象
	scn.addObject(*Bs);
	Bs->setBind(array, n);
	Bs->autoScale(500); // 进行相关设置
	Bs->setCallBack(make);
	Bs->setBarsCallBack(hightlight); // 用于交互的回调函数
	auto Title = new Text("冒泡排序演示：", Vector2(-800, 400), 15, "white");
	auto Subtitle = new Text("此时进行：", Vector2(-800, 300), 10, "white", "ld");
	scn.addObject(*Title);
	scn.addObject(*Subtitle); // 加入两行文字

	for (int i = n - 1; i >= 0; i--) {
		for (int j = 0; j < i; j++) {
			Bs->setDefaultColor("blue", j, j + 1);
			Bs->resetColor(j, j + 1); // 修改 j 和 j+1 条形的颜色为蓝色
			Subtitle->setContent("比较"); //修改文字内容
			scn.run(1000); // 运行动画 1s

			Subtitle->setContent("无需交换");// 修改文字内容

			if (array[j] < array[j + 1]) {
				swap(array[j], array[j + 1]);

				Bs->animSwap(j, j + 1);// 执行交换动画
				Subtitle->setContent("进行交换！");// 修改文字内容
			}
			scn.run(1000); // 运行动画 1s
			Bs->setDefaultColor("red", j, j + 1);
			Bs->resetColor(j, j + 1); // 修改 j 和 j+1 条形的颜色回红色
		}
		Bs->setDefaultColor("green", i); // 将排序好的数据颜色设置为绿色
		Bs->resetColor(i);
	}
	scn.run(5000);
}
int main() {
	while (1) {
		printf("输入播放的动画：\n\t1.\t冒泡排序\n\t2.\t链表插入节点\n输入：");
		int choice;
		cin >> choice;
		switch (choice) {
			case 1:
				main_sort();
				break;
			case 2:
				main_insert();
				break;
		}
	}
}
