#ifndef INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_ROLE_HPP
#define INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_ROLE_HPP

#include <list>
#include <vector>
#include <string>
#include <queue>

#include "Engine/Point.hpp"
#include "Engine/Sprite.hpp"

class OurGameScene;

class Role : public Engine::Sprite {
protected:
    std::vector<Engine::Point> path;
    float speed;
    float hp;
    int money;
    OurGameScene* getPlayScene();
    virtual void OnExplode();
    std::queue<std::string> tool;
public:
    int bombRange=1;
    float reachEndTime;
    Role(std::string img, float x, float y, float radius, float speed, float hp, int money);
    void Hit(float damage);
    virtual void Update(float deltaTime) override;
    virtual void Draw() const override;
    // 新添加的方法
    void SetPosition(float x, float y); // 設置角色的位置
    float GetX() const; // 獲取角色的x座標
    float GetY() const; // 獲取角色的y座標
    std::string UseTool();
    virtual int ReturnDir() =0;
    void gettool(std::string type);
};

#endif //INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_ROLE_HPP
