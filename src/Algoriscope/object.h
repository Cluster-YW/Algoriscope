#ifndef OBJECT_H
#define OBJECT_H
<<<<<<< HEAD
#include"render.h"
#include<vector>
#include"dynamics.h"

namespace Algoriscope {
	class Object {
	public:
	    Vector2 pos{Vector2(0,-0.5)};
		Vector2 golbalpos;
		vector<Object*>sons;
		int Draw(Render&render)
		{return 0;};
	};
	class Bar:public Object{
		public:
		int h,r;
		Vector2 size{Vector2 (0.05,0.05)};
		Vector2 unit{Vector2 (0.05,0.05)};
		Color color[2]{Color("FF0000"),Color("00FF00")};
		Bar(int h=0);
		int Set(int h);
	    int Draw(Render&render);
	};
	class Bars:public Object{
		public:
		int n;
		vector<Bar*>bars;
		Bars(int*arr,int n);
		int Draw(Render&render);
=======

namespace Algoriscope {
	class Object {
		public:
		private:

>>>>>>> 840ed39b2fbc8c7a772eb5af67975486e45b7dab
	};
}

#endif
