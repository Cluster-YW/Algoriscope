#ifndef VECTOR2_H
#define VECTOR2_H

#include <iostream>
#include <cmath>

class Vector2 {
public:
	float x;
	float y;
	float length;
	
	//无参构造函数
	Vector2();
	
	//有参构造函数
	Vector2(float x, float y);
	
	//拷贝构造函数
	Vector2(const Vector2 &vector2);
	
	//赋值运算符函数
	Vector2 &operator=(const Vector2 &vector);
	
	//------成员函数-------------------------------
	//设置向量坐标
	void Set(float x, float y);
	
	//返回向量长度
	float GetLength();
	
	//归一化(单位化)向量，使得向量长度为1
	void Normalize();
	
	//向量按比例缩放
	void Scale(float factor);
	
	//向量旋转一定角度
	Vector2 Rotate(float degree);
	
	//---------------静态函数------------------------
	//向量点乘
	static float Dot(const Vector2 &lhs, const Vector2 &rhs);
	
	//计算向量from和to的无方向夹角，返回角度（0~180）使用acos
	//如果不太清楚 google或baidu，或直接问老师
	static float Angle(const Vector2 &from, const Vector2 &to);
	
	//计算向量from和to的有方向夹角，返回角度（-180~180）使用 atan2
	static float SignedAngle(const Vector2 from, const Vector2 to);
	
	//计算向量from和to的距离 = ||from - to||
	static float Distance(const Vector2 from, const Vector2 to);
	
	//-------------------运算符-------------------------
	//下标运算符 vector[0]返回x, vector[1] 返回y
	float &operator[](int index);
	
	//输入输出运算符
	friend std::ostream &operator<<(std::ostream &os, const Vector2 &vector);
	
	friend std::istream &operator>>(std::istream &in, Vector2 &vector);
	
	//两个向量加法
	friend Vector2 operator+(const Vector2 &lhs, const Vector2 &rhs);
	
	//向量减法
	friend Vector2 operator-(const Vector2 &lhs, const Vector2 &rhs);
	
	//负向量
	friend Vector2 operator-(const Vector2 &lhs);
	
	//向量与标量乘，向量vector乘以标量factor
	friend Vector2 operator*(const Vector2 &lhs, const float factor);
	
	//标量与向量乘，标量factor乘以向量vector
	friend Vector2 operator*(const float &factor, const Vector2 &rhs);
	
	//向量与标量除法，向量vector除以标量factor，各元素x,y分别除以标量factor
	friend Vector2 operator/(const Vector2 &lhs, const float factor);
	
	//判断两个向量相等
	friend bool operator==(const Vector2 &lhs, const Vector2 &rhs);
	
	//判断两个向量不等
	friend bool operator!=(const Vector2 &lhs, const Vector2 &rhs);
	
private:
	//设置向量长度,应该将SetLength设为私有函数
	void SetLength();
};

#endif
