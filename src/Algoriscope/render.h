#ifndef RENDER_H
#define RENDER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <map>
#include <ft2build.h>
#include FT_FREETYPE_H 


#include "shader.h"
#include "vector2.h"
#include "color.h"

namespace Algoriscope {
	class Render {
	private:
		Vector2 size;// 画布/场景尺寸
		GLFWwindow* window;// 窗口对象
		Shader shader;//着色器
		
	public:
		
		//**渲染循环里先绘制图形再绘制文字
		
		//构造函数，进行相关初始化。
		Render(int sizex, int sizey);
		
		//设置标题
		int setTitle(const char* name);
		
		//析构函数，进行收尾工作
		~Render();
		
		//负责帧的更新
		//col - 背景色
		int update(const Color& col);
		
		//检测按键是否按下
		//key - 按下哪个键
		//options - 检测功能键（如ctrl,shift）等
		bool isKeyDown(const char& key, const char* options = " ") const ;
		
		//画直线
		//pos1 - 起点位置
		//pos2 - 终点位置
		//color - 线的颜色
		//width - 线条宽度
		int drawLine(const Vector2& pos1, const Vector2& pos2, const Color& col, const float width=10);
		
		//画三角形
		//3个点+颜色
		int drawTri(const Vector2& pos1, const Vector2& pos2, const Vector2& pos3, const Color& col) ;
		
		//画矩形
		// pos - 起始点 (左下角点)
		// size - 尺寸（宽和高）
		// color - 颜色
		int drawRect(const Vector2& pos, const Vector2& size, const Color& col) ;
		
		//画矩形框
		// pos - 起始点 (左下角点)
		// size - 尺寸（宽和高）
		// color - 颜色
		// width - 线条宽度
		int drawRectBorder(const Vector2& pos,const Vector2& size,const Color& col,const float width);
		
		//画点
		//pos - 位置
		//col - 颜色
		//size - 大小
		int drawPoints(const Vector2& pos,const Color& col,const float size);
		
		//渲染文字
		//pos - 左下位置
		//scale - 字体高度
		//text - 文字内容
		//iColor - 文字颜色
		int drawText(Vector2& pos,GLfloat scale,string text,Color iColor);
		
		
		
		GLFWwindow* getw(){
			return window;
		}
	};
}
#endif
