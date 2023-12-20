#include "render.h"
#define  MAX_CHAR 128
namespace Algoriscope {
	Render::Render() : size (1500.0f,1500.0f) {
		std::cout << "render()\n";
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
		window = glfwCreateWindow(size.x, size.y, "Computer Graphics", nullptr, nullptr);
		glfwMakeContextCurrent(window);
		glewExperimental = true;
		glewInit();
		glViewport(0, 0, size.x, size.y);
		
//		shader.init("vertexShader0.glsl","fragmentShader_frag=vertex.glsl");
//		shader.use();
	}
	
	//析构函数，进行收尾工作
	Render::~Render() {
		std::cout<<"Terminate\n";
		glfwTerminate();
	}
	//负责帧的更新
	int Render::update() {
		std::cout << "update()\n";
		glfwSwapBuffers(window);
		glfwPollEvents();
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		shader.init("vertexShaderDrawLines.glsl","fragmentShader_frag=vertexDrawLines.glsl");
		shader.use();

		return 0;
	}
	
	//检测按键是否按下
	//key - 按下哪个键
	//options - 检测功能键（如ctrl,shift）等
	bool Render::isKeyDown(const char& key, const char* options) const {
		return 0;
	}
	
	//画直线
	//pos1 - 起点位置
	//pos2 - 终点位置
	//color - 线的颜色
	int Render::drawLine(const Vector2& pos1, const Vector2& pos2, const Color& col) {
		glLineWidth(10.0f);
		const float line[] = {
			pos1.x,pos1.y,0.0,
			pos2.x,pos2.y,0.0
//			0.0f, 0.0f, 0.0f,
//			0.2f, 0.5f, 0.0f
		};
		GLuint vertex_array_object;//VAO,使用核心模式，只需调用一次
		glGenVertexArrays(1, &vertex_array_object);//先生成
		glBindVertexArray(vertex_array_object);//再绑定
		
		GLuint vertex_buffer_object;//VBO
		glGenBuffers(1, &vertex_buffer_object);
		glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object); //将顶点数据绑定至当前默认的缓冲中
		
		glBufferData(GL_ARRAY_BUFFER, sizeof(line), line, GL_STATIC_DRAW);
		
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); //设置顶点属性指针//试着去了解各个参数的意义
		glEnableVertexAttribArray(0);//开启通道
		
		glBindVertexArray(vertex_array_object);
		
		shader.setFloat4("inputColor",col.getRf(),col.getGf(),col.getBf(),col.getAf());
		
		glDrawArrays(GL_LINES, 0, 2);

		return 1;
	}
	
	//画三角形
	//3个点+颜色
	int Render::drawTri(const Vector2& pos1, const Vector2& pos2, const Vector2& pos3, const Color& col) {
		const float vertices[] = {
			pos1.x,pos1.y,0.0,
			pos2.x,pos2.y,0.0,
			pos3.x,pos3.y,0.0,
		};
		GLuint VAO,VBO,EBO;
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
		glGenBuffers(1, &VBO); 
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glBindVertexArray(VAO);
		shader.setFloat4("inputColor",col.getRf(),col.getGf(),col.getBf(),col.getAf());
		glDrawArrays(GL_TRIANGLES, 0, 6);
		return 0;
	}
	
	//画矩形
	// pos - 起始点
	// size - 尺寸（宽和高）
	// color - 颜色
	int Render::drawRect(const Vector2& pos, const Vector2& size, const Color& col) {
		const float vertices[] = {
			pos.x,pos.y,0.0,
			pos.x+size.x,pos.y,0.0,
			pos.x,pos.y+size.y,0.0,
			pos.x+size.x,pos.y+size.y,0.0
		};
		unsigned int indices[] = { 
			0, 1, 2, 
			1, 2, 3 
		}; 
		GLuint VAO,VBO,EBO;
		glGenVertexArrays(1, &VAO); 
		glBindVertexArray(VAO);
		glGenBuffers(1, &VBO); 
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glBindVertexArray(VAO);
		shader.setFloat4("inputColor",col.getRf(),col.getGf(),col.getBf(),col.getAf());
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		return 0;
	}
	int Render::drawText(const Vector2& pos, const char*){

		return 0;
	}
	
};
