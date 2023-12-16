#include "vector2.h"

Vector2::Vector2() {
	this->x = 0;
	this->y = 0;
	SetLength();
}

Vector2::Vector2(float x, float y) {
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

void Vector2::Set(float x, float y) {
	this->x = x;
	this->y = y;
	SetLength();
}

void Vector2::SetLength() {
	this->length = sqrt(pow(this->x, 2) + pow(this->y, 2));
}

float Vector2::GetLength() {
	return this->length;
}

void Vector2::Normalize() {
	float divisor = sqrt(pow(this->x, 2) + pow(this->y, 2));
	this->x /= divisor;
	this->y /= divisor;
	SetLength();
}

void Vector2::Scale(float factor) {
	this->x /= factor;
	this->y /= factor;
	SetLength();
}

float Vector2::Dot(const Vector2 &lhs, const Vector2 &rhs) {
	return lhs.x * rhs.x + lhs.y * rhs.y;
}

float Vector2::Angle(const Vector2 &from, const Vector2 &to) {
	float PI = 3.141592653589793238;
	float t = ((from.x) * (to.x) + (from.y) * (to.y)) /
	(sqrt(pow(from.x, 2) + pow(from.y, 2)) * sqrt(pow(to.x, 2) + pow(to.y, 2)));
	return acos(t) * (180 / PI);
}

float Vector2::SignedAngle(const Vector2 from, const Vector2 to) {
	float pi = 3.141592653589793238;
	return atan2((to.y - from.y), (to.x - from.x)) * (float) 180 / pi;
}

float Vector2::Distance(const Vector2 from, const Vector2 to) {
	return sqrt(pow(from.x - to.x, 2) + pow(from.y - to.y, 2));
}

float &Vector2::operator[](int index) {
	if (index == 0) {
		return this->x;
	} else {
		return this->y;
	}
}

std::ostream &operator<<(std::ostream &os, const Vector2 &vector) {
	return os << "x: " << vector.x << "\ny: " << vector.y << "\nlenth: " << vector.length << "\n";
}

std::istream &operator>>(std::istream &in, Vector2 &vector) {
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

Vector2 operator*(const Vector2 &lhs, const float factor) {
	Vector2 *v = new Vector2();
	v->x = lhs.x * factor;
	v->y = lhs.y * factor;
	v->SetLength();
	return *v;
}

Vector2 operator*(const float &factor, const Vector2 &rhs) {
	Vector2 *v = new Vector2();
	v->x = rhs.x * factor;
	v->y = rhs.y * factor;
	v->SetLength();
	return *v;
}

Vector2 operator/(const Vector2 &lhs, const float factor) {
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
