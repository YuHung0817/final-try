#ifndef MYTURRET_HPP
#define MYTURRET_HPP
#include "Turret.hpp"

class MyTurret: public Turret {
public:
	static const int Price;
    MyTurret(float x, float y);
	void CreateBullet() override;
};
#endif // MYTURRET_HPP
