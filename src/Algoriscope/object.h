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
		const string key_all = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ []\\;\',./";
	};

	template<typename T>
	using CallBackFunction = void(*)(T* self, InputState &input);
	//定义回调函数的模板

	class Object {
		public:
			Object (void) = default;
			Object (Vector2 _pos): position(_pos) {}
			virtual void update(float deltatime, InputState &input);
			virtual void draw(Render& render);
			virtual void debug_draw(Render& render);
			bool isTouchedByMouse = 0;
			bool isClickedByMouse = 0;
			bool isLeftClickedByMouse = 0;
			bool isRightClickedByMouse = 0;

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


			CallBackFunction<Object> call_back;
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

			virtual void update(float deltatime, InputState &input);
			virtual void draw(Render & render);
			virtual void debug_draw(Render & render);

			void setCallBack(CallBackFunction<Text> in) {
				call_back = in;
			}

		protected:
			string content;
			Dynamics size;
			DynamicC color;

			CallBackFunction<Text> call_back;
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
			CallBackFunction<Bar> call_back;
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

			void setCallBack(CallBackFunction<Box> in) {
				call_back = in;
			}
		protected:
			void* bind = nullptr; // 绑定
			char bindType = 0; // 绑定类型
			Dynamics size; //尺寸
			DynamicC color; // 颜色
			Color defaultcolor; //默认颜色

			Text* tag;
			CallBackFunction<Box> call_back;
	};

	class BarArray: public Object {
		public:
			BarArray(Vector2 _pos, int _n, float _w, float _g,
			         float _h, Color c = Color("red")) :
				Object(_pos), gap(_g) {

				for (int i = 0; i < _n; i++) {
					Vector2 bpos(_g * (i - (_n - 1) * 0.5f), 0);
					Bar* bar = new Bar(bpos, _w, _h, c);
					add_child(*bar);
					bars.push_back(bar);
				}
			}
			~BarArray() {
				for (auto bar : bars) {
					delete bar;
				}
			}
			virtual void update(float deltatime, InputState &input);
			virtual void draw(Render & render);
			virtual void debug_draw(Render & render);

			void setGap(float in) {
				gap = in;
			}
			void setWidth(float in) {
				for (auto bar : bars) {
					bar->setWidth(in);
				}
			}


			template<typename T>
			void setBind(T* ptr, int n) { // 通过指针设置绑定
				auto type = typeid(ptr).name();
				bindType = type[1];
				bind = ptr;
				if (n > bars.size()) {
					Bar* btemp = bars[bars.size() - 1];
					auto _w = btemp->getWidth();
					auto c = btemp->getDefaultColor();
					auto s = btemp->getScale();
					for (int i = bars.size(); i < n; i++) {
						Vector2 bpos(gap() * (i - (bars.size() - 1) * 0.5f), 0);
						Bar* bar = new Bar(bpos, _w, 0, c);
						bar->setScale(s);
						add_child(*bar);
						bars.push_back(bar);
					}
				}
				for (int i = 0; i < n; i++) {
					bars[i]->setBind(ptr + i);
					bars[i]->setHeight(bars[i]->getScale() * ptr[i]);
				}
			}

			void animSwap(int i, int j) {
				swap(bars[j], bars[i]);
				Vector2 v1 = bars[j]->getPosition();
				bars[j]->setPosition(bars[i]->getPosition());
				bars[i]->setPosition(v1);
				float* f1 = (float*)bars[j]->getBind();
				bars[j]->setBind((float*)(bars[i]->getBind()));
				bars[i]->setBind(f1);
			}

			void setScale(float in) {
				for (auto bar : bars) {
					bar->setScale(in);
				}
			}
			void autoScale(float in) {
				float high = 0;
				float low = 0;
				for (auto bar : bars) {
					auto s = bar->getHeight() / bar->getScale();
					cout << s << endl;
					high = high > s ? high : s;
					low = low < s ? low : s;
				}
				setScale( in / (high - low));
			}
			void setAlign(char in) {
				align = in;
			}
			Bar* getBar(int index) {
				if (index < -(int)(bars.size()) || index >= bars.size()) return nullptr;
				if (index < 0)index += bars.size();
				return bars[index];
			}

			void setCallBack(CallBackFunction<BarArray> in) {
				call_back = in;
			}
			void setBarsCallBack(CallBackFunction<Bar> in) {
				for (auto bar : bars){
					bar->setCallBack(in);
				}
			}
			void setColor(Color in, int _i);
			void setColor(Color in, int _i, int _j);
		    void setDefaultColor(Color in,int _i);
		    void setDefaultColor(Color in,int _i,int _j);
			void resetColor(int _i);
			void resetColor(int _i, int _j);
		protected:
			void* bind = nullptr; // 绑定
			char bindType = 0; // 绑定类型
			Dynamics gap;
			vector<Bar*> bars;

			CallBackFunction<BarArray> call_back;
			string align;
	};
}

#endif
