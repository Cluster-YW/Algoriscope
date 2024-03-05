#ifndef DYNAMICS_H
#define DYNAMICS_H

#include "vector2.h"
#include "color.h"
#include <string>

namespace Algoriscope {
	// 动画解算类：
	// 一个值，以 float 作为输入，每帧调用一遍 update() 函数
	// 可以通过 dnm=f 直接输入
	// 可以通过 dnm() 或 dnm.get() 获取动画处理后的输出量
	// 可以通过 f=dnm() 或 dnm(f) 直接把输出量赋给外部变量
	// 可以通过 dnm.set() 强制性地同时修改输入、输出量，并将运动的速度归零
	//
	// 三个运动学参数解读：
	// f	固有频率(Hz)	对变化的响应速度与震动的频率
	// z(ζ)	阻尼系数 		无阻尼 = 0 < 震荡 < 1 < 不震动
	// r	初始响应 		提前准备 < 0 < 立即响应 < 1 < 过度响应
	class Dynamics {
		public:
			Dynamics(float x0 = 0.0f, float f = 1.0f, float z = 1.0f, float r = 1.0f);
			//重载赋值运算符，直接修改输入值。
			float operator=(float f);
			//重载括号运算符，直接返回处理后的值。
			float operator()(void);
			//重载括号运算符，修改括号内的变量为处理后的值，返回处理后的值。
			float operator()(float &f);
			//更新函数，应当每帧调用一次。
			void update(float T);
			//设定运动学参数
			void setFZR(float f = 1.0f, float z = 1.0f, float r = 1.0f);
			//获取处理后的值
			float get();
			//强制输入，会一并修改处理后的值，并将动画速度直接归零
			float set(float f);
		private:
			float input;
			float x0;
			float y0;
			float Dy0;
			float k1, k2, k3; //三个方程系数
	};
	//二维动画解算类：
	//一个值，以 Vector2 作为输入，每帧调用一遍 update() 函数
	//类的方法与Dynamics相同
	class Dynamics2 {
		public:
			Dynamics2(float x0 = 0.0f, float y0 = 0.0f, float f = 1.0f, float z = 1.0f, float r = 1.0f);
			Dynamics2(Vector2 v, float f = 1.0f, float z = 1.0f, float r = 1.0f);
			//重载赋值运算符，直接修改输入值。
			Vector2 operator=(Vector2 f);
			//重载括号运算符，直接返回处理后的值。
			Vector2 operator()(void);
			//重载括号运算符，修改括号内的变量为处理后的值，返回处理后的值。
			Vector2 operator()(Vector2 &f);
			//更新函数，应当每帧调用一次。
			void update(float T);
			//设定运动学参数
			void setFZR(float f = 1.0f, float z = 1.0f, float r = 1.0f);
			//获取处理后的值
			Vector2 get();
			//获取目标值
			Vector2 getInput();
			//强制输入，会一并修改处理后的值，并将动画速度直接归零
			Vector2 set(Vector2 f);
		private:
			Vector2 input;
			Vector2 x0;
			Vector2 y0;
			Vector2 Dy0;
			float k1, k2, k3; //三个方程系数
	};
	class DynamicC {
		public:
			DynamicC(std::string c, float _k = 0.3f) : input(c), output(c), k(_k) {}
			DynamicC(Color c, float _k = 0.3f) : input(c), output(c), k(_k) {}
			//重载赋值运算符，直接修改输入值。
			Color operator=(Color f);
			//重载括号运算符，直接返回处理后的值。
			Color operator()(void);
			//重载括号运算符，修改括号内的变量为处理后的值，返回处理后的值。
			Color operator()(Color &f);
			//更新函数，应当每帧调用一次。
			void update(float T);
			//设定变化参数
			void setK(float _k = 0.3f);
			//获取处理后的值
			Color get();
			//强制输入，会一并修改处理后的值，并将动画速度直接归零
			Color set(Color f);

		private:
			Color input;
			Color output;
			float k;
	};
}
#endif
