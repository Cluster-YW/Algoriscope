#ifndef OBJECT_H
#define OBJECT_H

#include "vector2.h"
#include <vector>
#include "dynamics.h"
#include "render.h"
#include "Format.h"

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
			Vector2 getPosition() {
				return position.getInput();
			}
			Vector2 getGlobalPosition() {
				return global_position;
			}

		protected:
			Dynamics2 position; // 位置
			Vector2 global_position; // 全局位置/渲染位置
			void setGlobalPosition(Vector2 v2) {
				global_position = v2;
			}
			Object* parent = nullptr; // 父对象
			std::vector<Object*> children; // 子对象
		public:
			bool display = 1; //是否显示
	};

	class Text: public Object {
		public:
			Text(string _c, Vector2 _pos, float _size, Color c = Color("red")):
				content(_c), Object(_pos), size(_size), color(c) {
			}
			Text(Vector2 _pos, float _size, Color c = Color("red")):
				Object(_pos), size(_size), color(c) {
			}

			void setContent(string input) {
				content = input;
			}
			void setSize(float input) {
				size = input;
			}

			virtual void update(float deltatime);
			virtual void draw(Render & render);
			virtual void debug_draw(Render & render);
		protected:
			string content;
			Dynamics size;
			DynamicC color;
	};

	class Bar: public Object {
		public:
			Bar(Vector2 _pos, float _w, float _h, Color c = Color("red")):
				Object(_pos), width(_w), height(_h), color(c),
				defaultcolor(c) {
				tag = new Text("3", Vector2(0, 0), _w * 0.2f, Color("#FFFFFF"));
				Object::add_child(*tag);
				tag->display = 0;
			}
			~Bar() {
				delete tag;
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

			template<typename T>
			void setBind(T* ptr) { // 通过指针设置绑定
				auto type = typeid(ptr).name();
				bindType = type[1];
				bind = ptr;
				tag->display = 1;
			}

			template<typename T>
			void setBind(T& ptr) { // 通过引用设置绑定
				auto type = typeid(ptr).name();
				bindType = type[0];
				bind = &ptr;
				tag->display = 1;
			}

			void* getBind() { // 获取绑定
				return bind;
			}

			void setScale(float in) {
				scale = in;
			}

			void setColor(Color in) { //设置颜色
				color = in;
			}

			void resetColor() { //设置颜色
				color = defaultcolor;
			}

			void setDefaultColor(Color in) {
				defaultcolor = in;
			}

		protected:
			void* bind = nullptr; // 绑定
			char bindType = 0; // 绑定类型
			Dynamics scale = 100; // 与绑定变量的比例
			Dynamics width; // 宽度
			Dynamics height; // 高度
			DynamicC color; // 颜色
			Color defaultcolor; //默认颜色

			Text* tag;
	};

	class Box: public Object {

		public:
			Box(Vector2 _pos, float _size, Color _c = Color("red")) :
				Object(_pos), size(_size), color(_c),
				defaultcolor(_c) {
				tag = new Text("3", Vector2(0, 0), _size * 0.1f, Color("#FFFFFF"));
				Object::add_child(*tag);
				tag->display = 0;
			}
			~Box() {
				delete tag;
			}

			virtual void update(float deltatime);
			virtual void draw(Render & render);
			virtual void debug_draw(Render & render);

			void setColor(Color in) { //设置颜色
				color = in;
			}

			void resetColor() { //设置颜色
				color = defaultcolor;
			}

			void setDefaultColor(Color in) {
				defaultcolor = in;
			}

			template<typename T>
			void setBind(T* ptr) { // 通过指针设置绑定
				auto type = typeid(ptr).name();
				bindType = type[1];
				bind = ptr;
				tag->display = 1;
			}

			template<typename T>
			void setBind(T& ptr) { // 通过引用设置绑定
				auto type = typeid(ptr).name();
				bindType = type[0];
				bind = &ptr;
				tag->display = 1;
			}

			void* getBind() { // 获取绑定
				return bind;
			}
		protected:
			void* bind = nullptr; // 绑定
			char bindType = 0; // 绑定类型
			Dynamics size; //尺寸
			DynamicC color; // 颜色
			Color defaultcolor; //默认颜色

			Text* tag;
	};

}

#endif
