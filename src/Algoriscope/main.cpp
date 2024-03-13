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

Object* Oc, * Od;
Bar* Ba, * Bb ;

double vari = 0.5f;

int LOOP(Scene* scene, Render* render) {

}

/*
int main() {
	Scene scn(1920, 1080, 60);
//	scn.debug_mode = 1 ;
//	scn.debug_function = LOOP;
	scn.setTitle("Bubble Sort");
	const int n = 10;
	float array[n] = {0.3f, 0.6f, 0.7f, 0.2f, 0.8f
	                  , 0.1f, 0.9f, 0.4f, 0.5f, 1.0f
	                 };
	Bar* Bs[n] = {};
	Box* Bx[n] = {};

	for (int i = 0; i < n; i++) {
		Bs[i] = new Bar(Vector2((i - 4.5f) * 100.0f, 0)
		                , 50, 0,
		                Color("blue").lerp(Color("orange"), array[i] - 0.1f));
		Bs[i]->setBind(array[i]);
		Bs[i]->setScale(400);
		scn.addObject(*Bs[i]);

		Bx[i] = new Box(Vector2((i - 4.5f) * 100.0f, -100.0f), 100.0f, "darkblue");
		Bx[i]->setBind(array[i]);
		scn.addObject(*Bx[i]);
	}

	auto t = new Text("FUCKYOU", Vector2(-150.0f, -200.0f), 12.0, Color("yellow"));
	auto tj = new Text("FUCKYOU", Vector2(150.0f, -200.0f), 12.0, Color("yellow"));
	scn.addObject(*t);
	scn.addObject(*tj);
	string stri = "i=0";
	string strj = "j=0";
//	auto Bs = new Algoriscope::Bars(n, array) // 输入起码包括长度+绑定指针
	//如果后续可以考虑用vector的话就不用长度了
	for (int i = 0; i < n; i++) {
		stri[2] = i + '0';
		t->setContent(stri);
		for (int j = i+1; j < n; j++) {
			strj[2] = j + '0';
			tj->setContent(strj);

			if (array[j] < array[i]) {
				swap(array[j], array[i]);
				swap(Bs[j], Bs[i]);
				Vector2 v1 = Bs[j]->getPosition();
				Bs[j]->setPosition(Bs[i]->getPosition());
				Bs[i]->setPosition(v1);
				float* f1 = (float*)Bs[j]->getBind();
				Bs[j]->setBind((float*)(Bs[i]->getBind()));
				Bs[i]->setBind(f1);
			}
			Bs[j]->setColor("red");
			Bs[i]->setColor("red");
			Bx[j]->setColor("darkred");
			Bx[i]->setColor("darkred");
			scn.run(200);
			Bs[j]->resetColor();
			Bs[i]->resetColor();
			Bx[j]->resetColor();
			Bx[i]->resetColor();
		}
		Bs[i]->setColor("green");
		Bx[i]->setColor("green");
	}
	scn.run(1000);
	for (int i = 0; i < n; i++) {
		Bs[i]->resetColor();
		Bx[i]->setColor("darkgreen");
		scn.run(100);
	}
	scn.run(2000);
	delete[] Bs;
	delete[] Bx;
}*/


int main() {
	Scene scn(1920, 1080, 100);
	scn.debug_mode = 1 ;
	int n = 9;
	auto Bs = new BarArray(Vector2(0, 0), n, 50,
	                       100, 100); // 输入起码包括长度+绑定指针
	scn.addObject(*Bs);
	n = 10;
	float array[n] = {0.3f, -0.6f, -0.7f, 0.2f, 0.8f
	                  , 0.1f, 0.9f, 0.4f, 2.0f, 1.0f
	                 };
	Bs->setBind(array, n);
	Bs->autoScale(500);
	for (int i = n - 1; i >= 0; i--) {
		for (int j = 0; j < i; j++) {
			if (array[j] < array[j + 1]) {
				swap(array[j], array[j + 1]);

				Bs->animSwap(j, j + 1);
			}
			scn.run(100);
		}
	}
	scn.run(1000);
}
