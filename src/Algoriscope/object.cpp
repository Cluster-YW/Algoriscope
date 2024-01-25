#include "object.h"
#include "render.h"
namespace Algoriscope {
	Object::Object(int *arr, int n) {
		this->n = n;
		for (int i = 0; i < n; i++) {
			a.push_back(*(arr + i));
		};
	}
	int Object::DrawBar() {
		for (int i = 0; i < n; i++) {
			size.y = 0.05 * a[i];
			pos.x = -0.05 + 0.1 * n;
			drawRect(pos, size, col);
		};
		return 0;
	}
}


