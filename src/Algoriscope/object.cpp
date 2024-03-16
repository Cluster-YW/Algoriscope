#include "object.h"
namespace Algoriscope {
	void Object::update(float deltatime) {

		position.update(deltatime); // 更新位置的动画

		if (parent != nullptr) // 从父对象更新渲染位置
			global_position = (parent->global_position) + position();
		else
			global_position = position();

		for (auto child : children ) { // 进一步调用子对象的update()
			child->update(deltatime);
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

	void Bar::update(float deltatime) {

		if (bind != nullptr) { // 实现与外部变量绑定
			float _scale = scale();
			float _width = width();
			if (bindType == 'i') {
				tag->setContent( to_string( *(int*)bind ));
				setHeight( *(int*)bind * _scale);
				tag->setPosition(Vector2(0, *(int*)bind * _scale + _width * 0.5f));
			} else if (bindType == 'x')	{
				tag->setContent( to_string( *(long long*)bind ));
				setHeight( *(long long*)bind * _scale);
				tag->setPosition(Vector2(0, *(long long*)bind * _scale + _width * 0.5f));
			} else if (bindType == 'f')	{
				tag->setContent( util::Format("{0}", *(float*)bind));
				setHeight( *(float*)bind * _scale);
				tag->setPosition(Vector2(0, *(float*)bind * _scale + _width * 0.5f));
			} else if (bindType == 'd')	{
				tag->setContent( util::Format("{0}", *(double*)bind) );
				setHeight( *(double*)bind * _scale);
				tag->setPosition(Vector2(0, *(double*)bind * _scale + _width * 0.5f));
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

		for (auto child : children ) { // 进一步调用子对象的update()
			child->update(deltatime);
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

	void Text::update(float deltatime) {
		size.update(deltatime);
		position.update(deltatime); // 更新位置的动画
		color.update(deltatime); //更新颜色

		if (parent != nullptr) // 从父对象更新渲染位置
			global_position = (parent->getGlobalPosition()) + position();
		else
			global_position = position();

		for (auto child : children ) { // 进一步调用子对象的update()
			child->update(deltatime);
		}
	}
	void Text::draw(Render& render) {
		if (display == 0) {
			for (auto child : children ) { // 进一步调用子对象的draw()
				child->draw(render);
			}
			return;
		}
		render.drawText(global_position, size(), content, color());
		for (auto child : children ) { // 进一步调用子对象的draw()
			child->draw(render);
		}
	}
	void Text::debug_draw(Render& render) {
		for (auto child : children ) { // 进一步调用子对象的debug_draw()
			child->debug_draw(render);
		}
	}

	void Box::update(float deltatime) {

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
			child->update(deltatime);
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
		render.drawRect(position() - 0.5f * Vsize, Vsize,
		                color());
		render.drawRectBorder(position() - 0.5f * Vsize, Vsize,
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

	void BarArray::update(float deltatime) {
		position.update(deltatime); // 更新位置的动画
		gap.update(deltatime);

		int n =	bars.size();
		float gap_ = gap();
	
		for (int i = 0; i < n; i++) {
			if(align.find_first_of("l") != string::npos){
				Vector2 bpos( gap_ * i +bars[i]->getWidth()*0.5f, 0);
				bars[i]->setPosition(bpos);
			}
			else if(align.find_first_of("r") != string::npos){
				Vector2 bpos( gap_ * (i -(n -1)*0.5f), 0);
				bars[i]->setPosition(bpos);
			}
		}
		if (parent != nullptr) // 从父对象更新渲染位置
			global_position = (parent->getGlobalPosition()) + position();
		else
			global_position = position();

		for (auto child : children ) { // 进一步调用子对象的update()
			child->update(deltatime);
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
}

