#include "object.h"
namespace Algoriscope {

	Vector2 calcRadiusRectEnd(const Vector2& C,
	                          const Vector2& RU, const Vector2& LD, const Vector2& n) {
		auto check = [](Vector2 res, Vector2 C, float u, float d, float l, float r, Vector2 n)-> bool {
			if ((res.x - C.x)*n.x < 0) return 0;
			if ((res.y - C.y)*n.y < 0) return 0;
			if (res.x > r || res.x < l) return 0;
			if (res.y > u || res.y < d) return 0;
			return 1;
		};
		auto u = max(RU.y, LD.y);
		auto d = min(RU.y, LD.y);
		auto l = min(RU.x, LD.x);
		auto r = max(RU.x, LD.x);

		Vector2 trying;
		trying = Vector2(l, C.y + (l - C.x) * n.y / n.x);
		if (check(trying, C, u, d, l, r, n)) return trying;
		trying = Vector2(r, C.y + (r - C.x) * n.y / n.x);
		if (check(trying, C, u, d, l, r, n)) return trying;

		trying = Vector2(C.x + (u - C.y) * n.x / n.y, u);
		if (check(trying, C, u, d, l, r, n)) return trying;
		trying = Vector2(C.x + (d - C.y) * n.x / n.y, d);
		if (check(trying, C, u, d, l, r, n)) return trying;
	}

	std::map<void*, std::vector<Object*>> bind_map;

	void addBindMap(void* ptr, Object* obj) {
		if (ptr == nullptr)return;
		if (bind_map.count(ptr)) {
			bind_map[ptr].push_back(obj);
		} else {
			bind_map[ptr] = vector<Object*>();
			bind_map[ptr].push_back(obj);
		}
	}

	void popBindMap(void* ptr, Object* obj) {
		if (ptr == nullptr)return;
		if (bind_map.count(ptr)) {
			auto &vec = bind_map[ptr];
			auto newEnd = std::remove(vec.begin(), vec.end(), obj);
			vec.erase(newEnd, vec.end());
		}
	}

	void Object::update(float deltatime, InputState &input) {

		position.update(deltatime); // 更新位置的动画

		if (parent != nullptr) // 从父对象更新渲染位置
			global_position = (parent->global_position) + position();
		else
			global_position = position();

		for (auto child : children ) { // 进一步调用子对象的update()
			child->update(deltatime, input);
		}

	}
	void Object::draw(Render& render) {
		for (auto child : children ) { // 进一步调用子对象的draw()
			child->draw(render);
		}
	}
	void Object::debug_draw(Render& render) {
		render.drawRectBorder(global_position, Vector2(20, 20), Color("#FF0000"), 2);
		// 调试渲染
		std::string posinfo;
		posinfo = "(" + std::to_string((int)global_position.x) +
		          "," + std::to_string((int)global_position.y) + ")";
		render.drawText(global_position + Vector2(0, -20), 3.0f, posinfo, Color("#00FF00"));


		for (auto child : children ) { // 进一步调用子对象的debug_draw()
			child->debug_draw(render);
		}
	}
	int Object::add_child(Object &target) {
		children.push_back(&target); // 加入目标的地址（相当于指针）
		target.parent = this; // 设定目标的父对象为自己
		return children.size() - 1;
	}

	void Object::mouseProcess(InputState& input) {
		isTouchedByMouse = 0;
		isClickedByMouse = 0;
		isLeftClickedByMouse = 0;
		isRightClickedByMouse = 0;
	}

	void Bar::update(float deltatime, InputState &input) {

		if (bind != nullptr) { // 实现与外部变量绑定
			float _scale = scale();
			float _width = width();
			float text_bios = height() > 0 ? 0.5f : -0.5f;
			if (bindType == 'i') {
				tag->setContent( to_string( *(int*)bind ));
				setHeight( *(int*)bind * _scale);
				tag->setPosition(Vector2(0, *(int*)bind * _scale + _width * text_bios));
			} else if (bindType == 'x')	{
				tag->setContent( to_string( *(long long*)bind ));
				setHeight( *(long long*)bind * _scale);
				tag->setPosition(Vector2(0, *(long long*)bind * _scale + _width * text_bios));
			} else if (bindType == 'f')	{
				tag->setContent( util::Format("{0}", *(float*)bind));
				setHeight( *(float*)bind * _scale);
				tag->setPosition(Vector2(0, *(float*)bind * _scale + _width * text_bios));
			} else if (bindType == 'd')	{
				tag->setContent( util::Format("{0}", *(double*)bind) );
				setHeight( *(double*)bind * _scale);
				tag->setPosition(Vector2(0, *(double*)bind * _scale + _width * text_bios));
			}
		}

		position.update(deltatime); // 更新位置的动画
		width.update(deltatime); // 更新宽度
		height.update(deltatime); // 更新高度
		color.update(deltatime); //更新颜色
		scale.update(deltatime);


		if (parent != nullptr) // 从父对象更新渲染位置
			global_position = (parent->getGlobalPosition()) + position();
		else
			global_position = position();

		mouseProcess(input);

		if (call_back != nullptr) {
			call_back(this, input);
		}

		for (auto child : children ) { // 进一步调用子对象的update()
			child->update(deltatime, input);
		}

	}
	void Bar::draw(Render& render) {
		if (display == 0) {
			for (auto child : children ) { // 进一步调用子对象的draw()
				child->draw(render);
			}
			return;
		}

		Vector2 draw_position = global_position + Vector2(-width() * 0.5f, 0);

		if (height() < 0) { // 实现高度为负，向下绘制
			draw_position = draw_position + Vector2(0, height());
			render.drawRect(draw_position,
			                Vector2(width(), -height()), color());
//			render.drawRectBorder(draw_position, Vector2(width(), -height()), Color("yellow"), 3);
		} else {
			render.drawRect(draw_position,
			                Vector2(width(), height()), color());
//			render.drawRectBorder(draw_position, Vector2(width(), height()), Color("yellow"), 3);
		}


		for (auto child : children ) { // 进一步调用子对象的draw()
			child->draw(render);
		}
	}
	void Bar::debug_draw(Render& render) {
		render.drawRectBorder(global_position, Vector2(20, 20), Color("green"), 2);


		std::string posinfo;
		posinfo = "(" + std::to_string((int)global_position.x) +
		          "," + std::to_string((int)global_position.y) + ")";
		render.drawText(global_position + Vector2(0, -20), 3.0f, posinfo, Color("#00FFFF"));

		std::string sizeinfo;
		sizeinfo = "(" + std::to_string((int)width()) +
		           "," + std::to_string((int)height()) + ")";
		render.drawText(global_position + Vector2(0, -40), 3.0f, sizeinfo, Color("#00FFFF"));


		for (auto child : children ) { // 进一步调用子对象的debug_draw()
			child->debug_draw(render);
		}
	}
	void Bar::mouseProcess(InputState& input)  {
		float L = global_position.x - width() * 0.5f;
		float R = global_position.x + width() * 0.5f;
		float U = global_position.y + max(0.0f,  height());
		float D = global_position.y + min(0.0f, height());
		isTouchedByMouse = 0;
		isClickedByMouse = 0;
		isLeftClickedByMouse = 0;
		isRightClickedByMouse = 0;
		if (input.mousepos.x > L and input.mousepos.x < R and
		    input.mousepos.y > D and input.mousepos.y < U) {
			isTouchedByMouse = 1;
			if (input.mouse_left_down)isLeftClickedByMouse = isClickedByMouse = 1;
			if (input.mouse_right_down)isRightClickedByMouse = isClickedByMouse = 1;
		}
//		cout << util::Format("[{0},{1}],[{2},{3}]:{4}\n", L, R, U, D,isTouchedByMouse);
	}

	void Text::update(float deltatime, InputState &input) {
		size.update(deltatime);
		position.update(deltatime); // 更新位置的动画
		color.update(deltatime); //更新颜色

		if (parent != nullptr) // 从父对象更新渲染位置
			global_position = (parent->getGlobalPosition()) + position();
		else
			global_position = position();

		for (auto child : children ) { // 进一步调用子对象的update()
			child->update(deltatime, input);
		}
	}
	void Text::draw(Render& render) {
		if (display == 0) {
			for (auto child : children ) { // 进一步调用子对象的draw()
				child->draw(render);
			}
			return;
		}
		render.drawText(global_position, size(), content, color(), align);
		for (auto child : children ) { // 进一步调用子对象的draw()
			child->draw(render);
		}
	}
	void Text::debug_draw(Render& render) {
		render.drawRectBorder(global_position, Vector2(20, 20), Color("#0000FF"), 2);
		for (auto child : children ) { // 进一步调用子对象的debug_draw()
			child->debug_draw(render);
		}
	}

	void Box::update(float deltatime, InputState &input) {

		if (bind != nullptr) { // 实现与外部变量绑定
			if (bindType == 'i') {
				tag->setContent( to_string( *(int*)bind ));
			} else if (bindType == 'x')	{
				tag->setContent( to_string( *(long long*)bind ));
			} else if (bindType == 'f')	{
				tag->setContent( util::Format("{0}", *(float*)bind));
			} else if (bindType == 'd')	{
				tag->setContent( util::Format("{0}", *(double*)bind) );
			}
		}

		size.update(deltatime);
		position.update(deltatime); // 更新位置的动画
		color.update(deltatime); //更新颜色

		if (parent != nullptr) // 从父对象更新渲染位置
			global_position = (parent->getGlobalPosition()) + position();
		else
			global_position = position();

		for (auto child : children ) { // 进一步调用子对象的update()
			child->update(deltatime, input);
		}
	}

	void Box::draw(Render& render) {
		if (display == 0) {
			for (auto child : children ) { // 进一步调用子对象的draw()
				child->draw(render);
			}
			return;
		}
		Vector2 Vsize(size(), size());
		render.drawRect(global_position - 0.5f * Vsize, Vsize,
		                color());
		render.drawRectBorder(global_position - 0.5f * Vsize, Vsize,
		                      color().mix("#FFFFFF", 0.5f), size() * 0.05f);
		for (auto child : children ) { // 进一步调用子对象的draw()
			child->draw(render);
		}
	}

	void Box::debug_draw(Render& render) {
		for (auto child : children ) { // 进一步调用子对象的debug_draw()
			child->debug_draw(render);
		}
	}

	void BarArray::update(float deltatime, InputState &input) {
		position.update(deltatime); // 更新位置的动画
		gap.update(deltatime);

		int n =	bars.size();
		float gap_ = gap();

		for (int i = 0; i < n; i++) {
			if (align.find_first_of("l") != string::npos) {
				Vector2 bpos( gap_ * i + bars[i]->getWidth() * 0.5f, 0);
				bars[i]->setPosition(bpos);
			} else if (align.find_first_of("c") != string::npos) {
				Vector2 bpos( gap_ * (i - (n - 1) * 0.5f), 0);
				bars[i]->setPosition(bpos);
			} else if (align.find_first_of("r") != string::npos) {
				Vector2 bpos(-gap_ * i - bars[i]->getWidth() * 0.5f, 0);
				bars[i]->setPosition(bpos);
			}
		}

		if (call_back != nullptr) {
			call_back(this, input);
		}

		if (parent != nullptr) // 从父对象更新渲染位置
			global_position = (parent->getGlobalPosition()) + position();
		else
			global_position = position();

		for (auto child : children ) { // 进一步调用子对象的update()
			child->update(deltatime, input);
		}
	}
	void BarArray::draw(Render & render) {
		if (display == 0) {
			for (auto child : children ) { // 进一步调用子对象的draw()
				child->draw(render);
			}
			return;
		}
		for (auto child : children ) { // 进一步调用子对象的draw()
			child->draw(render);
		}
	}
	void BarArray::debug_draw(Render & render) {
		for (auto child : children ) { // 进一步调用子对象的debug_draw()
			child->debug_draw(render);
		}
	}
	void BarArray ::setColor(Color in, int i) {
		bars[i]->setColor(in);
	};
	void BarArray ::setColor(Color in, int i, int j) {
		for (i = i; i <= j; i++) {
			bars[i]->setColor(in);
		}
	};
	void BarArray ::resetColor(int i) {
		bars[i]->resetColor();
	};
	void BarArray ::resetColor(int i, int j) {
		for (i = i; i <= j; i++) {
			bars[i]->resetColor();
		}
	};
	void BarArray::setDefaultColor(Color in, int _i) {
		bars[_i]->setDefaultColor(in);
		resetColor(_i);
	};
	void BarArray::setDefaultColor(Color in, int _i, int _j) {
		int i = _i < _j ? _i : _j;
		int j = _i > _j ? _i : _j;

		for (i = i; i <= j; i++)
			setDefaultColor(in, i);
		resetColor(i, j);
	};

	void NodeBox::update(float deltatime, InputState &input) {
		if (bind != nullptr) { // 实现与外部变量绑定
			if (bindType == 'i') {
				tag->setContent( to_string( *(int*)bind ));
			} else if (bindType == 'x')	{
				tag->setContent( to_string( *(long long*)bind ));
			} else if (bindType == 'f')	{
				tag->setContent( util::Format("{0}", *(float*)bind));
			} else if (bindType == 'd')	{
				tag->setContent( util::Format("{0}", *(double*)bind) );
			}
		}

		size.update(deltatime);
		position.update(deltatime); // 更新位置的动画
		color.update(deltatime); //更新颜色

		if (parent != nullptr) // 从父对象更新渲染位置
			global_position = (parent->getGlobalPosition()) + position();
		else
			global_position = position();

		for (auto child : children ) { // 进一步调用子对象的update()
			child->update(deltatime, input);
		}
	}

	void NodeBox::draw(Render& render) {
		if (display == 0) {
			for (auto child : children ) { // 进一步调用子对象的draw()
				child->draw(render);
			}
			return;
		}
		auto _size = size();
		render.drawRect(global_position - Vector2(0.5f * _size, 0.5f * _size), Vector2(_size * 1.4f, _size),
		                color());
		render.drawRectBorder(global_position - Vector2(0.5f * _size, 0.5f * _size), Vector2(_size, _size),
		                      color().mix("#FFFFFF", 0.5f), size() * 0.05f);
		render.drawRectBorder(global_position - Vector2(_size * -0.45f, 0.5f * _size), Vector2(_size * 0.45f, _size),
		                      color().mix("#FFFFFF", 0.5f), size() * 0.05f);

		if (pointer != nullptr) {
			void* pointer_to = *pointer;
			if (pointer_to != nullptr) {
				if (bind_map.count(pointer_to)) {
					auto start = global_position - Vector2(_size * -0.7f, 0);
					auto &vec = bind_map[pointer_to];
					for (Object* objp : vec) {
						render.drawArrow(start,
						                 objp->getPointedPos(start), "white");
					}
				}
			}
		}

		for (auto child : children ) { // 进一步调用子对象的draw()
			child->draw(render);
		}
	}

	void NodeBox::debug_draw(Render& render) {
		for (auto child : children ) { // 进一步调用子对象的debug_draw()
			child->debug_draw(render);
		}
	}

	Vector2 NodeBox::getPointedPos(Vector2 from) {
		return calcRadiusRectEnd(global_position,
		                         global_position + Vector2(size() * 0.9f, size() * 0.5f),
		                         global_position - Vector2(size() * 0.5f, size() * 0.5f),
		                         from - global_position
		                        );
	}
}

