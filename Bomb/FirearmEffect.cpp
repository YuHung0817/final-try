//
// Created by IRIS0817 on 2024/6/12.
//
#include <cmath>
#include <random>
#include <string>
#include <utility>
#include <iostream>
#include <allegro5/allegro_primitives.h>
#include <allegro5/color.h>
#include "Engine/AudioHelper.hpp"
#include "UI/Animation/DirtyEffect.hpp"
#include "Engine/Group.hpp"
#include "Engine/IObject.hpp"
#include "FirearmEffect.hpp"
#include "Scene/OurGameScene.hpp"
#include "Engine/Point.hpp"

bool FirearmEffect::change=false;
float FirearmEffect::ticks=0;
int FirearmEffect::offset=0;
int FirearmEffect::frameIndex=0;
FirearmEffect::FirearmEffect(int x,int y,int t) :
        Bomb("our_game/firearmeffect2.png", x,y,t) {
            AudioHelper::PlayAudio("lasar.wav");
}
void FirearmEffect::OnExplode() {
}

void FirearmEffect::Update(float deltaTime) {
    //for animax
    timer-=deltaTime;
    ticks+=deltaTime;
    if(ticks>=1.0) {
        change=true;
        ticks=0;
    }

    //for remove
    Sprite::Update(deltaTime);
    OurGameScene* scene = getPlayScene();

    if(timer<=2.5){
        int i=Position.y/64;
        int j=Position.x/64;
        scene->CheckDie(i,j);
    }
    if(timer<=0){
        //
        std::cout<<"time=0\n";
        OnExplode();
        
        getPlayScene()->FirearmEffectGroup->RemoveObject(objectIterator);
        //scene->ClearBomb(Position.x,Position.y,CollisionRadius);
    }
}
void FirearmEffect::Draw() const{
    if(change) {
        frameIndex++;
        frameIndex %= 4;
        change=false;
    }
    offset = frameIndex * 64;
    std::cout<<"offset: "<<offset<<std::endl;
    int frameWidth = 64;
    int frameHeight = 63;
    al_draw_scaled_bitmap(bmp.get(),  0+ offset, 0, frameWidth, frameHeight,
                          Position.x - frameWidth / 2, Position.y - frameHeight / 2,
                          frameWidth-10, frameHeight-10, 0);

    //Sprite::Draw();
    if (OurGameScene::DebugMode) {
        // Draw collision radius.
        al_draw_circle(Position.x, Position.y, CollisionRadius, al_map_rgb(255, 0, 0), 2);
    }
}




