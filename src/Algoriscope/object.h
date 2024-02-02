#ifndef OBJECT_H
#define OBJECT_H

#include"vector2.h"
#include"color.h"
#include"render.h"

namespace Algoriscope {
	class ObjectRect {
		public:
			void getRect(const Vector2& x, const Vector2& y, const Color& z){
				{
					pos=x;size=y;col=z;
				}
			}
			void Rect();
		private:
			Vector2 pos;
			Vector2 size;
			Color col;
		

	};
	void ObjectRect::Rect(){
		{
			Render drawRect(pos,size,col);
		}
	}

	
}

#endif
