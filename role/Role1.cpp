//
// Created by IRIS0817 on 2024/6/12.
//
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
#include "Role1.hpp"
#include "Role.hpp"
//Role1
int Role1::offset=0;
int Role1::frameIndex=0;
int Role1::dir=0;
bool Role1::change=false;
Role1::Role1(int x, int y) : Role("our_game/role1.png", x, y, 10, 50, 30, 30) {}
void Role1::Draw() const{
    if(change) {
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
                          Position.x - frameWidth / 2, Position.y - frameHeight / 2,
                          frameWidth-10, frameHeight-10, 0);

    //Sprite::Draw();
    if (OurGameScene::DebugMode) {
        // Draw collision radius.
        al_draw_circle(Position.x, Position.y, CollisionRadius, al_map_rgb(255, 0, 0), 2);
    }
}

void Role1::SetDir(int i){
    dir=i;
}
int Role1::ReturnDir(){
    return dir;
}