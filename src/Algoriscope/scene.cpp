#include "scene.h"

namespace Algoriscope {
	Scene::Scene(int x, int y, int _FPS):
		size(x, y), render(x, y), FPS(_FPS), background("#222222") {
	}
	
	int Scene::setTitle(const char*name) {
		render.setTitle(name);
		return 0;
	}
	
	int Scene::run(const Color& background,int time,bool mouse) {
		float timer = 0.0f;
		clock_t last, now;
		last = now = clock();
		
		while (1) {
			
			// TODO : 这里加一段填充背景色
			render.update(background);
			
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


