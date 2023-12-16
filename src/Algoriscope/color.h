#ifndef _COLOR_H_
#define _COLOR_H_

namespace Algoriscope {
	
	
	class Color {
	public:
		int r, g, b, a;
		float h, s, l;
		Color(const char* RGB);
		Color(int r = 0, int g = 0, int b = 0, int a = 255);
		Color(float h=0, float s=0, float l=0);
		void SetRed(int r) {
			this->r = r;
			SwitchfromRGBtoHSL();
		};
		void SetGreen(int g) {
			this->g = g;
			SwitchfromRGBtoHSL();
		};
		void SetBlue(int b) {
			this->b = b;
			SwitchfromRGBtoHSL();
		};
		void SetA(int a) {
			this->a = a;
			SwitchfromRGBtoHSL();
		};
	private:
		void Check1();
		void Check2();
		void SwitchfromRGBtoHSL();
		void SwitchfromHSLtoRGB();
		
		
	};
	
}

#endif
