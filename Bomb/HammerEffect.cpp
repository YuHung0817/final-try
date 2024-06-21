//
// Created by IRIS0817 on 2024/6/14.
//
#include <cmath>
#include <random>
#include <string>
#include <utility>
#include <iostream>
#include <allegro5/allegro_primitives.h>
#include <allegro5/color.h>

#include "UI/Animation/DirtyEffect.hpp"
#include "Engine/Group.hpp"
#include "Engine/IObject.hpp"
#include "HammerEffect.hpp"
#include "Scene/OurGameScene.hpp"
#include "Engine/Point.hpp"


bool HammerEffect::change=false;
float HammerEffect::ticks=0;
int HammerEffect::offset=0;
int HammerEffect::frameIndex=0;
HammerEffect::HammerEffect(int x,int y,int t) :
        Bomb("our_game/hammereffect.png", x,y,t){
}
void HammerEffect::OnExplode() {
}

void HammerEffect::Update(float deltaTime) {
    //for animax
    timer-=deltaTime;
    ticks+=deltaTime;
    if(ticks>=0.5) {
        change=true;
        ticks=0;
    }

    //for remove
    Sprite::Update(deltaTime);
    OurGameScene* scene = getPlayScene();
    if(timer<=0){
        //
        std::cout<<"time=0\n";
        OnExplode();
        getPlayScene()->FireEffectGroup->RemoveObject(objectIterator);
        //scene->ClearBomb(Position.x,Position.y,CollisionRadius);
    }
}
void HammerEffect::Draw() const{
    int frameWidth = 64;
    int frameHeight = 142;
    if(change) {
        frameIndex++;
        frameIndex %= 8;
        change=false;
        if(frameIndex==4 || frameIndex==5){
            frameHeight=100;
        }
    }
    offset = frameIndex * 64;

    al_draw_scaled_bitmap(bmp.get(),  0+ offset, 0, frameWidth, frameHeight,
                          Position.x - frameWidth / 2, Position.y - frameHeight / 2,
                          frameWidth-10, frameHeight-10, 0);

    //Sprite::Draw();
    if (OurGameScene::DebugMode) {
        // Draw collision radius.
        al_draw_circle(Position.x, Position.y, CollisionRadius, al_map_rgb(255, 0, 0), 2);
    }
}




