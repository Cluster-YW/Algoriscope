#ifndef RENDER_H
#define RENDER_H

#include "shader.h"
#include "vector2.h"
#include "color.h"

namespace Algoriscope {
	class Render {
	private:
		vector2 size;//画布/场景尺寸
	public:
		//构造函数，进行相关初始化。
		Render() {
			glfwInit();
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			glfwWindowHint(GLFW_RESIZABLE,GL_FALSE);
			int screen_width = 1280;int screen_height = 720;
			auto window = glfwCreateWindow(screen_width, screen_height, "Computer Graphics",nullptr, nullptr);
			glfwMakeContextCurrent(window);
			glewExperimental = true;
			glViewport(0, 0, screen_width, screen_height);
			
		}
		
		//析构函数，进行收尾工作
		~Render() {
			glDeleteVertexArrays(1,&vertex_array_object);
			glDeleteBuffers(1,&vertex_buffer_object);
			glfwTerminate();
			return 0;
		}
		//负责帧的更新
		int update() {
			glClearColor(0.0f,0.0f,0.0f,1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			
			
			
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
		
		//检测按键是否按下
		//key - 按下哪个键
		//options - 检测功能键（如ctrl,shift）等
		bool isKeyDown(const char& key, const char* options = "") const {
			
		}
		
		//画直线
		//pos1 - 起点位置
		//pos2 - 终点位置
		//color - 线的颜色
		int drawLine(const vector2& pos1, const vector2& pos2, const color& col) {
			float line[] = {
				pos1.x,,pos2.y,0.0f,
				pos2,0.0f,
			};
		}
		
		//画三角形
		//3个点+颜色
		int drawTri(const vector2& pos1, const vector2& pos2, const vector2& pos3, const color& col) {
			
		}
		
		//画矩形
		// pos - 起始点
		// size - 尺寸（宽和高）
		// color - 颜色
		int drawRect(const vector2& pos, const vector2& size, const color& col) {
			
		}
		
		int drawText(const vector2& pos, const char*)
		
	};
}

#endif
