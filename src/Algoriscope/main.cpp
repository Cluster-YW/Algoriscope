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
	auto col = Color("#FFFFFF");
	auto b = Vector2(100.0f, 600.0f);
	auto size = Vector2(200.0f, 100.0f);

	auto tcol = Color("#FFFF00");
	auto t = scene->timer / 1000.0f;
	cout << t << endl;
	auto a = Vector2(0 + 100 * cos(2 * t), 0);
//	render->drawText(a, 1.0, "Text Test.", tcol);
	// 文字(降低了运行的速度)

	render->drawRect(b, size, col);

	Oc->setPosition(Vector2(sin(t * 2) * 200, cos(t * 2) * 200));
	Od->setPosition(Vector2(sin(sin(t * t)) * 100, 0));

	if (t > 1.0f && t < 1.1f) {
		vari = 3.3f;
	}
	if (t > 2.0f && t < 2.1f) {
		Ba->setHeight(300.0f);
		Ba->setColor(Color("blue"));
	}
	if (t > 4.0f && t < 4.1f) {
		Ba->setWidth(300.0f);
		vari = -vari;
	}
	if (t > 3.0f && t < 3.1f) {
		Ba->setHeight(-200.0f);
	}
	return 0;
}


int main() {
	Algoriscope::Scene scn(1920, 1080, 60);
	scn.debug_mode = 0 ;
	const int n = 10;
	float array[n] = {};
	Bar* Bs[n] = {};
	for (int i = 0; i < n; i++) {
		array[i] = (float)i * 0.3f + 0.3f;
		Bs[i] = new Algoriscope::Bar(Vector2((i - 5) * 40.0f, 0)
		                             , 30, 0,
		                             Color("red").lerp(Color("blue"), i * 0.1f));
		Bs[i]->setBind(array[i]);
		scn.addObject(*Bs[i]);
	}
//	auto Bs = new Algoriscope::Bars(n, array) // 输入起码包括长度+绑定指针
	//如果后续可以考虑用vector的话就不用长度了
	for (int i = n - 1; i >= 0; i--) {
		for (int j = 0; j < i; j++) {
			if (array[j] < array[j + 1]) {
				swap(array[j], array[j + 1]);
				swap(Bs[j], Bs[j + 1]);
				Vector2 v1 = Bs[j]->getPosition();
				Bs[j]->setPosition(Bs[j + 1]->getPosition());
				Bs[j + 1]->setPosition(v1);
				float* f1 = (float*)Bs[j]->getBind();
				Bs[j]->setBind((float*)(Bs[j + 1]->getBind()));
				Bs[j + 1]->setBind(f1);
				scn.run(500);
			}
		}
	}
	scn.run(200);
}


/*
int main() {
	Algoriscope::Scene a(1920, 1080, 120);
//	a.debug_mode = 0 ;
	a.debug_function = LOOP;
	a.setTitle("COlor,TesT");
	auto Ob = new Object;
	Ob->setPosition(Vector2(0, 0));
	a.addObject(*Ob);

	Oc = new Object;
	Oc->setPosition(Vector2(200, 200));
	Ob->add_child(*Oc);

	Od = new Object;
	Od->setPosition(Vector2(200, 0));
	Ob->add_child(*Od);

	Ba = new Bar(Vector2(0, 0), 100, 100, Color("green"));
	Oc->add_child(*Ba);

	Bb = new Bar(Vector2(0, 0), 100, 100);
	Ob->add_child(*Bb);
	Bb->setBind(&vari);

	a.run(2000);
	Ob->setPosition(Vector2(-200, -300));


	a.run(2000);
	Bb->setColor(Color("yellow"));
	Ob->setPosition(Vector2(100, 100));


	a.run(2000);
}
*/

/*

int main() {
	Algoriscope::Scene scn(1920, 1080, 100);
	a.debug_mode = 1 ;
	const int n = 10;
	float* array[n] = {};
	auto Bs = new Algoriscope::Bars(n, array) // 输入起码包括长度+绑定指针
	scn.addObject(Bs);
	//如果后续可以考虑用vector的话就不用长度了
	for (int i = n - 1; i >= 0; i++) {
		for (int j = 0; j < i; j++) {
			if (array[j] < array[j + 1]) {
				Bs.swap(j, j + 1);
				scn.run(1000);
			}
		}
	}
	scn.run(1000);
}

*/
