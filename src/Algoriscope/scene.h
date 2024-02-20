#ifndef SCENE_H
#define SCENE_H

#include <time.h>

#include "vector2.h"
#include "color.h"
#include "object.h"
#include "render.h"


namespace Algoriscope {
	class Scene {
	public:
		Scene(int x, int y, int _FPS = 60);
		
		int setTitle(const char*name); 
		
		// 运行场景一定时间
		// time -	运行的时间（毫秒）
		// mouse -	是否可以通过鼠标点击直接结束
		int run(const Color& background,int time = -1, bool mouse = 1);
		
		
		int addObject(Object* p);
	private:
		int FPS;
		Vector2 size;
		string title;
		Render render;
		Color background;
		Object* root; // 之后把这里改成一个 unique_ptr
	};
}

#endif

