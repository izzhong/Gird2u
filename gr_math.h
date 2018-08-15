//FILE ANNO

//TODO(zhong) : maybe i will implement it myself.but now the point is not the math.
//				so i use the standard c++ math.

#ifndef _GRID_MATH_H_
#define _GRID_MATH_H_

#include"gr_precision.h"
#include<cmath>

namespace grid
{
	inline Real gr_sqrt(Real real_value)
	{
		return std::sqrt(real_value);
	}
}//namespace grid

#endif //_GRID_MATH_H_