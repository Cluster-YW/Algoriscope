#include "array.h"

namespace Algoriscope {

	void BarArray::update(float deltatime, InputState &input) {
		position.update(deltatime); // 更新位置的动画
		gap.update(deltatime);

		int n =	elements.size();
		float gap_ = gap();

		for (int i = 0; i < n; i++) {
			if (align.find_first_of("l") != string::npos) {
				Vector2 bpos( gap_ * i + elements[i]->getWidth() * 0.5f, 0);
				elements[i]->setPosition(bpos);
			} else if (align.find_first_of("c") != string::npos) {
				Vector2 bpos( gap_ * (i - (n - 1) * 0.5f), 0);
				elements[i]->setPosition(bpos);
			} else if (align.find_first_of("r") != string::npos) {
				Vector2 bpos(-gap_ * i - elements[i]->getWidth() * 0.5f, 0);
				elements[i]->setPosition(bpos);
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
		elements[i]->setColor(in);
	};
	void BarArray ::setColor(Color in, int _i, int _j) {
		int i = _i < _j ? _i : _j;
		int j = _i > _j ? _i : _j;
		for (i = i; i <= j; i++) {
			elements[i]->setColor(in);
		}
	};
	void BarArray ::resetColor(int i) {
		elements[i]->resetColor();
	};
	void BarArray ::resetColor(int i, int j) {
		for (i = i; i <= j; i++) {
			elements[i]->resetColor();
		}
	};
	void BarArray::setDefaultColor(Color in, int _i) {
		elements[_i]->setDefaultColor(in);
		resetColor(_i);
	};
	void BarArray::setDefaultColor(Color in, int _i, int _j) {
		int i = _i < _j ? _i : _j;
		int j = _i > _j ? _i : _j;

		for (i = i; i <= j; i++)
			setDefaultColor(in, i);
		resetColor(i, j);
	};
	void BarArray::resetDefaultColor(Color in, int _i) {
		elements[_i]->resetDefaultColor(in);
	};
	void BarArray::resetDefaultColor(Color in, int _i, int _j) {
		int i = _i < _j ? _i : _j;
		int j = _i > _j ? _i : _j;
		
		for (i = i; i <= j; i++)
			resetDefaultColor(in, i);
	};

	void BoxArray::update(float deltatime, InputState &input) {
		position.update(deltatime); // 更新位置的动画

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
	void BoxArray::draw(Render & render) {
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
	void BoxArray::debug_draw(Render & render) {
		for (auto child : children ) { // 进一步调用子对象的debug_draw()
			child->debug_draw(render);
		}
	}
	void BoxArray ::setColor(Color in, int i) {
		elements[i]->setColor(in);
	};
	void BoxArray ::setColor(Color in, int _i, int _j) {
		int i = _i < _j ? _i : _j;
		int j = _i > _j ? _i : _j;
		for (i = i; i <= j; i++) {
			elements[i]->setColor(in);
		}
	};
	void BoxArray ::resetColor(int i) {
		elements[i]->resetColor();
	};
	void BoxArray ::resetColor(int i, int j) {
		for (i = i; i <= j; i++) {
			elements[i]->resetColor();
		}
	};
	void BoxArray::setDefaultColor(Color in, int _i) {
		elements[_i]->setDefaultColor(in);
	};
	void BoxArray::setDefaultColor(Color in, int _i, int _j) {
		int i = _i < _j ? _i : _j;
		int j = _i > _j ? _i : _j;
		
		for (i = i; i <= j; i++)
			setDefaultColor(in, i);
	};
	void BoxArray::resetDefaultColor(Color in, int _i) {
		elements[_i]->resetDefaultColor(in);
	};
	void BoxArray::resetDefaultColor(Color in, int _i, int _j) {
		int i = _i < _j ? _i : _j;
		int j = _i > _j ? _i : _j;
		
		for (i = i; i <= j; i++)
			resetDefaultColor(in, i);
	};
}
