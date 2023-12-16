#ifndef ALGORISCOPE_VECTOR2_H
#define ALGORISCOPE_VECTOR2_H

namespace Algoriscope {


	class Color {
		public:
			int r, g, b;
			float a, h, s, l;
			Color(const char* RGB);
			Color(int r = 0, int g = 0, int b = 0, float a = 1.0);
			Color(float h=0, float s=0, float l=0);
			void SetRed(int r) {
				this->r = r;
				void SwitchfromRGBtoHSL();
			};
			void SetGreen(int g) {
				this->g = g;
				void SwitchfromRGBtoHSL();
			};
			void SetBlue(int b) {
				this->b = b;
				void SwitchfromRGBtoHSL();
			};
			void SetA(float a) {
				this->a = a;
			};
		private:
			void Check1();
			void Check2();
			void SwitchfromRGBtoHSL();
			void SwitchfromHSLtoRGB();


	};
	
}

#endif
