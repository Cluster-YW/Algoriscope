#ifndef OBJECT_H
#define OBJECT_H
#include"render.h"

namespace Algoriscope {
	class Object {
		public:
		Object*object;
		int x=0;
		Vector2 pos{Vector2 (0,0)};
		Color col{("#FF0000")};
		int DrawBar();
		

	};
	int Object::DrawBar()
	{   Vector2 a(2,x);
		drawRect(pos,a,col);
	     return 0;
	};
	
}

#endif
