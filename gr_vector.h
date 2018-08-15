//file anno

#ifndef _GRID_VECTOR_H_
#define _GRID_VECTOR_H_

#include"gr_math.h"
#include<cassert>

namespace grid
{	
	//2D vector : (x,y)
	//There are two points you should pay your attention on them.
	//	1. the operator* overloading is not the usual vector scalar-multiplication.
	//	   please check the code of operator*().	
	//	2. when you normalize a zero vector.
	//	   please check the function code of is_zero() and normalize().
	class Vector2
	{
	public:	

		Real x, y;

	public:

		//default 2dvector is (0.0,0.0)
		Vector2() :	
			x(0.0), y(0.0) {  }

		//stop the change of {x,y} to Vector2(x,y)
		explicit Vector2(Real _x, Real _y) :
			x(_x), y(_y) {	}

		Vector2& set(Real _x, Real _y)
		{
			x = _x;
			y = _y;
			return *this;
		}
	
		Vector2 operator+(const Vector2& right) const
		{	//vector plus : *this + right
			return Vector2(x + right.x, y + right.y);
		}

		Vector2& operator+=(const Vector2& right)
		{	//vector plus_equal : *this = *this + right
			x += right.x;
			y += right.y;
			return *this;
		}

		Vector2 operator-(const Vector2& right) const
		{	//vector subtract : *this - right
			return Vector2(x - right.x, y - right.y);
		}

		Vector2& operator-=(const Vector2& right)
		{	//vector subtract_equal : *this = *this - right
			x -= right.x;
			y -= right.y;
			return *this;
		}

		//only support the format like this : (vector * real_value)
		//why dont implement the format like : (real_value * vector)
		//there are two resons : 1. the format like the first is enough.
		//						 2. if i implement two formats.u maybe use it like this :
		//							real_value * vector * real_value,
		//							which called function two times,creats extra spending.
		Vector2 operator*(Real real_value) const
		{	//vector scalar multi : *this * real_value
			return Vector2(x *real_value, y * real_value);
		}

		Vector2& operator*=(Real real_value)
		{	//vector scalar_multi_equal : *this = *this * k
			x *= real_value;
			y *= real_value;
			return *this;
		}

		Vector2 operator-() const
		{	//like : *this * -1.0
			return Vector2(-x, -y);
		}

		bool operator==(const Vector2& right) const
		{	//remove the precision error
			return is_zero_real(x - right.x) && 
				   is_zero_real(y - right.y);
		}

		bool operator!=(const Vector2& right) const
		{
			return !(*this == right);
		}
	
		//2dvector dot product
		Real dot(const Vector2& right) const
		{
			return _real(x * right.x + y * right.y);
		}

		//2dvector corss product
		Real cross(const Vector2& right) const
		{
			return _real(x * right.y - y * right.x);
		}

		//judge a 2dvector is a zero vecotr
		bool is_zero() const
		{
			return is_zero_real(x) && is_zero_real(y);
		}

		//normalize a 2dvector to let its length change to 1.
		//if you normalize a zero vector,function will assert.
		//so use it carefully.
		Vector2& normalize()
		{
			if (is_zero())
				assert(false);
			Real vector_length = 1.0 / gr_sqrt(x * x + y * y);
			x *= vector_length;
			y *= vector_length;
			return *this;
		}

		//calculate the length of a 2dvector
		Real length() const
		{
			if (is_zero())
				return 0.0;
			else
				return gr_sqrt(x * x + y * y);
		}
	};//class Vector2

	//in many algorithms,a 2dvector or a 3dvector is not important.
	//so I typedef it into [Vector].so when I implement some algorithms.
	//I can change it to 3d much easier.
	using Vector = Vector2;

}//namespace grid

#endif //_GRID_VECTOR_H_