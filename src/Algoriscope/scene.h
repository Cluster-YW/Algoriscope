#ifndef SCENE_H
#define SCENE_H

#include "vector2.h"
#include "color.h"
#include "object.h"
#include "render.h"

namespace Algoriscope {
	class Scene {
		public:
			Scene(int x, int y);
		private:
			Vector2 size;
			string title;
			Render render;
			Color background;
	};
}

#endif
