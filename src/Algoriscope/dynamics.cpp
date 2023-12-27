#include "dynamics.h"
#include <algorithm>
#define PI (3.1415926)
namespace Algoriscope {
	Dynamics::Dynamics(float x0, float f, float z, float r) {
		input = y0 = (this->x0) = x0;
		Dy0 = 0;
		setFZR(f, z, r);
	}
	void Dynamics::setFZR(float f, float z, float r) {
		k1 = z / (PI * f);
		k2 = 1 / ((2 * PI * f) * (2 * PI * f));
		k3 = r * z / (2 * PI * f);
	}
	float Dynamics::update(float T) {
		float x1 = input;
		float k2_stable = std::max(k2, (float)1.1 * (T * T / 4 + T * k1 / 2));
		float Dx1 = (x1 - x0) / T;
		float y1 = y0 + Dy0 * T;
		float Dy1 = Dy0 + T * (x1 + k3 * Dx1 - y1 - k1 * Dy0) / k2_stable;
		x0 = x1;
		y0 = y1;
		Dy0 = Dy1;
		return y0;
	}
	float Dynamics::operator=(float f) {
		input = f;
		return input;
	}
	float Dynamics::operator()(void) {
		return y0;
	}
	float Dynamics::operator()(float &f) {
		f = y0;
		return y0;
	}
	float Dynamics::get() {
		return y0;
	}
	float Dynamics::set(float f) {
		Dy0=0;
		return input=x0=y0=f;
	}

	Dynamics2::Dynamics2(float x0, float y0, float f, float z, float r) {
		input = (this->y0) = (this->x0) = Vector2(x0, y0);
		Dy0 = Vector2(0.0f, 0.0f);
		setFZR(f, z, r);
	}
	Dynamics2::Dynamics2(Vector2 v, float f, float z, float r) {
		input = (this->y0) = (this->x0) = v;
		Dy0 = Vector2(0.0f, 0.0f);
		setFZR(f, z, r);
	}
	void Dynamics2::setFZR(float f, float z, float r) {
		k1 = z / (PI * f);
		k2 = 1 / ((2 * PI * f) * (2 * PI * f));
		k3 = r * z / (2 * PI * f);
	}
	Vector2 Dynamics2::update(float T) {
		Vector2 x1 = input;
		float k2_stable = std::max(k2, (float)1.1 * (T * T / 4 + T * k1 / 2));
		Vector2 Dx1 = (x1 - x0) / T;
		Vector2 y1 = y0 + Dy0 * T;
		Vector2 Dy1 = Dy0 + T * (x1 + k3 * Dx1 - y1 - k1 * Dy0) / k2_stable;
		x0 = x1;
		y0 = y1;
		Dy0 = Dy1;
		return y0;
	}
	Vector2 Dynamics2::operator=(Vector2 f) {
		input = f;
		return input;
	}
	Vector2 Dynamics2::operator()(void) {
		return y0;
	}
	Vector2 Dynamics2::operator()(Vector2 &f) {
		f = y0;
		return y0;
	}
	Vector2 Dynamics2::get() {
		return y0;
	}
	Vector2 Dynamics2::set(Vector2 f) {
		Dy0=Vector2(0,0);
		return input=x0=y0=f;
	}
}
