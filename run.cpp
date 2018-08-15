//Grid2u 2d game engine
//@zhong
//2018 - 
//version 0.1

//������������2d������Чģ�� רΪ2d��Ϸ����
//�����ƻ����� �ʵ� ���� ������ ת��  Լ�� ��ײ
//�汾�ſ�����
//������ȫ��ʵ�� ��Ϸ�������濪�� �����������Ҫ��Ϊ�汾 1.0 ��ʽ������git
//Ȼ��һ��ά���������� һ������Ϸ ������

//TODO(zhong) : ʵ�־ֲ�������ע�� done 2018/8/12
//TODO(zhong) : ģ�ⳡ�� 
//				����һ������ ����Χ��һ������һֱΧ����ת
//				���ر���Ե��� �����ֳԲ���
//				��ͻȻ���� ������̲���������С�ܶ������
//				������Խ��Խ�� Ȼ��������Ե��� ������ .. ���ġ�����

//TODO(zhong) : �Ż�ע�����洢��ʽ
//TODO(zhong) : �Ż��ڴ���䷽ʽ ���е�ע�����Ӧ�ù����ڴ� 
//TODO(zhong) : �Ż��ռ���� �Ĳ���֮���

#include"include/grid2u.h"
using namespace grid;
using namespace std;

int main()
{
	//stpe1 ׼��������Դ
	//		100������
	Real max_height = 20;	//�̻������߶�
	Real max_angle = std::_Pi / 3;	//�̻��������Ƕ�
	int  max_number = 1000;	//�̻����������	

	//׼��һ�������ð��������ƵĶ���
	Particle key;

							//����������ֵ
	uniform_real_distribution<Real> uniform_height(0.0, max_height);
	uniform_real_distribution<Real> uniform_angle(-0.5 * max_angle, 0.5* max_angle);
	default_random_engine e;

	//����һ��������������������
	vector<Particle> fire;
	fire.resize(max_number);
	Real random_angle = 0.0;
	Real random_height = 0.0;

	//����һ������ע���
	ParticleRegistry firework_particles;
	firework_particles.register_particle(&key);
	//�����������Դ
	for (int i = 0; i < max_number; ++i)
	{
		//�����ȡ���ӵ�ֵ
		random_height = uniform_height(e);
		random_angle = uniform_angle(e);
		fire[i].set_velocity(Vector(max_height * sin(random_angle), -max_height * cos(random_angle)));
		firework_particles.register_particle(&fire[i]);
	}

	//�󶨵������������
	PyhsicsPipeline firework;//���������������
	firework.bind_particle_registry(firework_particles);

	auto test_set = firework.get_particle_resource();
	//for (auto it : test_set)
	//{
	//	cout << it->get_position() << endl;
	//	cout << it->get_velocity() << endl;
	//}

	//step 2������������������������������

	//�����Զ��岢����������
	//����ֱ��ʹ�������ṩ������
	Gravity* firework_gravity = new Gravity(Vector(0, 0.8));
	KeyForce* keyforce = new KeyForce();
	//��������������ע���
	ParticleForceRegistry firework_force_registry;
	//���������ȫ��������
	firework_force_registry.register_global_force(firework_gravity);
	
	firework_force_registry.register_force(&key, keyforce);

	//�󶨵������������
	firework.bind_force_registry(firework_force_registry);

	//step3 ִ������ 
	//����render�������Ⱦ
	GridRender firework_render(1067, 600, 60, SHOWCONSOLE);
	setorigin(1067 / 2, 550);
	//��fireworkd_render�����Դ
	for (auto it : test_set)
	{
		firework_render.render_objects_.push_back(it);
	}
	while (true)
	{
		firework.calculate();
		firework_render.render();
	}

	delete firework_gravity;
	delete keyforce;
	system("pause");
	return 0;
}