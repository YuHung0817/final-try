//
// Created by IRIS0817 on 2024/6/12.
//

#ifndef INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_BOMB1_HPP
#define INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_BOMB1_HPP
#include <allegro5/base.h>
#include <list>

#include "Bomb.hpp"

namespace Engine {
    struct Point;
}  // namespace Engine

class Bomb1 : public Bomb{
protected:
    //const float rotateRadian = 2 * ALLEGRO_PI;
    //std::list<Bullet*>::iterator lockedBulletIterator;
public:
    explicit Bomb1(int x,int y);
    virtual void Update(float deltaTime) override;
    void OnExplode() override;
};

#endif //INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_BOMB1_HPP
