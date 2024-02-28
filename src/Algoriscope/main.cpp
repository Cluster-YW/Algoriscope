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

Object* Oc;
Object* Od;
Bar* Ba ;

float vari = 1.0f;

int LOOP(Scene* scene, Render* render) {
	auto col = Color("#FFFFFF");
	auto b = Vector2(100.0f, 600.0f);
	auto size = Vector2(200.0f, 100.0f);

	auto tcol = Color("#FFFF00");
	auto t = scene->timer / 1000.0f;
//	cout<<t<<endl;
	auto a = Vector2(500 + 100 * cos(2 * t), 600);
	render->drawText(a, 1.0, "Text Test.", tcol);
	// 文字

	render->drawRect(b, size, col);

	Oc->setPosition(Vector2(sin(t * 2) * 200, cos(t * 2) * 200));
	Od->setPosition(Vector2(sin(sin(t * t)) * 100, 0));

	if (t > 1.0f && t < 1.1f) {
		vari = 2.5f;
	}
	if (t > 2.0f && t < 2.1f) {
		Ba->setHeight(300.0f);
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
	Algoriscope::Scene a(1920, 1080, 10);
	a.debug_mode = 1 ;
	a.debug_function = LOOP;
	a.setTitle("Test window");
	auto Ob = new Object;
	Ob->setPosition(Vector2(500, 700));
	a.addObject(*Ob);

	Oc = new Object;
	Oc->setPosition(Vector2(200, 200));
	Ob->add_child(*Oc);

	Od = new Object;
	Od->setPosition(Vector2(200, 0));
	Ob->add_child(*Od);

	Ba = new Bar(Vector2(0, 0), 100, 100);
	Oc->add_child(*Ba);

	auto Bb = new Bar(Vector2(0, 0), 100, 100);
	Ob->add_child(*Bb);
	Bb->setBind(&vari);

	a.run(2000);
	Ob->setPosition(Vector2(700, 300));

	a.run(2000);
	Ob->setPosition(Vector2(1000, 700));

	a.run(2000);
}
