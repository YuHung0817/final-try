//
// Created by IRIS0817 on 2024/6/12.
//

#ifndef INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_BOMB_HPP
#define INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_BOMB_HPP
#include <string>

#include "Engine/Sprite.hpp"


class OurGameScene;

namespace Engine {
    struct Point;
}  // namespace Engine

class Bomb : public Engine::Sprite {
protected:
    float timer;
    OurGameScene* getPlayScene();
    virtual void OnExplode();
public:
    explicit Bomb(std::string img,int x,int y,int t);
    void Update(float deltaTime) override;
};
#endif //INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_BOMB_HPP
