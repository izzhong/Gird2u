//gr_particle_constraint.cpp

#include"include/gr_particle_constraint.h"
#include"include/gr_particle_force.h"

namespace grid
{
	//首先简单的思考 一条直线上的类似运动

	void SurroundParticleConstraint::operator()(Particle* particle)
	{
		//根据粒子和物体的相对位置计算受力
		Vector location = particle->get_position() - fix_position_;
		//根据这个location计算受力
		Vector force = location * (-1.0 * sensitivity_);
		//根据这个受力计算下一帧的位置
	}

} //namespace grid