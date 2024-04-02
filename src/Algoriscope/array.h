#ifndef ARRAY_H
#define ARRAY_H

#include "object.h"

namespace Algoriscope {
	class Array: public Object {
		public:
			Array(Vector2 pos): Object(pos) {}

			virtual void update(float deltatime, InputState &input) = 0;
			virtual void draw(Render& render) = 0;
			virtual void debug_draw(Render& render) = 0;
		protected:
			void* bind = nullptr; // 绑定
			char bindType = 0; // 绑定类型
			vector<Object*> elements;
			string align = "c";

			CallBackFunction<Array> call_back = nullptr;
	};

	class BarArray: public Array {
		public:
			BarArray(Vector2 _pos, int _n, float _w, float _g,
			         float _h, Color c = Color("red")) :
				Array(_pos), gap(_g) {

				for (int i = 0; i < _n; i++) {
					Vector2 bpos(_g * (i - (_n - 1) * 0.5f), 0);
					Bar* bar = new Bar(bpos, _w, _h, c);
					add_child(*bar);
					elements.push_back(bar);
				}
			}

			virtual void update(float deltatime, InputState &input) ;
			virtual void draw(Render& render) ;
			virtual void debug_draw(Render& render) ;

			void setColor(Color in, int _i);
			void setColor(Color in, int _i, int _j);
			void setDefaultColor(Color in, int _i);
			void setDefaultColor(Color in, int _i, int _j);
			void resetColor(int _i);
			void resetColor(int _i, int _j);

			void setGap(float in) {
				gap = in;
			}
			void setWidth(float in) {
				for (auto bar : elements) {
					bar->setWidth(in);
				}
			}


			template<typename T>
			void setBind(T* ptr, int n) { // 通过指针设置绑定
				auto type = typeid(ptr).name();
				bindType = type[1];
				bind = ptr;
				if (n > elements.size()) {
					Bar* btemp = elements[elements.size() - 1];
					auto _w = btemp->getWidth();
					auto c = btemp->getDefaultColor();
					auto s = btemp->getScale();
					for (int i = elements.size(); i < n; i++) {
						Vector2 bpos(gap() * (i - (elements.size() - 1) * 0.5f), 0);
						Bar* bar = new Bar(bpos, _w, 0, c);
						bar->setScale(s);
						add_child(*bar);
						elements.push_back(bar);
					}
				}
				for (int i = 0; i < n; i++) {
					elements[i]->setBind(ptr + i);
					elements[i]->setHeight(elements[i]->getScale() * ptr[i]);
				}
			}

			void animSwap(int i, int j) {
				swap(elements[j], elements[i]);
				Vector2 v1 = elements[j]->getPosition();
				elements[j]->setPosition(elements[i]->getPosition());
				elements[i]->setPosition(v1);
				void* f1 = (void*)elements[j]->getBind();
				elements[j]->setBind((void*)(elements[i]->getBind()));
				elements[i]->setBind(f1);
			}

			void setScale(float in) {
				for (auto bar : elements) {
					bar->setScale(in);
				}
			}
			void autoScale(float in) {
				float high = 0;
				float low = 0;
				for (auto bar : elements) {
					auto s = bar->getHeight() / bar->getScale();
					cout << s << endl;
					high = high > s ? high : s;
					low = low < s ? low : s;
				}
				setScale( in / (high - low));
			}
			void setAlign(string in = "") {
				align = in;
			}
			Bar* getBar(int index) {
				if (index < -(int)(elements.size()) || index >= elements.size()) return nullptr;
				if (index < 0)index += elements.size();
				return elements[index];
			}

			void setCallBack(CallBackFunction<BarArray> in) {
				call_back = in;
			}
			void setBarsCallBack(CallBackFunction<Bar> in) {
				for (auto bar : elements) {
					bar->setCallBack(in);
				}
			}
		protected:
			Dynamics gap;
			vector<Bar*> elements;
			CallBackFunction<BarArray> call_back = nullptr;

	};
	class BoxArray: public Array {
		public:
			BoxArray(Vector2 _pos, int _n, float _size, Color c = Color("darkred")) :
				Array(_pos) {

				for (int i = 0; i < _n; i++) {
					Vector2 bpos( (i - (_n - 1) * 0.5f)*_size, 0);
					Box* box = new Box(bpos, _size, c);
					add_child(*box);
					elements.push_back(box);
				}
			}
			virtual void update(float deltatime, InputState &input) ;
			virtual void draw(Render& render) ;
			virtual void debug_draw(Render& render) ;

			void setColor(Color in, int _i);
			void setColor(Color in, int _i, int _j);
			void setDefaultColor(Color in, int _i);
			void setDefaultColor(Color in, int _i, int _j);
			void resetColor(int _i);
			void resetColor(int _i, int _j);

			void setSize(float in) {
				for (auto box : elements) {
					box->setSize(in);
				}
			}

			template<typename T>
			void setBind(T* ptr, int n) { // 通过指针设置绑定
				auto type = typeid(ptr).name();
				bindType = type[1];
				bind = ptr;
				if (n > elements.size()) {

				}
				for (int i = 0; i < n; i++) {
					elements[i]->setBind(ptr + i);
				}
			}

			void setAlign(string in = "") {
				align = in;
			}
			Box* getBox(int index) {
				if (index < -(int)(elements.size()) || index >= elements.size()) return nullptr;
				if (index < 0)index += elements.size();
				return elements[index];
			}

			void animSwap(int i, int j) {
				auto t1 = elements[i]->_getTag();
				auto t2 = elements[j]->_getTag();
				Vector2 v1 = t1->getGlobalPosition();
				Vector2 v2 = t2->getGlobalPosition();
				t1->_setPosAtOnce(v2 - v1);
				t1->setPosition(Vector2(0, 0));
				t2->_setPosAtOnce(v1 - v2);
				t2->setPosition(Vector2(0, 0));
			}
			void setCallBack(CallBackFunction<BoxArray> in) {
				call_back = in;
			}
			void setBoxsCallBack(CallBackFunction<Box> in) {
				for (auto box : elements) {
					box->setCallBack(in);
				}
			}
		protected:
			Dynamics gap;
			vector<Box*> elements;
			CallBackFunction<BoxArray> call_back = nullptr;
	};

}

#endif
