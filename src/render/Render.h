#ifndef ALGORISCOPE_RENDER_H_
#define ALGORISCOPE_RENDER_H_

#include "shader.h"
#include "Vector2.h"
#include "color.h"

namespace Algoriscope {
	class Render {
		private:
			Vector2 size;// 画布/场景尺寸
			GLFWwindow* window;// 窗口对象
			Shader shader;
			
		public:
			//构造函数，进行相关初始化。
			Render() {
				std::cout<<"render()\n";
				glfwInit();
				glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
				glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
				glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
				glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
				window = glfwCreateWindow(size.x, size.y, "Computer Graphics", nullptr, nullptr);
				glfwMakeContextCurrent(window);
				glewExperimental = true;
				glViewport(0, 0, size.x, size.y);

				shader.use();
			}

			//析构函数，进行收尾工作
			~Render() {
				glfwTerminate();
			}
			//负责帧的更新
			int update() {
				std::cout<<"update();\n";
				glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
				glClear(GL_COLOR_BUFFER_BIT);
				glfwSwapBuffers(window);
				glfwPollEvents();
				return 0;
			}

			//检测按键是否按下
			//key - 按下哪个键
			//options - 检测功能键（如ctrl,shift）等
			bool isKeyDown(const char& key, const char* options = "") const ;

			//画直线
			//pos1 - 起点位置
			//pos2 - 终点位置
			//color - 线的颜色
			int drawLine(const Vector2& pos1, const Vector2& pos2) {
				const float line[]={
//					pos1.x,pos2.y,1.0,
//					pos2.x,pos2.y,1.0,
					1.0f,1.0f,0.0f,
					1.0f,1.0f,0.0f
				};
				GLuint vertex_array_object;//VAO,使用核心模式，只需调用一次
				glGenVertexArrays(1, &vertex_array_object);//先生成
				glBindVertexArray(vertex_array_object);//再绑定
				
				GLuint vertex_buffer_object;//VBO
				glGenBuffers(1, &vertex_buffer_object);
				glBindBuffer(GL_ARRAY_BUFFER,vertex_buffer_object);//将顶点数据绑定至当前默认的缓冲中
				
				glBufferData(GL_ARRAY_BUFFER,sizeof(line),line,GL_STATIC_DRAW);
				
				glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)0);//设置顶点属性指针//试着去了解各个参数的意义
				glEnableVertexAttribArray(0);//开启通道
				glBindVertexArray(vertex_array_object);
				glDrawArrays(GL_LINES,0,2);
				return 0;
			}

			//画三角形
			//3个点+颜色
			int drawTri(const Vector2& pos1, const Vector2& pos2, const Vector2& pos3, const Color& col) ;

			//画矩形
			// pos - 起始点
			// size - 尺寸（宽和高）
			// color - 颜色
			int drawRect(const Vector2& pos, const Vector2& size, const Color& col) ;

			int drawText(const Vector2& pos, const char*);

	};
}

#endif
