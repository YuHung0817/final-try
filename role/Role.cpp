#include "Role.hpp"

#include <allegro5/allegro_primitives.h>
#include <allegro5/color.h>
#include <cmath>
#include <random>
#include <string>
#include <vector>
#include <iostream>

#include "Engine/AudioHelper.hpp"
#include "Bullet/Bullet.hpp"
#include "UI/Animation/DirtyEffect.hpp"
#include "Role.hpp"
#include "UI/Animation/ExplosionEffect.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Group.hpp"
#include "Engine/IScene.hpp"
#include "Engine/LOG.hpp"
#include "Scene/OurGameScene.hpp"

OurGameScene* Role::getPlayScene() {
    return dynamic_cast<OurGameScene*>(Engine::GameEngine::GetInstance().GetActiveScene());
}

void Role::OnExplode() {
    getPlayScene()->EffectGroup->AddNewObject(new ExplosionEffect(Position.x, Position.y));
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> distId(1, 3);
    std::uniform_int_distribution<std::mt19937::result_type> dist(1, 20);
    for (int i = 0; i < 10; i++) {
        // Random add 10 dirty effects.
        getPlayScene()->GroundEffectGroup->AddNewObject(new DirtyEffect("play/dirty-" + std::to_string(distId(rng)) + ".png", dist(rng), Position.x, Position.y));
    }
}

Role::Role(std::string img, float x, float y, float radius, float speed, float hp, int money) :
        Engine::Sprite(img, x, y), speed(speed), hp(hp), money(money) {
    CollisionRadius = radius;
    reachEndTime = 0;
}

void Role::Hit(float damage) {
    hp -= damage;
    if (hp <= 0) {
        OnExplode();
        getPlayScene()->RoleGroup->RemoveObject(objectIterator);
    }
}
void Role::Draw() const{
    /*if(change) {
        //std::cout << "FrameIndex: " << frameIndex << std::endl;
        frameIndex = (frameIndex + 1) % 4;
        // Adjust the offset accordingly
        offset = frameIndex * 64;
        change = false;
    }
    offset = frameIndex * 64;
    int frameWidth = 64;
    int frameHeight = 99;
    al_draw_scaled_bitmap(bmp.get(), (dir*64*4) + offset, 0, frameWidth, frameHeight,
                          Position.x +40- frameWidth / 2, Position.y+40 - frameHeight / 2,
                          frameWidth-10, frameHeight-10, 0);
*/
    //Sprite::Draw();
    if (OurGameScene::DebugMode) {
        // Draw collision radius.
        al_draw_circle(Position.x, Position.y, CollisionRadius, al_map_rgb(255, 0, 0), 2);
    }
}
void Role::Update(float deltaTime) {


}
float Role::GetX() const {
    return this->Position.x;
}

float Role::GetY() const {
    return this->Position.y;
}
void Role::gettool(std::string type){
    std::cout<<"type== "<<type<<std::endl;
    tool.push(type);
}
std::string Role::UseTool(){
    if(tool.empty()) return "";
    else {
        std::cout<<"tool.front(): "<<tool.front()<<std::endl;
        std::string tmp=tool.front();
        tool.pop();
        return tmp;
    }
}