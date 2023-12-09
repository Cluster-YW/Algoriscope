#include<iostream>
#include<cmath>
using namespace std;
class Vector2 {
public:
	double x;
	double y;
	double length;
	
	//无参构造函数
	Vector2();
	
	//有参构造函数
	Vector2(double x, double y);
	
	//拷贝构造函数
	Vector2(const Vector2 &vector2);
	
	//赋值运算符函数
	Vector2 &operator=(const Vector2 &vector);
	
	//------成员函数-------------------------------
	//设置向量坐标
	void Set(double x, double y);
	
	//返回向量长度
	double GetLength();
	
	//归一化(单位化)向量，使得向量长度为1
	void Normalize();
	
	//向量按比例缩放
	void Scale(double factor);
	
	//---------------静态函数------------------------
	//向量点乘
	static double Dot(const Vector2 &lhs, const Vector2 &rhs);
	
	//计算向量from和to的无方向夹角，返回角度（0~180）使用acos
	//如果不太清楚 google或baidu，或直接问老师
	static double Angle(const Vector2 &from, const Vector2 &to);
	
	//计算向量from和to的有方向夹角，返回角度（-180~180）使用 atan2
	static double SignedAngle(const Vector2 from, const Vector2 to);
	
	//计算向量from和to的距离 = ||from - to||
	static double Distance(const Vector2 from, const Vector2 to);
	
	//-------------------运算符-------------------------
	//下标运算符 vector[0]返回x, vector[1] 返回y
	double &operator[](int index);
	
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
	friend Vector2 operator*(const Vector2 &lhs, const double factor);
	
	//标量与向量乘，标量factor乘以向量vector
	friend Vector2 operator*(const double &factor, const Vector2 &rhs);
	
	//向量与标量除法，向量vector除以标量factor，各元素x,y分别除以标量factor
	friend Vector2 operator/(const Vector2 &lhs, const double factor);
	
	//判断两个向量相等
	friend bool operator==(const Vector2 &lhs, const Vector2 &rhs);
	
	//判断两个向量不等
	friend bool operator!=(const Vector2 &lhs, const Vector2 &rhs);
	
private:
	//设置向量长度,应该将SetLength设为私有函数
	void SetLength();
};Vector2::Vector2() {
	this->x = 0;
	this->y = 0;
	SetLength();
}

Vector2::Vector2(double x, double y) {
	Set(x, y);
	SetLength();
}

Vector2::Vector2(const Vector2 &vector2) {
	Set(vector2.x, vector2.y);
	SetLength();
}

Vector2 &Vector2::operator=(const Vector2 &vector) {
	Set(vector.x, vector.y);
	SetLength();
	return *this;
}

void Vector2::Set(double x, double y) {
	this->x = x;
	this->y = y;
	SetLength();
}

void Vector2::SetLength() {
	this->length = sqrt(pow(this->x, 2) + pow(this->y, 2));
}

double Vector2::GetLength() {
	return this->length;
}

void Vector2::Normalize() {
	double divisor = sqrt(pow(this->x, 2) + pow(this->y, 2));
	this->x /= divisor;
	this->y /= divisor;
	SetLength();
}

void Vector2::Scale(double factor) {
	this->x /= factor;
	this->y /= factor;
	SetLength();
}

double Vector2::Dot(const Vector2 &lhs, const Vector2 &rhs) {
	return lhs.x * rhs.x + lhs.y * rhs.y;
}

double Vector2::Angle(const Vector2 &from, const Vector2 &to) {
	double PI = 3.141592653589793238;
	double t = ((from.x) * (to.x) + (from.y) * (to.y)) /
	(sqrt(pow(from.x, 2) + pow(from.y, 2)) * sqrt(pow(to.x, 2) + pow(to.y, 2)));
	return acos(t) * (180 / PI);
}

double Vector2::SignedAngle(const Vector2 from, const Vector2 to) {
	double pi = 3.141592653589793238;
	return atan2((to.y - from.y), (to.x - from.x)) * (double) 180 / pi;
}

double Vector2::Distance(const Vector2 from, const Vector2 to) {
	return sqrt(pow(from.x - to.x, 2) + pow(from.y - to.y, 2));
}

double &Vector2::operator[](int index) {
	if (index == 0) {
		return this->x;
	} else if (index == 1) {
		return this->y;
	}
}

std::ostream &operator<<(ostream &os, const Vector2 &vector) {
	return os << "x: " << vector.x << "\ny: " << vector.y << "\nlenth: " << vector.length << "\n";
}

std::istream &operator>>(istream &in, Vector2 &vector) {
	vector.SetLength();
	return in >> vector.x >> vector.y;
}

Vector2 operator+(const Vector2 &lhs, const Vector2 &rhs) {
	Vector2 *v = new Vector2();
	v->x = lhs.x + rhs.x;
	v->y = lhs.y + rhs.y;
//    return v;
	v->SetLength();
	return *v;
}

Vector2 operator-(const Vector2 &lhs, const Vector2 &rhs) {
	Vector2 *v = new Vector2();
	v->x = lhs.x - rhs.x;
	v->y = lhs.y - rhs.y;
//    return v;
	v->SetLength();
	return *v;
}

Vector2 operator-(const Vector2 &lhs) {
	Vector2 *v = new Vector2();
	v->x = -lhs.x;
	v->y = -lhs.y;
	v->SetLength();
	return *v;
}

Vector2 operator*(const Vector2 &lhs, const double factor) {
	Vector2 *v = new Vector2();
	v->x = lhs.x * factor;
	v->y = lhs.y * factor;
	v->SetLength();
	return *v;
}

Vector2 operator*(const double &factor, const Vector2 &rhs) {
	Vector2 *v = new Vector2();
	v->x = rhs.x * factor;
	v->y = rhs.y * factor;
	v->SetLength();
	return *v;
}

Vector2 operator/(const Vector2 &lhs, const double factor) {
	Vector2 *v = new Vector2();
	v->x = lhs.x / factor;
	v->y = lhs.y / factor;
	v->SetLength();
	return *v;
}

bool operator==(const Vector2 &lhs, const Vector2 &rhs) {
	if (lhs.x == rhs.x && lhs.y == lhs.y) {
		return true;
	}
	return false;
}

bool operator!=(const Vector2 &lhs, const Vector2 &rhs) {
	if (lhs.x == rhs.x && lhs.y == lhs.y) {
		return false;
	}
	return true;
}
