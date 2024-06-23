#ifndef MYBULLET_HPP
#define MYBULLET_HPP
#include "Bullet.hpp"

class Enemy;
class Turret;
namespace Engine {
struct Point;
}  // namespace Engine

class MyBullet : public Bullet {
public:
	explicit MyBullet(Engine::Point position, Engine::Point forwardDirection, float rotation, Turret* parent);
	void OnExplode(Enemy* enemy) override;
};
#endif // MYBULLET_HPP
