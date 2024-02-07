#include "scene.h"

namespace Algoriscope {
	Scene::Scene(int x, int y, int _FPS):
		size(x, y), render(x, y), FPS(_FPS), background("#222222") {
	}

	int Scene::setTitle(const char*name) {
		render.setTitle(name);
		return 0;
	}

	int Scene::run(int time, bool mouse) {
		float timer = 0.0f;
		clock_t last, now;
		last = now = clock();

		auto i = 0;
		while (1) {
			now = clock();
			if (now - last < CLOCKS_PER_SEC / FPS) {
				continue;
			}
			last = now;// 稳定帧率

			timer += 1000.0f / FPS;
			if (time > 0) {
				if (timer > time) {
					break;
				}
			}

			render.update(background);
//			root->update();
//			root->render();
			cout << i << endl;
			i++;
			if (debug_function != nullptr)
				debug_function(this, &render);
		}
		cout << "loopend" << endl;
		return 0;
	}
	int Scene::addObject(Object* p) {

		return 0;
	}
}


