#ifndef ALGORISCOPE_VECTOR2_H
#define ALGORISCOPE_VECTOR2_H

namespace Algoriscope {


	class Color  
	{
		public:
		    int r,g,b;
		    float a;
		    Color(const char* RGB);
		    Color(int r=0,int g=0,int b=0,float a =1.0);
		    void SetRed(int r)
		     {this->r=r;};
	        void SetGreen(int g)
		     {this->g=g;};
		    void SetBlue(int b)
		    {this->b=b;};
		     void SetA(float a)
		    {this->a=a;};
	    private:
		    void Check();


	};
	Color::Color(const char* RGB) {
		int arr[7]={0};
		for(int i=1;i<7;i++)
		{if(*(RGB+i)>64&&*(RGB+i)<72)arr[i] =*(RGB+i)-55;
		else if(*(RGB+i)>47&&*(RGB+i)<58)  arr[i]=*(RGB+i)-48;}
		r=arr[1]*16+arr[2];
		g=arr[3]*16+arr[4];
		b=arr[5]*16+arr[6];	
		Check();
	
	};

	Color::Color(int r,int g,int b,float a)
	{   this->r=r;
		this->g=g;  
		this->b=b;
		this->a=a;
	     Check();};
	void Color::Check()
	{if(r>255)this->r=255;
		else if(r<0)this->r=0;
		else this->r=r;
	if(g>255)this->g=255;
		else if(g<0)this->g=0;
		else this->g=g;
	if(b>255)this->b=255;
		else if(b<0)this->b=0;
		else this->b=b;
	if(a>1.0)this->a=1.0;
		else if(a<0)this->r=0;
		else this->a=a;};
}

#endif
