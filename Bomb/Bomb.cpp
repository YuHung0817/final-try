//
// Created by IRIS0817 on 2024/6/12.
//
#include "Bomb.hpp"
#include "Engine/Collider.hpp"
#include "Enemy/Enemy.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Group.hpp"
#include "Engine/IObject.hpp"
#include "Engine/IScene.hpp"
#include "Scene/OurGameScene.hpp"
#include "Engine/Point.hpp"
#include "Engine/Sprite.hpp"

OurGameScene* Bomb::getPlayScene() {
    return dynamic_cast<OurGameScene*>(Engine::GameEngine::GetInstance().GetActiveScene());
}
void Bomb::OnExplode() {
}
Bomb::Bomb(std::string img, int x,int y,int t) :
        Sprite(img, x, y) ,timer(t){
    CollisionRadius = 1;//cna be adeed when the stage1
}
void Bomb::Update(float deltaTime) {
    Sprite::Update(deltaTime);
    OurGameScene* scene = getPlayScene();
    timer-=deltaTime;
    if(timer<=0){
        //
        OnExplode();
        scene->ClearBomb(Position.x,Position.y,CollisionRadius);
    }
}


