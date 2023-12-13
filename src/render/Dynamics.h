#pragma once

class Dynamics {
	double value;
	double x0;
	double y0, Dy0;
	double f, z, r;
	//f - 固有频率
	//z - 阻尼参数
	//r - 响应参数
	double k1, k2, k3;
	void Calculatek();
	//通过 f、z、r 三个参数得到具体的计算参数 k1、k2、k3
public:
	Dynamics();
	Dynamics(double _x0);
	Dynamics(double _x0, double _f, double _z, double _r);
	int Update(double T);
	// 应当每帧执行Update()函数
	// 更新一步，x1 为输入值，T 为时间步长
	// 返回 1 表示时间步长超出系统稳定的阈值，自动增加k2以保持稳定
	void SetValue(double x);
	// 直接设定原始值 x0 ，而不更新输出值 y0
	double GetValue();
	//读取输出值
	void SetPara(double _f, double _z, double _r);
	//修改运动学参数
};


