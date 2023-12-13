#define GLEW_STATIC
#include <iostream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <math.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
class Shader {
public:
	Shader(const char* vertexPath, const char* fragmentPath) {
		
		this->vertexPath = vertexPath;// 读入顶点着色器的文件位置
		this->fragmentPath = fragmentPath; //读入片段着色器的文件位置
		
		
		// ——————VS————————
		// 顶点着色器部分
		//
		unsigned int vertex;
		vertex = glCreateShader(GL_VERTEX_SHADER);// 创建顶点着色器
		
		string vertShaderSrc = loadShaderSrc(vertexPath); // 读取 glsl 到 vertexShaderSrc
		const GLchar* vertShader = vertShaderSrc.c_str(); // 把 string 转换为 GLchar
		glShaderSource(vertex, 1, &vertShader, NULL); // 输入着色器源代码
		
		glCompileShader(vertex); // 编译着色器
		
		// ——————FS————————
		// 片段着色器部分
		// 类似VS
		unsigned int fragment;
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		
		string fragmentShaderSrc = loadShaderSrc(fragmentPath);
		const GLchar* fragmentShader = fragmentShaderSrc.c_str();
		glShaderSource(fragment, 1, &fragmentShader, NULL);
		
		glCompileShader(fragment);
		
		// shader Program
		// 创建着色器程序
		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);
		
		// 程序创建完成后删除着色器
		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}
	// 读取文件函数
	string loadShaderSrc(const char* filename) {
		ifstream file; //创建file
		stringstream buf;
		string ret = "";
		file.open(filename);
		if (file.is_open()) {
			buf << file.rdbuf(); //文件写入buf
			ret = buf.str();  //buf存入ret
		} else {
			cout << "Could not open " << filename << endl;
		}
		file.close();
		return ret;
	}
	// 使用着器
	void use() {
		glUseProgram(ID);
	}
	// 设置 bool 类型的 uniform 值
	// nams		着色器源码中的 uniform 名字
	// value	要更改的值
	void setBool(const std::string& name, bool value) const {
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
	}
	// 下面的函数类似
	// 设置 int 类型的 uniform 值
	void setInt(const std::string& name, int value) const {
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}
	void setFloat(const std::string& name, float value) const {
		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	}
	const char* vertexPath;
	const char* fragmentPath;
	unsigned int ID;
};

//#include "stb_image.h"图片导入 与纹理相关

using namespace std;

void processInput(GLFWwindow* window);


//模型顶点数据
float vertices[] = {
	0.5f, 0.5f, 0.0f, 
	0.5f, -0.5f, 0.0f, 
	-0.5f, -0.5f, 0.0f, 
	-0.5f, 0.5f, 0.0f, 
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
	
	if (window == NULL)//若初始化失败
	{
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();//销毁窗口，释放资源
		return EXIT_FAILURE;
	}
	glfwMakeContextCurrent(window);//指定线程，创建OpenGL上下文
	
	glewExperimental = true;
	
	if (glewInit() != GLEW_OK)//初始glew工具
	{
		std::cout << "glew init failed." << std::endl;
		glfwTerminate();
		return EXIT_FAILURE;
	}
	//设置视口视角
	glViewport(0, 0, 800, 600);
	
//	  框线模式 Wireframe Mode
//	  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//	  剔除多边形背面
//	  glEnable(GL_CULL_FACE);
//	  glCullFace(GL_FRONT);//GL_BACK:剔除背面 ，GL_FRONT:剔除正面
	 
	
	//VBO
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// Bind 究竟是什么意思？
	// 个人理解：把当前操作的目标设置为某个对象——颜午
	
	//EBO
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	
	// VBO - 负责数据的传输
	// VAO - 负责数据的解释
	
	//VAO 绑定Vertex Arrays
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// 上述代码的解释
	// glVertexAttribPointer() 负责解释 VBO 中顶点使用的顺序。
	// 第一个参数 0，表示对应数据要传入属性的 location。此处为 0 (location = 0)。
	// 第二个参数 3，表示传入属性由几个值构成。此处表示一次传入 3 个，对应 vec3。
	// 第三个参数 GL_FLOAT，表示传入数据类型。此处表示 float。
	// 第四个参数 GL_FALSE，设置是否标准化（把所有数据压缩到 0~1 之间）。此处选择否。
	// 第五个参数 6 * sizeof(float)，表示内存步长。
	// 		这里指每隔 6 个 float 的内存大小传入。
	//  	若设置为 0 ，则按紧密排列的假设自动设定。
	// 第六个参数 (void*)0 起始位置指针，类型为 void* 无类型指针。
	// 		未绑定 VBO 时，直接指向需要上传的数据地址。
	// 		绑定 VBO 时，表示 VBO 位置的地址偏移量。
	//		此处第一个为 0 表示从头开始取。第二个表示跳过开头的 3 个开始取。
	//	
	// glEnableVertexAttribArray() 表示启用顶点属性。不启用则对应 location 无法输入。
	
	while (!glfwWindowShouldClose(window))
	{
		//读取shadersource文本文件
		const char* vertexPath ="vertexShader.glsl";
		const char* fragmentPath ="fragmentShader_frag=vertex.glsl";
		
		processInput(window);//处理输入事件
		
		glClearColor(0.2f, 0.3f, 0.3f, 0.1f);
		//清空colorbuff的缓冲区
		glClear(GL_COLOR_BUFFER_BIT);
		//--------
		
		//更新 VBO 的缓冲数据
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		
		//Draw Triangle
		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		
		//use shader头文件
		Shader shader(vertexPath, fragmentPath);
		shader.use();
		
		float change =0.2;
		for(int i=0;i<5;i++)
		{
			shader.setFloat("change",change);
			glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
			change+=0.5;
		}
		
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		// glDrawArrays() 	直接画图
		// 第一个参数 要画的图形
		// 第二个参数 从 VAO 读出的第几个点开始
		// 第三个参数 使用的点的个数
		// glDrawElements() 按照索引的方式画图
		// 第一个参数 要画的图形
		// 第二个参数 使用的点的个数
		// 第三和第四个参数分别表示读取 EBO 的数据类型和起始位置偏移量
		
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
