#ifndef SCENE_H
#define SCENE_H

#include <time.h>
#include <map>
#include <vector>

#include "vector2.h"
#include "color.h"
#include "object.h"
#include "render.h"


namespace Algoriscope {
	class Scene {
		public:
			bool debug_mode = 0;
			float timer = 0.0f;
			int (*debug_function)(Scene*, Render*, InputState&) = nullptr;

			Scene(int x, int y, int _FPS = 60);
			~Scene() {
				bind_map.clear();
				delete root;
			}

			int setTitle(const char*name);

			// 运行场景一定时间
			// time -	运行的时间（毫秒）
			// mouse -	是否可以通过空格直接结束
			int run(int time = -1, bool canbreak = 1);

			void processInput();

			int addObject(Object& p);
		private:
			void debug_info_draw(int i);

			int FPS;
			Vector2 size;
			string title;
			Render render;
			Color background;
			Object* root; // 之后把这里改成一个 unique_ptr
			InputState input;
			bool running = 1;
			bool paused = 0;
	};
}

#endif

