#include "object.h"
#include "render.h"
namespace Algoriscope {
	Object::Object(int x) {
		this->n = 1;
		a.push_back(x);
	}
	Object::Object(int *arr, int n) {
		this->n = n;
		a.clear();
		for (int i = 0; i < n; i++) {
			a.push_back(*(arr + i));
		};
	}
	int Object::set(int*arr,int n){
	this->n = n;
		a.clear();
		for (int i = 0; i < n; i++) {
			a.push_back(*(arr + i));
		};
		return 0;
	}
	int Object::DrawObject(Render&render) {
		
		if (n == 1) {
			size.y = 0.05 * a[0];
			render.drawRect(pos, size, col[1]);
		} else if (n > 1)DrawBar(render);
		return 0;
	}
	int Object::DrawBar(Render&render) {
        int judge[n]={0};
		for (int i = n - 1; i > 0; i--) {
			for (int j = 0; j < i; j++) {
				if (a[i] >= a[j])judge[i] = 0;
				else break;
				if (i == j + 1)judge[i] = 1;
			};
			if (judge[i] == 0)break;
			if (i == 1 && judge[1] == 1)judge[0] = 1;
		};

		for (int i = 0; i < n; i++) {
			size.y = 0.05 * a[i];
			pos.x = -0.05 * n + 0.1 * i;
			render.drawRect(pos, size, col[judge[i]]);
		};
		return 0;
	}
	
}


