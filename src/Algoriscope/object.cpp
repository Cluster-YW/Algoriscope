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
//		std::string posinfo;
//		posinfo = "(" + std::to_string((int)global_position.x) +
//		          "," + std::to_string((int)global_position.y) + ")";
//		render.drawText(global_position + Vector2(0, -20), 0.3f, posinfo, Color("#00FF00"));


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
			setHeight( *bind * scale());
		}

		position.update(deltatime); // 更新位置的动画
		width.update(deltatime); // 更新宽度
		height.update(deltatime); // 更新高度

		if (parent != nullptr) // 从父对象更新渲染位置
			global_position = (parent->getGlobalPosition()) + position();
		else
			global_position = position();

		for (auto child : children ) { // 进一步调用子对象的update()
			child->update(deltatime);
		}

	}
	void Bar::draw(Render& render) {
		Vector2 draw_position = global_position + Vector2(-width() * 0.5f, 0);

		if (height() < 0) { // 实现高度为负，向下绘制
			draw_position = draw_position + Vector2(0, height());
			render.drawRect(draw_position,
			                Vector2(width(), -height()), Color("blue"));
			render.drawRectBorder(draw_position,Vector2(width(), -height()),Color("yellow"),3);
		} else {
			render.drawRect(draw_position,
			                Vector2(width(), height()), Color("red"));
			render.drawRectBorder(draw_position,Vector2(width(), height()),Color("yellow"),3);
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
		render.drawText(global_position + Vector2(0, -20), 0.3f, posinfo, Color("#00FFFF"));

		std::string sizeinfo;
		sizeinfo = "(" + std::to_string((int)width()) +
		           "," + std::to_string((int)height()) + ")";
		render.drawText(global_position + Vector2(0, -40), 0.3f, sizeinfo, Color("#00FFFF"));


		for (auto child : children ) { // 进一步调用子对象的debug_draw()
			child->debug_draw(render);
		}
	}
}

