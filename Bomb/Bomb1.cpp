//
// Created by IRIS0817 on 2024/6/12.
//
#include <cmath>
#include <random>
#include <string>
#include <utility>
#include <iostream>
#include "Engine/AudioHelper.hpp"
#include "UI/Animation/DirtyEffect.hpp"
#include "Engine/Group.hpp"
#include "Engine/IObject.hpp"
#include "Bomb1.hpp"
#include "Scene/OurGameScene.hpp"
#include "Engine/Point.hpp"
//Bomb1

Bomb1::Bomb1(int x,int y,int t) :
        Bomb("our_game/bomb2.png", x,y,t) {
        AudioHelper::PlayAudio("placebomb.wav");
}
void Bomb1::OnExplode() {
}

void Bomb1::Update(float deltaTime) {
    //std::cout<<"here\n";
    Sprite::Update(deltaTime);
    OurGameScene* scene = getPlayScene();
    //std::cout<<"timer:"<<timer;
    timer-=deltaTime;

    if(timer<=0){
        //
        std::cout<<"time=0\n";
        OnExplode();
        getPlayScene()->BombGroup->RemoveObject(objectIterator);
        scene->ClearBomb(Position.x,Position.y,CollisionRadius);
        AudioHelper::PlayAudio("placebomb.wav");
    }
}



