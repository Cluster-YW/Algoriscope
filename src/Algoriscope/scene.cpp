#include "scene.h"


namespace Algoriscope {
	Scene::Scene(int x, int y, int _FPS):
		size(x, y), render(x, y), FPS(_FPS), background("#222222") {
		root = new Object;
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

			float deltatime = 10.0f / FPS;

			last = now;// 稳定帧率

			timer += 1000.0f / FPS;
			this->timer += 1000.0f / FPS;
			
			if (time > 0) {
				if (timer > time) {
					break;
				}
			}

			render.update(background);

			root->update(deltatime);

			root->draw(render);

			if (debug_mode) {
				root -> debug_draw(render);
			}

			cout << i << endl;
			i++;
			
			if (debug_function != nullptr)
				debug_function(this, &render);
		}
		cout << "loopend" << endl;
		return 0;
	}
	int Scene::addObject(Object& p) {
		root->add_child(p);
		return 0;
	}
}


