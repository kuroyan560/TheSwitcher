#pragma once
template<typename T>
struct Vector2
{
	T x;
	T y;

	Vector2<T> operator+(const Vector2<T>& obj)const
	{
		return Vector2<T>{ this->x + obj.x, this->y + obj.y };
	}

	Vector2<T>& operator+=(const Vector2<T>& obj)
	{
		*this = *this + obj;
		return *this;
	}

	Vector2<T> operator-(const Vector2<T>& obj)const
	{
		return Vector2<T>{this->x - obj.x, this->y - obj.y};
	}

	Vector2<T> operator-=(const Vector2<T>& obj)
	{
		*this = *this - obj;
		return *this;
	}

	Vector2<T> operator-()const
	{
		return Vector2<T>{-this->x, -this->y};
	}

	Vector2<T> operator*(const float& num)const
	{
		return Vector2<T>{this->x* num, this->y* num};
	}

	Vector2<T> operator/(const int& num)const
	{
		return Vector2<T>{this->x / num, this->y / num};
	}

	bool operator==(const Vector2<T>& obj)const
	{
		return (this->x == obj.x && this->y == obj.y);
	}

	bool operator!=(const Vector2<T>& obj)const
	{
		return (this->x != obj.x && this->y != obj.y);
	}
};