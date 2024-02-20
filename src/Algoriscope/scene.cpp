#include "scene.h"

namespace Algoriscope {
	Scene::Scene(int x, int y, int _FPS):
		size(x, y), render(x, y), FPS(_FPS), background("#222222") {
	}
<<<<<<< HEAD

	int Scene::run(int time, bool mouse) {
=======
	
	int Scene::setTitle(const char*name) {
		render.setTitle(name);
		return 0;
	}
	
	int Scene::run(int time,bool mouse) {
>>>>>>> 840ed39b2fbc8c7a772eb5af67975486e45b7dab
		float timer = 0.0f;
		clock_t last, now;
		last = now = clock();

		while (1) {
			
<<<<<<< HEAD
			// TODO : 这里加一段填充背景色
=======
			
>>>>>>> 840ed39b2fbc8c7a772eb5af67975486e45b7dab
			
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
			
			// TODO : 这里加一段填充背景色
			render.update(background);
			
//			root->update();
//			root->render();
		}
		cout << "loopend" << endl;
		return 0;
	}
	int Scene::addObject(Object* p) {
		return 0;
	}
}
