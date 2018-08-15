//Grid2u 2d game engine
//@zhong
//2018 - 
//version 0.1

//本引擎着力于2d物理特效模拟 专为2d游戏开发
//初步计划引入 质点 刚体 作用力 转矩  约束 碰撞
//版本号看心情
//最终以全部实现 游戏物理引擎开发 整本书的所有要求为版本 1.0 正式发布到git
//然后一边维护开发引擎 一边做游戏 美滋滋

//TODO(zhong) : 实现局部作用力注册 done 2018/8/12
//TODO(zhong) : 模拟场景 
//				你是一个地球 你周围有一个月球一直围着你转
//				你特别想吃掉它 但是又吃不着
//				你突然发现 你可以吞并其他比你小很多的星星
//				于是你越吃越大 然后把月亮吃掉了 啊哈哈 .. 无聊。。。

//TODO(zhong) : 优化注册器存储方式
//TODO(zhong) : 优化内存分配方式 所有的注册表都不应该管理内存 
//TODO(zhong) : 优化空间管理 四叉树之类的

#include"include/grid2u.h"
using namespace grid;
using namespace std;

int main()
{
	//stpe1 准备粒子资源
	//		100个粒子
	Real max_height = 20;	//烟花的最大高度
	Real max_angle = std::_Pi / 3;	//烟花的最大发射角度
	int  max_number = 1000;	//烟花的最大数量	

	//准备一个可以用按键来控制的对象
	Particle key;

							//获得随机的数值
	uniform_real_distribution<Real> uniform_height(0.0, max_height);
	uniform_real_distribution<Real> uniform_angle(-0.5 * max_angle, 0.5* max_angle);
	default_random_engine e;

	//声明一个粒子用来存放随机数据
	vector<Particle> fire;
	fire.resize(max_number);
	Real random_angle = 0.0;
	Real random_height = 0.0;

	//声明一个粒子注册表
	ParticleRegistry firework_particles;
	firework_particles.register_particle(&key);
	//向其中添加资源
	for (int i = 0; i < max_number; ++i)
	{
		//随机获取粒子的值
		random_height = uniform_height(e);
		random_angle = uniform_angle(e);
		fire[i].set_velocity(Vector(max_height * sin(random_angle), -max_height * cos(random_angle)));
		firework_particles.register_particle(&fire[i]);
	}

	//绑定到物理运算管线
	PyhsicsPipeline firework;//定义物理运算管线
	firework.bind_particle_registry(firework_particles);

	auto test_set = firework.get_particle_resource();
	//for (auto it : test_set)
	//{
	//	cout << it->get_position() << endl;
	//	cout << it->get_velocity() << endl;
	//}

	//step 2向物理运算管线中添加作用力发生器

	//首先自定义并创建作用力
	//这里直接使用引擎提供的重力
	Gravity* firework_gravity = new Gravity(Vector(0, 0.8));
	KeyForce* keyforce = new KeyForce();
	//创建粒子作用力注册表
	ParticleForceRegistry firework_force_registry;
	//向其中添加全局作用力
	firework_force_registry.register_global_force(firework_gravity);
	
	firework_force_registry.register_force(&key, keyforce);

	//绑定到物理运算管线
	firework.bind_force_registry(firework_force_registry);

	//step3 执行运算 
	//利用render库进行渲染
	GridRender firework_render(1067, 600, 60, SHOWCONSOLE);
	setorigin(1067 / 2, 550);
	//向fireworkd_render添加资源
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