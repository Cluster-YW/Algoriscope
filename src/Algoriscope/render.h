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
		Shader shader;
		
	public:
		//构造函数，进行相关初始化。
		Render(int sizex, int sizey);
		
		int setTitle(const char* name);
		
		//析构函数，进行收尾工作
		~Render();
		//负责帧的更新
		int update(const Color& col);
		
		//检测按键是否按下
		//key - 按下哪个键
		//options - 检测功能键（如ctrl,shift）等
		bool isKeyDown(const char& key, const char* options = " ") const ;
		
		//画直线
		//pos1 - 起点位置
		//pos2 - 终点位置
		//color - 线的颜色
		int drawLine(const Vector2& pos1, const Vector2& pos2, const Color& col);
		
		//画三角形
		//3个点+颜色
		int drawTri(const Vector2& pos1, const Vector2& pos2, const Vector2& pos3, const Color& col) ;
		
		//画矩形
		// pos - 起始点
		// size - 尺寸（宽和高）
		// color - 颜色
		int drawRect(const Vector2& pos, const Vector2& size, const Color& col) ;
		
		int drawRectBorder(const Vector2& pos,const Vector2&size,const Color&col,const float width);
		
		int drawCircle(Vector2 pos,GLfloat r,Color col);
		
		int drawText(Vector2 pos,GLfloat scale,string text,Color iColor);
		
		GLFWwindow* getw(){
			return window;
		}
	};
}
#endif
