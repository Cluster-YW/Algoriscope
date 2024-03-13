#include "color.h"

using namespace Algoriscope;

Color::Color(const char* c) {
	std::string str = c;
	if (str[0] != '#') {
		if (str == "white") str = "#FFFFFF";
		else if (str == "black") str = "#000000";
		else if (str == "darkgrey") str = "#222222";
		else if (str == "lightgrey")str = "#AAAAAA";
		else if (str == "red") 		str = "#EE4444";
		else if (str == "blue") 	str = "#5588EE";
		else if (str == "green") 	str = "#66EE88";
		else if (str == "yellow") 	str = "#FFDD66";
		else if (str == "orange")	str = "#EEAA44";
		else if (str == "darkred") 		str = "#701010";
		else if (str == "darkblue") 	str = "#103060";
		else if (str == "darkgreen") 	str = "#206030";
		else if (str == "darkyellow") 	str = "#707010";
	}
	int arr[7] = {0};
	for (int i = 1; i < 7; i++) {
		if (str[i] > 64 && str[i]  < 72)arr[i] = str[i]  - 55;
		else if (str[i] > 47 && str[i]  < 58)  arr[i] = str[i]  - 48;
	}
	r = arr[1] * 16 + arr[2];
	g = arr[3] * 16 + arr[4];
	b = arr[5] * 16 + arr[6];
	a = 255;
	trimRGBA();
	calcF();
	switchfromRGBtoHSL();
};

Color::Color(std::string str) {
	if (str[0] != '#') {
		if (str == "darkgrey") str = "#222222";
		if (str == "lightgrey")str = "#AAAAAA";
		if (str == "red") 		str = "#EE4444";
		if (str == "blue") 	str = "#5588EE";
		if (str == "green") 	str = "#66EE88";
		if (str == "yellow") 	str = "#FFDD66";
	}
	int arr[7] = {0};
	for (int i = 1; i < 7; i++) {
		if (str[i] > 64 && str[i]  < 72)arr[i] = str[i]  - 55;
		else if (str[i] > 47 && str[i]  < 58)  arr[i] = str[i]  - 48;
	}
	r = arr[1] * 16 + arr[2];
	g = arr[3] * 16 + arr[4];
	b = arr[5] * 16 + arr[6];
	a = 255;
	trimRGBA();
	calcF();
	switchfromRGBtoHSL();
};

Color::Color(int r, int g, int b, int a) {
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
	trimRGBA();
	calcF();
	switchfromRGBtoHSL();
};
Color Color::HSL(float h, float s, float l) {
	Color col;
	col.h = h;
	col.s = s;
	col.l = l;
	col.trimHSL();
	col.switchfromHSLtoRGB();
	col.calcF();
	return col;
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
	else if (a < 0)this->a = 0;
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
	float _r = rf;
	float _g = gf;
	float _b = bf;
	max = std::max({_r, _g, _b});
	min = std::min({_r, _g, _b});
//	std::cout << max << "-" << min << std::endl;
//	计算L
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
void Color::calcF() {
	rf = r / 255.0f;
	gf = g / 255.0f;
	bf = b / 255.0f;
	af = a / 255.0f;
}
Color Color::lerp(Color target, float k) {
	auto ilerp = [](int a, int b, float k)->int{
		return (int)(a * (1 - k) + b * k);
	};
	return Color(ilerp(r, target.getR(), k),
	             ilerp(g, target.getG(), k),
	             ilerp(b, target.getB(), k),
	             ilerp(a, target.getA(), k));
}
Color Color::mix(Color target, float k) {
	if (target.getS() == 0) {
		target.SetH(h);
	}
	auto flerp = [](float a, float b, float k)->float{
		return (a * (1 - k) + b * k);
	};
	return Color::HSL(
	           flerp(h, target.getH(), k),
	           flerp(s, target.getS(), k),
	           flerp(l, target.getL(), k));
}
