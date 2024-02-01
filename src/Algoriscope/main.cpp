#include "render.h"
#include "object.h"
#include <iostream>
using namespace Algoriscope;
int main() {
	Render render(1500,1500);
	int arr[6]={1,2,4,3,5,6};
	int arr1[6]={1,2,3,7,5,6};
	Object a(arr,6);
	a.set(arr1,6);
	while (1) {
		a.DrawBar(render);
		render.update();
	}
}
