//gr_particle_constraint.cpp

#include"include/gr_particle_constraint.h"
#include"include/gr_particle_force.h"

namespace grid
{
	//���ȼ򵥵�˼�� һ��ֱ���ϵ������˶�

	void SurroundParticleConstraint::operator()(Particle* particle)
	{
		//�������Ӻ���������λ�ü�������
		Vector location = particle->get_position() - fix_position_;
		//�������location��������
		Vector force = location * (-1.0 * sensitivity_);
		//�����������������һ֡��λ��
	}

} //namespace grid