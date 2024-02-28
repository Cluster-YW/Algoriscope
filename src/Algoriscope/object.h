#ifndef OBJECT_H
#define OBJECT_H

#include "vector2.h"
#include <vector>
#include "dynamics.h"
#include "render.h"

namespace Algoriscope {
	class Object {
		public:
			Object (void) = default;
			Object (Vector2 _pos): position(_pos) {}
			virtual void update(float deltatime);
			virtual void draw(Render& render);
			virtual void debug_draw(Render& render);

			int add_child(Object &target);

			void setPosition(const Vector2 pos) {
				position = pos;
			}
			Vector2 getGlobalPosition() {
				return global_position;
			}
			
//			double getxposition(){
//				return 
//			}

		protected:
			Dynamics2 position; // 位置
			Vector2 global_position; // 全局位置/渲染位置
			void setGlobalPosition(Vector2 v2) {
				global_position = v2;
			}
			Object* parent = nullptr; // 父对象
			std::vector<Object*> children; // 子对象
	};

	class Bar: public Object {
		public:
			Bar(Vector2 _pos, float _w, float _h):
				Object(_pos), width(_w), height(_h) {

			}
			virtual void update(float deltatime);
			virtual void draw(Render & render);
			virtual void debug_draw(Render & render);

			int add_child(Object & target);

			void setPosition(const Vector2 pos) {
				position = pos;
			}


			void setHeight(float h) { // 设置高度（带动画）
				height = h;
			}
			void setWidth(float w) { // 设置宽度（带动画）
				width = w;
			}

			void setBind(float *fp) { // 设置绑定
				bind = fp;
			}
			
		
		protected:
			float* bind; // 绑定
			Dynamics scale = 100; // 与绑定变量的比例
			Dynamics width; // 宽度
			Dynamics height; // 高度
	};
}

#endif
