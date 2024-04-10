#ifndef OBJECT_H
#define OBJECT_H

#include "vector2.h"
#include <vector>
#include "dynamics.h"
#include "render.h"
#include "Format.h"

namespace Algoriscope {
	struct InputState {
		Vector2 mousepos_screen;
		Vector2 mousepos;
		bool mouse_left_down = 0;
		bool mouse_right_down = 0;
		bool key_down[350] = {};
		int key_change[350] = {};
		const string key_all = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ []\\;\',./\n";
	};

	Vector2 calcRadiusRectEnd(const Vector2& C,
	                          const Vector2& RU, const Vector2& LD, const Vector2& n);

	template<typename T>
	using CallBackFunction = void(*)(T* self, InputState &input);
	//定义回调函数的模板

	class Object {
		public:
			Object (void) = default;
			Object (Vector2 _pos): position(_pos) {}

			~Object() {
				for (auto pObj : children) {
					cout << "Deleting Object...\n";
					delete pObj;
				}
			}
			virtual void update(float deltatime, InputState &input);
			virtual void draw(Render& render);
			virtual void debug_draw(Render& render);

			virtual	Vector2 getPointedPos(Vector2 from) {
				return global_position;
			}

			bool isTouchedByMouse = 0;
			bool isClickedByMouse = 0;
			bool isLeftClickedByMouse = 0;
			bool isRightClickedByMouse = 0;

			int add_child(Object &target);

			void setPosition(const Vector2 pos) {
				position = pos;
			}
			void _setPosAtOnce(const Vector2 pos) {
				position.set(pos);
			}
			Vector2 getPosition() {
				return position.getInput();
			}
			Vector2 getGlobalPosition() {
				return global_position;
			}
			void setCallBack(CallBackFunction<Object> in) {
				call_back = in;
			}
		protected:
			virtual void mouseProcess(InputState& input);
			Dynamics2 position; // 位置
			Vector2 global_position; // 全局位置/渲染位置
			void setGlobalPosition(Vector2 v2) {
				global_position = v2;
			}
			Object* parent = nullptr; // 父对象
			std::vector<Object*> children; // 子对象


			CallBackFunction<Object> call_back = nullptr;
		public:
			bool display = 1; //是否显示
	};

	extern std::map<void*, std::vector<Object*>> bind_map;

	void addBindMap(void* ptr, Object* obj);
	void popBindMap(void* ptr, Object* obj);

	class Text: public Object {
		public:
			Text(string _c, Vector2 _pos, float _size, Color c = Color("red"), string _align = "m"):
				content(_c), Object(_pos), size(_size), color(c), align(_align) {
			}
			Text(Vector2 _pos, float _size, Color c = Color("red"), string _align = "m"):
				content(""), Object(_pos), size(_size), color(c), align(_align) {
			}

			void setContent(string input) {
				content.content = input;
				content.generate();
			}
			void setSize(float input) {
				size = input;
			}
			void setAlign(string input) {
				align = input;
			}

			virtual void update(float deltatime, InputState &input);
			virtual void draw(Render & render);
			virtual void debug_draw(Render & render);

			void setCallBack(CallBackFunction<Text> in) {
				call_back = in;
			}

		protected:
			TextUre content;
			Dynamics size;
			DynamicC color;

			string align;
			CallBackFunction<Text> call_back = nullptr;
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
			virtual void update(float deltatime, InputState &input);
			virtual void draw(Render & render);
			virtual void debug_draw(Render & render);

			virtual	Vector2 getPointedPos(Vector2 from) {
				return calcRadiusRectEnd(global_position + Vector2(0, 0.5 * height()), global_position + Vector2(-0.5f * width(), 0),
				                         global_position + Vector2(0.5f * width(), height()), from - (global_position + Vector2(0, 0.5 * height())));
			}

			int add_child(Object & target);


			void setHeight(float h) { // 设置高度（带动画）
				height = h;
			}
			void setWidth(float w) { // 设置宽度（带动画）
				width = w;
			}
			float getHeight() {
				return height.getInput();
			}
			float getWidth() {
				return width.getInput();
			}
			float getScale() {
				return scale.getInput();
			}

			template<typename T>
			void setBind(T* ptr) { // 通过指针设置绑定
				popBindMap(bind, this);
				auto type = typeid(ptr).name();
				if (type[1] != 'v')
					bindType = type[1];
				bind = ptr;
				addBindMap(bind, this);
				tag->display = 1;
			}

			template<typename T>
			void setBind(T& ptr) { // 通过引用设置绑定
				setBind(&ptr);
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
			void resetDefaultColor(Color in) {
				defaultcolor = in;
				color = defaultcolor;
			}

			Color getColor() {
				return color.getInput();
			}
			Color getDefaultColor() {
				return defaultcolor;
			}

			void setCallBack(CallBackFunction<Bar> in) {
				call_back = in;
			}

		protected:
			virtual void mouseProcess(InputState& input);
			void* bind = nullptr; // 绑定
			char bindType = 0; // 绑定类型
			Dynamics scale = 100; // 与绑定变量的比例
			Dynamics width; // 宽度
			Dynamics height; // 高度
			DynamicC color; // 颜色
			Color defaultcolor; //默认颜色

			Text* tag = nullptr;
			CallBackFunction<Bar> call_back = nullptr;
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

			virtual void update(float deltatime, InputState &input);
			virtual void draw(Render & render);
			virtual void debug_draw(Render & render);

			void setSize(float in) {
				size = in;
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
			void resetDefaultColor(Color in) {
				defaultcolor = in;
				color = defaultcolor;
			}

			template<typename T>
			void setBind(T* ptr) { // 通过指针设置绑定
				auto type = typeid(ptr).name();
				popBindMap(bind, this);
				bindType = type[1];
				bind = ptr;
				tag->display = 1;
				addBindMap(bind, this);
			}

			template<typename T>
			void setBind(T& ptr) { // 通过引用设置绑定
				setBind(&ptr);
			}

			void* getBind() { // 获取绑定
				return bind;
			}

			void setCallBack(CallBackFunction<Box> in) {
				call_back = in;
			}

			Text* _getTag() {
				return tag;
			}
		protected:
			void* bind = nullptr; // 绑定
			char bindType = 0; // 绑定类型
			Dynamics size; //尺寸
			DynamicC color; // 颜色
			Color defaultcolor; //默认颜色

			Text* tag;
		private:
			CallBackFunction<Box> call_back;
	};

	class NodeBox: public Box {
		public:
			NodeBox(Vector2 _pos, float _size, Color _c = Color("red")) :
				Box(_pos, _size, _c) {
				tag = new Text("3", Vector2(0, 0), _size * 0.1f, Color("#FFFFFF"));
				add_child(*tag);
				tag->display = 0;
			}
			~NodeBox() {
				delete tag;
			}

			virtual void update(float deltatime, InputState &input);
			virtual void draw(Render & render);
			virtual void debug_draw(Render & render);

			virtual	Vector2 getPointedPos(Vector2 from);

			void setCallBack(CallBackFunction<NodeBox> in) {
				call_back = in;
			}

			void setNext(void** next) {
				pointer = next;
			}

			template<typename T>
			void setNext(T &next) {
				pointer = (void**)&next;
			}

			void** getNext() {
				return pointer;
			}

		protected:
			void** pointer = nullptr;

			CallBackFunction<NodeBox> call_back = nullptr;
	};
}

#endif
