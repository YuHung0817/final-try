//
// Created by IRIS0817 on 2024/6/12.
//
#include <cmath>
#include <random>
#include <string>
#include <utility>
#include <iostream>

#include "UI/Animation/DirtyEffect.hpp"
#include "Engine/Group.hpp"
#include "Engine/IObject.hpp"
#include "Box.hpp"
#include "Scene/OurGameScene.hpp"
#include "Engine/Point.hpp"
//Box

Box::Box(int x,int y) :
        Instrument("our_game/box.png", x,y) {
}
void Box::OnExplode() {
}

void Box::Update(float deltaTime) {

    Sprite::Update(deltaTime);/*
    OurGameScene* scene = getPlayScene();
    std::cout<<"timer:"<<timer;
    timer-=deltaTime;

    if(timer<=0){
        //
        std::cout<<"time=0\n";
        OnExplode();
        getPlayScene()->BombGroup->RemoveObject(objectIterator);
        scene->ClearBomb(Position.x,Position.y,CollisionRadius);
    }*/
}



