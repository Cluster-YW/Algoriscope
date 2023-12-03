#define GLEW_STATIC
#include <iostream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "shader.h"  
#include <math.h>
//#include "stb_image.h"图片导入 与纹理相关

using namespace std;

void processInput(GLFWwindow* window);


//模型顶点数据
float vertices[] = {
	0.5f, 0.5f, 0.0f,   /* Postion 右上角  Color*/  1.0f, 0.0f, 0.0f,
	0.5f, -0.5f, 0.0f,  /* 右下角 */			    0.0f, 1.0f, 0.0f,
	-0.5f, -0.5f, 0.0f, /* 左下角 */			    0.0f, 0.0f, 1.0f,
	-0.5f, 0.5f, 0.0f,  /* 左上角*/					1.0f, 0.0f, 1.0f,
};


unsigned int indices[] = { // 注意索引从0开始! 
	0, 1, 3, // 第一个三角形
	1, 2, 3  // 第二个三角形
};



int main(int argc, char* argv[]) {
	
	
	glfwInit();
	//设置opengl版本3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//告诉glfw主要版本3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//告诉glfw次要版本3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//告诉glfw使用core-profile
	
	GLFWwindow* window = glfwCreateWindow(800, 600, "Test window", NULL, NULL);
	
	if (window == NULL)
	{
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();//销毁窗口，释放资源
		//return EXIT_FAILURE;
	}
	glfwMakeContextCurrent(window);//指定线程
	
	glewExperimental = true;
	
	if (glewInit() != GLEW_OK)//初始glew工具
	{
		std::cout << "glew init failed." << std::endl;
		glfwTerminate();
		return EXIT_FAILURE;
	}
	//设置视口视角
	glViewport(0, 0, 800, 600);
	/*
	  //框线模式 Wireframe Mode
	  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	  //剔除多边形背面
	  //glEnable(GL_CULL_FACE);
	  //glCullFace(GL_FRONT);//GL_BACK:剔除背面 ，GL_FRONT:剔除正面
	 */
	//VAO 绑定Vertex Arrays
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	//VBO
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	//EBO
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	
	while (!glfwWindowShouldClose(window))
	{
		//读取shadersource文本文件
		const char* vertexPath ="vertexShader.glsl";
		const char* fragmentPath ="fragmentShader_frag=vertex.glsl";
		
		
		processInput(window);
		
		
		glClearColor(0.2f, 0.3f, 0.3f, 0.1f);
		//清空colorbuff的缓冲区
		glClear(GL_COLOR_BUFFER_BIT);
		//--------
		
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		
		//Draw Triangle
		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		
		//use shader头文件
		Shader shader(vertexPath, fragmentPath);
		shader.use();
		
		float time = glfwGetTime();
		float sinTime = sin(time);// 可写成sin(time*10) 则速度加快
		shader.setFloat("change", sinTime); //把sinTime赋给名为change的变量  
		
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	glfwTerminate();
	return 0;
}
//Esc按键响应程序
void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		vertices[0] += 0.01f;
		vertices[1] += 0.01f;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		vertices[0] -= 0.01f;
		vertices[1] -= 0.01f;
	}
	
}
