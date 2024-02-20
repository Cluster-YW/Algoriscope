#include "object.h"
#include "render.h"
namespace Algoriscope {
	Bar::Bar(int h) {
		this->h = h;
		size.y = unit.y * h;
	}
	int Bar::Set(int h) {
		this->h = h;
		size.y = unit.y * h;
		return 0;
	}
	int Bar::Draw(Render&render) {
		render.drawRect(pos, size, color[r]);
		return 0;
	}
	Bars::Bars(int *arr, int n) {
		this->n = n;
		for (int i = 0; i < n; i++)bars[i]->Set(*(arr + i));
	}
	int Bars::Draw(Render&render) {
		for (int i = n - 1; i > 0; i--) {
			for (int j = 0; j < i; j++) {
				if (bars[i]->h >= bars[j]->h)bars[i]->r = 0;
				else break;
				if (i == j + 1)bars[i]->r = 1;
			};
			if (bars[i]->r == 0)break;
			if (i == 1 && bars[1]->r == 1)bars[0]->r = 1;
		};
		for (int i = 0; i < n; i++) {
			bars[i]->Draw(render);
			render.update();
		};
		return 0;
	}

}


