//
// Created by IRIS0817 on 2024/6/12.
//

#ifndef INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_BOX_HPP
#define INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_BOX_HPP
#include <allegro5/base.h>
#include <list>

#include "Instrument.hpp"

namespace Engine {
    struct Point;
}  // namespace Engine

class Box : public Instrument{
protected:
    //const float rotateRadian = 2 * ALLEGRO_PI;
    //std::list<Bullet*>::iterator lockedBulletIterator;
public:
    explicit Box(std::string img,int x,int y);
    virtual void Update(float deltaTime) override;
    void OnExplode() override;
};

#endif //INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_BOX_HPP
