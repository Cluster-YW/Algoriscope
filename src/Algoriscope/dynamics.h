#ifndef DYNAMICS_H
#define DYNAMICS_H

namespace Algoriscope {
	class Dynamics {
		public:
			Dynamics(float x0=0.0f, float f=1.0f, float z=1.0f, float r=1.0f);
			//重载赋值运算符，直接修改输入值
			float operator=(float f);
			//重载括号运算符，直接返回处理后的值
			float operator()(void);
			//重载括号运算符，修改括号内的变量
			float operator()(float &f);
			float update(float T);
			void setFZR(float f=1.0f, float z=1.0f, float r=1.0f);
			float get();
		private:
			float input;
			float x0;
			float y0;
			float Dy0;
			float k1, k2, k3; //三个方程系数
	};
}
#endif
