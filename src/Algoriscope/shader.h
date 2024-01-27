#ifndef ALGORISCOPE_SHADER_H
#define ALGORISCOPE_SHADER_H



#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;
class Shader {
	public:
		Shader() {

		}
		Shader(const char* vPath, const char* fPath) {
			init(vPath, fPath);
		}
		void init(const char* vPath, const char* fPath) {

			this->vertexPath = vPath;// 读入顶点着色器的文件位置
			this->fragmentPath = fPath; //读入片段着色器的文件位置
			// ——————VS————————
			// 顶点着色器部分
			//
			unsigned int vertex;
			vertex = glCreateShader(GL_VERTEX_SHADER);// 创建顶点着色器
			string vertShaderSrc = loadShaderSrc(vertexPath); // 读取 glsl 到 vertexShaderSrc
			const GLchar* vertShader = vertShaderSrc.c_str(); // 把 string 转换为 GLchar
			glShaderSource(vertex, 1, &vertShader, NULL); // 输入着色器源代码

			glCompileShader(vertex); // 编译着色器

			int success;
			char info_log[512];
			//检查着色器是否成功编译，如编译失败，打印错误信息
			glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
			if (!success) {
				glGetShaderInfoLog(vertex, 512, NULL, info_log);
				cout << "vertex编译失败\n" << info_log << endl;
			}

			// ——————FS————————
			// 片段着色器部分
			// 类似VS
			unsigned int fragment;
			fragment = glCreateShader(GL_FRAGMENT_SHADER);

			string fragmentShaderSrc = loadShaderSrc(fragmentPath);
			const GLchar* fragmentShader = fragmentShaderSrc.c_str();
			glShaderSource(fragment, 1, &fragmentShader, NULL);

			glCompileShader(fragment);
			glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
			if (!success) {
				glGetShaderInfoLog(fragment, 512, NULL, info_log);
				cout << "编译失败\n" << info_log << endl;
			}



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
		void setFloat4(const std::string& name, float value1, float value2, float value3, float value4) const {
			glUniform4f(glGetUniformLocation(ID, name.c_str()), value1, value2, value3, value4);
		}
		void setMat4(const std::string &name, const glm::mat4 &mat) const{
			glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
		}
		const char* vertexPath;
		const char* fragmentPath;
		unsigned int ID;
};
#endif
