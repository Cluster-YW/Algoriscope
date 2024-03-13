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

			float deltatime = 1.0f / FPS;

			timer += 1000.0f * (now - last) / CLOCKS_PER_SEC;
			this->timer += 1000.0f * (now - last) / CLOCKS_PER_SEC;

			last = now;// 稳定帧率


			if (time > 0) {
				if (timer > time) {
					break;
				}
			}

			render.update(background);

			root->update(deltatime);

			root->draw(render);

			if (debug_mode) {
				render.drawLine(Vector2(-size.x, 0), Vector2(size.x, 0), Color("#0000FF"));
				render.drawLine(Vector2(0, -size.y), Vector2(0, size.y), Color("#FF0000"));
				render.drawText(Vector2(size.x * 0.5f - 20, 15), 5,
				                util::Format("{0}", size.x * 0.5f), "#0000FF");
				render.drawText(Vector2(20, size.y * 0.5f - 15), 5,
				                util::Format("{0}", size.y * 0.5f), "#FF0000");
				render.drawText(Vector2(-size.x * 0.48f, size.y * 0.48f), 5, "#" + to_string(i), "#FFFFFF");
				root -> debug_draw(render);
			}

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


