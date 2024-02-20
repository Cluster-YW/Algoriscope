#include "render.h"
#include "object.h"
#include <iostream>
using namespace Algoriscope;
int main() {
	Render render(1500,1500);
	int arr[10]={1,2,3,4,5,8,7,8,9,10};
	Bar a(10);
	while (1) {
		a.Draw(render);
	}
}
