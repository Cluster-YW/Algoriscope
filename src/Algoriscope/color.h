#ifndef _COLOR_H_
#define _COLOR_H_

#include <algorithm>
#include <iostream>
#include <string>

namespace Algoriscope {


	class Color {
		private:
			int r, g, b, a;
			float rf, gf, bf, af;
			float h, s, l;
		public:
			Color(const char[]);
			Color(std::string str);
			Color(int r = 0, int g = 0, int b = 0, int a = 255);
		
			Color HSL(float h = 0, float s = 0, float l = 0);

			void SetR(int r) {
				this->r = r;
				calcF();
				switchfromRGBtoHSL();
			};
			void setG(int g) {
				this->g = g;
				calcF();
				switchfromRGBtoHSL();
			};
			void setB(int b) {
				this->b = b;
				calcF();
				switchfromRGBtoHSL();
			};
			void setA(int a) {
				this->a = a;
				calcF();
				switchfromRGBtoHSL();
			};
			void SetH(int h) {
				this->h = h;
				switchfromHSLtoRGB();
				calcF();
			};
			void SetS(int s) {
				this->s = s;
				switchfromHSLtoRGB();
				calcF();
			};
			void SetL(int l) {
				this->l = l;
				switchfromHSLtoRGB();
				calcF();
			};

			// Get函数
			int getR() const {
				return this->r;
			}
			int getG() const {
				return this->g;
			}
			int getB() const {
				return this->b;
			}
			int getA() {
				return this->a;
			}
			float getH() {
				return this->h;
			}
			float getS() {
				return this->s;
			}
			float getL() {
				return this->l;
			}
			// rgba标准化函数
			float getRf()const {
				return rf;
			}
			float getGf()const {
				return gf;
			}
			float getBf()const {
				return bf;
			}
			float getAf()const {
				return af;
			}

			Color lerp(Color target, float k); // RGB 线性插值
			Color mix(Color target, float k); // HSL 色相插值
		private:
			void trimRGBA();
			void trimHSL();
			void switchfromRGBtoHSL();
			void switchfromHSLtoRGB();
			void calcF();
	};

}

#endif
