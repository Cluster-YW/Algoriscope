#ifndef _COLOR_H_
#define _COLOR_H_

#include <algorithm>
#include <iostream>

namespace Algoriscope {
	class Color {
		private:
			int r, g, b, a;
			float h, s, l;
		public:

			Color(const char* RGB);
			Color(int r = 0, int g = 0, int b = 0, int a = 255);
			Color(float h = 0, float s = 0, float l = 0);
		void Set(const char*RGB);
			void Set(int r) {
				this->r = r;
				switchfromRGBtoHSL();
			};
			void setG(int g) {
				this->g = g;
				switchfromRGBtoHSL();
			};
			void setB(int b) {
				this->b = b;
				switchfromRGBtoHSL();
			};
			void setA(int a) {
				this->a = a;
				switchfromRGBtoHSL();
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
				return this->r / 255.0f;
			}
			float getGf()const {
				return this->g / 255.0f;
			}
			float getBf()const {
				return this->b / 255.0f;
			}
			float getAf()const {
				return this->a / 255.0f;
			}
		private:
			void trimRGBA();
			void trimHSL();
			void switchfromRGBtoHSL();
			void switchfromHSLtoRGB();
	};

}

#endif
