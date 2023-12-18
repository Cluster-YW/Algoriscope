#include "color.h"

using namespace Algoriscope;
Color::Color(const char* RGB) {
	int arr[7] = {0};
	for (int i = 1; i < 7; i++) {
		if (*(RGB + i) > 64 && *(RGB + i) < 72)arr[i] = *(RGB + i) - 55;
		else if (*(RGB + i) > 47 && *(RGB + i) < 58)  arr[i] = *(RGB + i) - 48;
	}
	r = arr[1] * 16 + arr[2];
	g = arr[3] * 16 + arr[4];
	b = arr[5] * 16 + arr[6];
	a = 255;
	trimRGBA();
	switchfromRGBtoHSL();
};

Color::Color(int r, int g, int b, int a) {
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
	trimRGBA();
	switchfromRGBtoHSL();
};
Color::Color(float h, float s, float l) {
	this->h = h;
	this->s = s;
	this->l = l;
	trimHSL();
	switchfromHSLtoRGB();
};
void Color::trimRGBA() {
	if (r > 255)this->r = 255;
	else if (r < 0)this->r = 0;
	else this->r = r;
	if (g > 255)this->g = 255;
	else if (g < 0)this->g = 0;
	else this->g = g;
	if (b > 255)this->b = 255;
	else if (b < 0)this->b = 0;
	else this->b = b;
	if (a > 255)this->a = 255;
	else if (a < 0)this->r = 0;
	else this->a = a;
};
void Color::trimHSL() {
	while (h > 360 || h < 0) {
		if (h > 360)this->h = h - 360;
		else if (h < 0)this->h = h + 360;
		else this->h = h;
	};
	if (s > 1.0)this->s = 1.0;
	else if (s < 0)this->s = 0;
	else this->s = s;
	if (l > 1.0)this->l = 1.0;
	else if (l < 0)this->l = 0;
	else this->l = l;
}
void Color::switchfromRGBtoHSL() {
	float max, min;
	float _r = this->getRf();
	float _g = this->getGf();
	float _b = this->getBf();
	max = std::max({_r, _g, _b});
	min = std::min({_r, _g, _b});
	std::cout << max << "-" << min << std::endl;
	//计算L
	l = (max + min) / 2;
	//计算S
	if (max == min)s = 0;
	else if (l < 0.5)s = (max - min) / (max + min);
	else s = (max - min) / (2 - max - min);
	//计算H
	if (max == min) {
		h = 0.0f;
	} else {
		if (_r == max)h = (_g - _b) / (max - min);
		else if (_g == max)h = 2.0 + (_b - _r) / (max - min);
		else h = 4.0 + (_r - _g) / (max - min);
		h = h * 60;
		if (h < 0)h += 360;
	}
}
void Color::switchfromHSLtoRGB() {
	float temp2, temp1, _h, arr[3] = {0};
	if (s == 0)r = g = b = l * 255;
	else {
		if (l < 0.5)temp2 = l * (1.0 + s);
		else temp2 = l + s - l * s;
		temp1 = 2.0 * l - temp2;
		_h = h / 360;
		arr[0] = _h + 1.0 / 3.0;
		arr[1] = _h;
		arr[2] = _h - 1.0 / 3.0;
		for (int i = 0; i < 3; i++) {
			while (arr[i] > 1 || arr[i] < 0) {
				if (arr[i] > 1)arr[i] -= 1;
				else if (arr[i] < 0)arr[i] += 1;
				else break;
			};
			if (6.0 * arr[i] < 1)arr[i] = temp1 + (temp2 - temp1) * 6.0 * arr[i];
			else if (2.0 * arr[i] < 1)arr[i] = temp2;
			else if (3.0 * arr[i] < 2)arr[i] = temp1 + (temp2 - temp1) * ((2.0 / 3.0) - arr[i]) * 6.0;
			else arr[i] = temp1;

		}
		r = arr[0] * 255;
		g = arr[1] * 255;
		b = arr[2] * 255;
	}
}
