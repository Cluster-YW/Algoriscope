#ifndef SHADER_H
#define SHADER_H
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;
class Shader
{
public:
    Shader(const char* vertexPath, const char* fragmentPath)
    {

        this->vertexPath = vertexPath;
        this->fragmentPath = fragmentPath;


        //——————VS————————
        unsigned int vertex, fragment;
        vertex = glCreateShader(GL_VERTEX_SHADER);
        //读取glsl 到vertexShaderSrc
        string vertShaderSrc = loadShaderSrc(vertexPath);
        //把string转换为GLchar
        const GLchar* vertShader = vertShaderSrc.c_str();
        glShaderSource(vertex, 1, &vertShader, NULL);
        glCompileShader(vertex);

        // ——————FS————————
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        string fragmentShaderSrc = loadShaderSrc(fragmentPath);
        const GLchar* fragmentShader = fragmentShaderSrc.c_str();
        glShaderSource(fragment, 1, &fragmentShader, NULL);
        glCompileShader(fragment);

        // shader Program
        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        glLinkProgram(ID);

        //delete
        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }
    //读取文件函数
    string loadShaderSrc(const char* filename) {
        ifstream file; //创建file
        stringstream buf;
        string ret = "";
        file.open(filename);
        if (file.is_open()) {
            buf << file.rdbuf(); //文件写入buf
            ret = buf.str();  //buf存入ret
        }
        else {
            cout << "Could not open " << filename << endl;
        }
        file.close();
        return ret;
    }
    void use()
    {
        glUseProgram(ID);
    }
    void setBool(const std::string& name, bool value) const
    {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
    }
    void setInt(const std::string& name, int value) const
    {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }
    void setFloat(const std::string& name, float value) const
    {
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    }
    const char* vertexPath;
    const char* fragmentPath;
    unsigned int ID;
};
#endif
