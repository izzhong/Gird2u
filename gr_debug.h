//debug ����Ҫ�����ܾ��Ǳ����� ��������ֲ��в������

#ifndef _GRID_DEBUG_H_
#define _GRID_DEBUG_H_

#include"gr_particle.h"
#include<iostream>

namespace grid
{
	//cout a vector like this (x,y)
	std::ostream& operator<<(std::ostream& os,const Vector& right)
	{
		std::cout << "(" << right.x << "," << right.y << ")";
		return os;
	}

	std::ostream& operator<<(std::ostream& os, const Particle& particle)
	{
		std::cout 
			<< particle.get_inverse_mass() << "," 
			<< particle.get_position() << "," 
			<< particle.get_velocity();
		return os;
	}

} //namespace grid

#endif //_GRID_DEBUG_H_