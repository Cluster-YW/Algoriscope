#ifndef OBJECT_H
#define OBJECT_H
#include"render.h"
#include<vector>

namespace Algoriscope {
	class Object {
	public:
		vector<int>a;
		int n=0;
		Vector2 pos{Vector2 (0,-0.5)};//原点
		Vector2 size{Vector2(0.05,0)};//
		Vector2 unit{Vector2(0.05,0.05)};//单位
		Color col[2]{("#FF0000"),("#00FF00")};
		//定义数据，arr为数组名，n为数据个数
		Object(int*arr,int n);
		Object(int x);
		int set(int*arr,int n);
		int DrawObject(Render&render);
		int DrawBar(Render&render);
		
	};	
}

#endif
