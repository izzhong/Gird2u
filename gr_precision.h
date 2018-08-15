//file anno

#ifndef _GRID_PRECISION_H_
#define _GRID_PRECISION_H_

//mabye some machines can not support double.
//so you can change this typedef to [float] if need.
using Real = double;
constexpr Real REAL_PRECISION = 1e-8;

inline bool is_zero_real(Real r)
{	//remove the precision error.
	return (r < 0.0 ? -r : r) < REAL_PRECISION;
} 

//you can use it like this : _Real(a_Real_value)
//to trans a Real value which can remove the precision error.
inline Real _real(Real r)
{	
	return is_zero_real(r) ? 0.0 : r;
}

#endif //_GRID_PRECISION_H_