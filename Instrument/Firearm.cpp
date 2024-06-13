//
// Created by IRIS0817 on 2024/6/13.
//
#include <cmath>
#include <random>
#include <string>
#include <utility>
#include <iostream>

#include "UI/Animation/DirtyEffect.hpp"
#include "Engine/Group.hpp"
#include "Engine/IObject.hpp"
#include "Firearm.hpp"
#include "Scene/OurGameScene.hpp"
#include "Engine/Point.hpp"
//Box

Firearm::Firearm(int x,int y) :
        Instrument("our_game/firearm.png", x,y) {
}
void Firearm::OnExplode() {
}

void Firearm::Update(float deltaTime) {

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



