#ifndef ALGORISCOPE_DYNAMICS_H
#define ALGORISCOPE_DYNAMICS_H

#ifndef PI
	#define PI    (3.1415926f)
	#define invPI (0.3183098f)
#endif
namespace Algoriscope {
	class Dynamics {
			double value;
			double x0;
			double y0, Dy0;
			double f, z, r;
			//f - 固有频率
			//z - 阻尼参数
			//r - 响应参数
			double k1, k2, k3;
			void calculateK();
			//通过 f、z、r 三个参数得到具体的计算参数 k1、k2、k3
		public:
			Dynamics();
			Dynamics(double _x0);
			Dynamics(double _x0, double _f, double _z, double _r);
			int update(double T);
			// 应当每帧执行Update()函数
			// 更新一步，x1 为输入值，T 为时间步长
			// 返回 1 表示时间步长超出系统稳定的阈值，自动增加k2以保持稳定
			void setValue(double x);
			// 直接设定原始值 x0 ，而不更新输出值 y0
			double getValue();
			//读取输出值
			void setPara(double _f, double _z, double _r);
			//修改运动学参数
	};
	void Dynamics::calculateK() {
		double invf = 1 / f;
		k1 = z * invPI * invf;
		k2 = 0.25f * invPI * invPI * invf * invf ;
		k3 = r * z * 0.5f * invPI * invf;
	}

	Dynamics::Dynamics() {
		x0 = y0 = Dy0 = 0;
		f = 2.0f;
		z = 1.0f;
		r = 0.5f;
		calculateK();
	}

	Dynamics::Dynamics(double _x0) {
		x0 = y0 = _x0;
		Dy0 = 0;
		f = 2.0f;
		z = 1.0f;
		r = 0.5;
		calculateK();
	}

	Dynamics::Dynamics(double _x0, double _f, double _z, double _r) {
		x0 = y0 = _x0;
		Dy0 = 0;
		f = _f;
		z = _z;
		r = _r;
		calculateK();
	}

	int Dynamics::update(double T) {
		double x1 = value;
		int ret = 0;
		double k2_stable = k2, k2_limit = 1.1f * (T * T * 0.25f + k1 * 0.5);
		if (k2 < k2_limit) {
			k2_stable = k2_limit;
			ret = 1;
		}
		double Dx1 = (x1 - x0) / T;
		double y1 = y0 + Dy0 * T;
		double Dy1 = Dy0 + T * (x1 + k2 * Dx1 - y1 - k1 * Dy0) / k2_stable;
		x0 = x1;
		y0 = y1;
		Dy0 = Dy1;
		return ret;
	}

	double Dynamics::getValue() {
		return y0;
	}

	void Dynamics::setPara(double _f, double _z, double _r) {
		f = _f;
		z = _z;
		r = _r;
		calculateK();
	}

	void Dynamics::setValue(double x) {
		value = x;
	}
}
#endif
