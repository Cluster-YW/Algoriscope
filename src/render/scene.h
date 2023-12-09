#ifndef ALGORISCOPE_SCENE_H
#define ALGORISCOPE_SCENE_H

#include "render.h"
#include "object.h"

namespace Algoriscope {
	class Scene {
		private:
			Render render;
			Object root;
			Color color_bg;
		public:
			Scene() {

			}
			~Scene() {

			}
	};
}

#endif

