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
	scn.addIn(*Node);
	Node->setBind(A.data);
	Node->setNext((A.next));

	auto Node2 = new NodeBox(Vector2(0, -50), 100, "darkred");
	scn.addIn(*Node2);
	Node2->setBind(B.data);
	Node2->setNext((B.next));

	auto Node3 = new NodeBox(Vector2(400, -50), 100, "darkred");
	scn.addIn(*Node3);
	Node3->setBind(C.data);
	Node3->setNext((C.next));

	scn.run(2000);

	D.data = 15;

	auto Node4 = new NodeBox(Vector2(200, 600), 100, "darkblue");
	scn.addIn(*Node4);
	Node4->setBind(D.data);
	Node4->setPosition(Vector2(200, 100));
	Node4->setNext(D.next);

	scn.run(2000);
	D.next = B.next;
	scn.run(2000);

	B.next = &D;
	scn.run(2000);
}

int part(float arr[], int left, int right, BarArray* Bs, Text* Subtitle, Scene* scn) {
	int l = left, r = right;
	float pivot = arr[left];

	while (left < right) {
		Bs->resetDefaultColor("green", left);
		Subtitle->setContent("分割点");
		scn->run(500);
		while (left < right && arr[right] >= pivot) {
			Bs->resetDefaultColor("blue", right);
			Bs->resetDefaultColor("blue", left);
			Subtitle->setContent("比较");
			scn->run(300);
			Subtitle->setContent("无需交换");
			scn->run(500);

			Bs->resetDefaultColor("red", right);
			Bs->resetDefaultColor("green", left);
			Subtitle->setContent("分割点");
			scn->run(500);
			right--;
		}


		if (left < right) {
			Bs->resetDefaultColor("blue", right);
			Bs->resetDefaultColor("blue", left);
			Subtitle->setContent("比较");
			scn->run(300);
			swap(arr[left], arr[right]);

			Bs->animSwap(left, right);
			Subtitle->setContent("进行交换！");
			scn->run(500);
			Bs->resetDefaultColor("green", right);
			Bs->resetDefaultColor("red", left);
			Subtitle->setContent("分割点");
			scn->run(500);
			left++;
		}
		while (left < right && arr[left] <= pivot) {
			Bs->resetDefaultColor("blue", right);
			Bs->resetDefaultColor("blue", left);
			Subtitle->setContent("比较");
			scn->run(300);
			Subtitle->setContent("无需交换");
			scn->run(500);

			Bs->resetDefaultColor("green", right);
			Bs->resetDefaultColor("red", left);
			Subtitle->setContent("分割点");
			scn->run(500);
			left++;
		}

		if (left < right) {
			Bs->resetDefaultColor("blue", right);
			Bs->resetDefaultColor("blue", left);
			Subtitle->setContent("比较");
			scn->run(300);
			swap(arr[left], arr[right]);
			Bs->animSwap(left, right);
			Subtitle->setContent("进行交换！");
			scn->run(500);

			Bs->resetDefaultColor("red", right);
			Bs->resetDefaultColor("green", left);
			Subtitle->setContent("分割点");
			scn->run(500);
			right--;
		}

	}
	Bs->setDefaultColor("red", l, r);
	Bs->resetColor(l, r);
	arr[left] = pivot;
	return left;
}
void QuickSort(float arr[], int left, int right, BarArray* Bs, Text* Subtitle, Scene* scn) {
	if (left == right) {
		Bs->resetDefaultColor("green", left);
		return;
	} else if (left < right) {
		Bs->resetDefaultColor("yellow", left, right);
		scn->run(500);
		printf("[%d,%d]", left, right);

		int divide = part(arr, left, right, Bs, Subtitle, scn);
		printf("DIVIDE:%d\n", divide);
		Bs->resetDefaultColor("green", divide);
		QuickSort(arr, left, divide - 1, Bs, Subtitle, scn);
		QuickSort(arr, divide + 1, right, Bs, Subtitle, scn);
	}
}

int main_quick_sort() {
	int	n = 10;
	float array[n] = {0.3f, -0.6f, -0.7f, 0.2f, 0.8f
	                  , 0.1f, 0.9f, 0.4f, 2.0f, 1.0f
	                 };

	Scene scn(1920, 1080, 100);
	BarArray* Bs = new BarArray(Vector2(0, -60.0f), n, 50,
	                            100, 100); // 创建一个条形图对象
	scn.addIn(*Bs);
	Bs->setBind(array, n);
	Bs->autoScale(500); // 进行相关设置
	Bs->setCallBack(make);
	Bs->setBarsCallBack(hightlight); // 用于交互的回调函数
	auto Title = new Text("快速排序演示：", Vector2(-800, 400), 15, "white");
	auto Subtitle = new Text("此时进行：", Vector2(-800, 300), 10, "white", "ld");
	scn.addIn(*Title);
	scn.addIn(*Subtitle); // 加入两行文字
	scn.run(500);

	QuickSort(array, 0, n - 1, Bs, Subtitle, &scn);

	Subtitle->setContent("排序完成！");
	scn.run(1000);
}
int main_sort_bubble() {
	Scene scn(1920, 1080, 100);
	int n = 9;
	n = 10;
	float array[n] = {0.3f, -0.6f, -0.7f, 0.2f, 0.8f
	                  , 0.1f, 0.9f, 0.4f, 2.0f, 1.0f
	                 };

	auto Bs = new BarArray(Vector2(0, -60.0f), n, 50,
	                       100, 100); // 创建一个条形图对象
	scn.addIn(*Bs);
	Bs->setBind(array, n);
	Bs->autoScale(500); // 进行相关设置
	Bs->setCallBack(make);
	Bs->setBarsCallBack(hightlight); // 用于交互的回调函数
	auto Title = new Text("冒泡排序演示：", Vector2(-800, 400), 15, "white");
	auto Subtitle = new Text("此时进行：", Vector2(-800, 300), 10, "white", "ld");
	scn.addIn(*Title);
	scn.addIn(*Subtitle); // 加入两行文字

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

int sort_selection() { //选择排序源代码
	int n;
	int *arr;
	printf("输入数据总数量：\n");
	cin >> n;
	printf("输入待排序数据（整数/使用空格分隔）：\n");
	arr = new int[n];
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (arr[i] < arr[j]) {
				swap(arr[i], arr[j]);
			}
		}
	}
	for (int i = 0; i < n; i++) {
		cout << arr[i] << " ";
	}
}

int main_sort_selection() { //选择排序源代码
	int n;
	int *arr;
	printf("输入数据总数量：\n");
	cin >> n;
	printf("输入待排序数据（整数/使用空格分隔）：\n");
	arr = new int[n];
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}
	Scene scn(1920, 1080, 100);
	auto b = scn.addBind<BarArray>(arr, n,
	                               Vector2(0, 0), n, 50, 75, 0, "red");
	auto Bx = scn.addBind<BoxArray>(arr, n,
	                                Vector2(0, -200.0f), n, 100);
	for (int i = 0; i < n; i++) {
		b->setColor("blue", i);
		Bx->setColor("darkblue", i);
		for (int j = i + 1; j < n; j++) {
			b->setColor("blue", j);
			Bx->setColor("darkblue", j);
			if (arr[i] < arr[j]) {
				swap(arr[i], arr[j]);
				b->animSwap(i, j);
				Bx->animSwap(i, j);
			}
			scn.run(1000);
			b->resetColor(j);
			Bx->resetColor(j);
		}
		b->resetDefaultColor("green", i);
		Bx->resetDefaultColor("darkgreen", i);
	}
	scn.run(3000);
	for (int i = 0; i < n; i++) {
		cout << arr[i] << " ";
	}
}

int main() {
	while (1) {
		printf("输入播放的动画：\n\t1.\t冒泡排序\n\t2.\t链表插入节点\n\t3.\t快速排序\n\t4.\t插入排序\n输入：");
		int choice;
		cin >> choice;
		switch (choice) {
			case 1:
				main_sort_bubble();
				break;
			case 2:
				main_insert();
				break;
			case 3:
				main_quick_sort();
				break;
			case 4:
				main_sort_selection();
				break;
		}
	}
}
