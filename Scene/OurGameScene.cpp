//
// Created by IRIS0817 on 2024/6/11.
//
#include <allegro5/allegro.h>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <functional>
#include <vector>
#include <queue>
#include <string>
#include <memory>
#include <iostream>

#include "Engine/AudioHelper.hpp"
#include "UI/Animation/DirtyEffect.hpp"
#include "role/Role.hpp"
#include "role/Role1.hpp"
#include "role/Role2.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Group.hpp"
#include "UI/Component/Label.hpp"
#include "Turret/LaserTurret.hpp"
#include "Turret/MachineGunTurret.hpp"
#include "Turret/MissileTurret.hpp"
#include "Turret/Turret4.hpp"
#include "Turret/Turret5.hpp"
#include "Turret/Turret6.hpp"
#include "Turret/Turret7.hpp"
#include "UI/Animation/Plane.hpp"
#include "Scene/OurGameScene.hpp"
#include "Engine/Resources.hpp"
#include "Turret/TurretButton.hpp"
#include "tool/Resurrect.hpp"
#include "tool/ResurrectButton.hpp"
#include "Engine/IScene.hpp"
#include "Engine/Point.hpp"
#include "Bomb/Bomb.hpp"
#include "Bomb/Bomb1.hpp"
#include "Instrument/Instrument.hpp"
#include "Instrument/Box.hpp"
#include "Instrument/Firearm.hpp"
#include "Instrument/Bubble.hpp"
#include "Instrument/Hammer.hpp"
#include "Instrument/ToolBomb.hpp"

Box* OurGameScene::mapBox[25][13];
Firearm* OurGameScene::mapFirearm[25][13];
Bubble* OurGameScene::mapBubble[25][13];
Hammer* OurGameScene::mapHammer[25][13];
ToolBomb* OurGameScene::mapToolBomb[25][13];
bool OurGameScene::DebugMode = false;
const std::vector<Engine::Point> OurGameScene::directions = { Engine::Point(-1, 0), Engine::Point(0, -1), Engine::Point(1, 0), Engine::Point(0, 1) };
const int OurGameScene::MapWidth = 25, OurGameScene::MapHeight = 13;
const int OurGameScene::BlockSize = 64;
const Engine::Point OurGameScene::SpawnGridPoint = Engine::Point(-1, 0);
const Engine::Point OurGameScene::EndGridPoint = Engine::Point(MapWidth, MapHeight - 1);
const std::vector<int> OurGameScene::code = { ALLEGRO_KEY_UP, ALLEGRO_KEY_UP, ALLEGRO_KEY_DOWN, ALLEGRO_KEY_DOWN,
                                           ALLEGRO_KEY_LEFT, ALLEGRO_KEY_LEFT, ALLEGRO_KEY_RIGHT, ALLEGRO_KEY_RIGHT,
                                           ALLEGRO_KEY_B, ALLEGRO_KEY_A, ALLEGRO_KEYMOD_SHIFT, ALLEGRO_KEY_ENTER };
Engine::Point OurGameScene::GetClientSize() {
    return Engine::Point(MapWidth * BlockSize, MapHeight * BlockSize);
}
void OurGameScene::Initialize() {
    std::cout<<"to ourgame initialize\n";
    // TODO: [HACKATHON-3-BUG] (1/5): There's a bug in this file, which crashes the game when you lose. Try to find it.
    // TODO: [HACKATHON-3-BUG] (2/5): Find out the cheat code to test.
    // TODO: [HACKATHON-3-BUG] (2/5): It should generate a Plane, and add 10000 to the money, but it doesn't work now.
    mapState.clear();
    keyStrokes.clear();
    ticks = 0;
    deathCountDown = -1;
    SpeedMult = 1;
    // Add groups from bottom to top.
    AddNewObject(TileMapGroup = new Group());
    AddNewObject(GroundEffectGroup = new Group());
    AddNewObject(DebugIndicatorGroup = new Group());
    AddNewObject(BombGroup = new Group());
    AddNewObject(InstrumentGroup =new Group());
    AddNewObject(RoleGroup = new Group());
    AddNewObject(EffectGroup = new Group());
    // Should support buttons.
    AddNewControlObject(UIGroup = new Group());


    std::cout<<"to read map\n";
    ReadMap();
    ConstructUI();
    imgTarget = new Engine::Image("play/target.png", 0, 0);
    imgTarget->Visible = false;
    UIGroup->AddNewObject(imgTarget);
    // Preload Lose Scene
    deathBGMInstance = Engine::Resources::GetInstance().GetSampleInstance("astronomia.ogg");
    Engine::Resources::GetInstance().GetBitmap("lose/benjamin-happy.png");
    // Start BGM.
    bgmId = AudioHelper::PlayBGM("play.ogg");

    //add new role
    role1 = new Role1(1 * BlockSize+20+5, 1 * BlockSize+20+5+5);
    RoleGroup->AddNewObject(role1);
    //add new role
    role2 = new Role2(23 * BlockSize+20, 11 * BlockSize+20+10);
    RoleGroup->AddNewObject(role2);
}
void OurGameScene::Terminate() {
    AudioHelper::StopBGM(bgmId);
    AudioHelper::StopSample(deathBGMInstance);
    deathBGMInstance = std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE>();
    IScene::Terminate();
}

void OurGameScene::Update(float deltaTime) {
    IScene::Update(deltaTime);
    role1->Update(deltaTime);
    role2->Update(deltaTime);

}
void OurGameScene::Draw() const {
    IScene::Draw();
    if (DebugMode) {
        // Draw reverse BFS distance on all reachable blocks.
        for (int i = 0; i < MapHeight; i++) {
            for (int j = 0; j < MapWidth; j++) {
                if (mapState[i][j] == TILE_FLOOR) {
                    // Not elegant nor efficient, but it's quite enough for debugging.
                    //Engine::Label label(std::to_string(mapDistance[i][j]), "pirulen.ttf", 32, (j + 0.5) * BlockSize, (i + 0.5) * BlockSize);
                    //label.Anchor = Engine::Point(0.5, 0.5);
                    //label.Draw();
                }
            }
        }
    }
}
//we need to have the two roles,
//so ASDW,space and UpDownLeftRight,enter will need
void OurGameScene::OnKeyDown(int keyCode) {
    IScene::OnKeyDown(keyCode);
    if (keyCode == ALLEGRO_KEY_TAB) {
        DebugMode = !DebugMode;
    }
    /*******/
    if (keyCode == ALLEGRO_KEY_UP) {
        int newX=role1->Position.x;
        int newY=role1->Position.y-BlockSize;
        if(CheckSpaceValid(newX,newY)) {
            role1->Position.y -= BlockSize;
            TakeTool(role1);
        }
    } else if (keyCode == ALLEGRO_KEY_DOWN) {
        int newX=role1->Position.x;
        int newY=role1->Position.y+BlockSize;
        if(CheckSpaceValid(newX,newY)) {
            role1->Position.y += BlockSize;
            TakeTool(role1);
        }
    } else if (keyCode == ALLEGRO_KEY_LEFT) {
        int newX=role1->Position.x-BlockSize;
        int newY=role1->Position.y;
        if(CheckSpaceValid(newX,newY)) {
            role1->Position.x -= BlockSize;
            TakeTool(role1);
        }
    } else if (keyCode == ALLEGRO_KEY_RIGHT) {
        int newX=role1->Position.x+BlockSize;
        int newY=role1->Position.y;
        if(CheckSpaceValid(newX,newY)) {
            role1->Position.x += BlockSize;
            TakeTool(role1);
        }
    }else if (keyCode== ALLEGRO_KEY_ENTER){
    //no other on the hand ,put bomb
    //or put the first get tool
        PutBomb(role1->Position.x,role1->Position.y);
    }


     if (keyCode == ALLEGRO_KEY_W) {
        int newX=role2->Position.x;
        int newY=role2->Position.y-BlockSize;
        if(CheckSpaceValid(newX,newY)) {
            role2->Position.y -= BlockSize;
            TakeTool(role2);
        }
    } else if (keyCode == ALLEGRO_KEY_S) {
        int newX=role2->Position.x;
        int newY=role2->Position.y+BlockSize;
        if(CheckSpaceValid(newX,newY)) {
            role2->Position.y += BlockSize;
            TakeTool(role2);
        }
    } else if (keyCode == ALLEGRO_KEY_A) {
        int newX=role2->Position.x-BlockSize;
        int newY=role2->Position.y;
        if(CheckSpaceValid(newX,newY)) {
            role2->Position.x -= BlockSize;
            TakeTool(role2);
        }
    } else if (keyCode == ALLEGRO_KEY_D) {
        int newX=role2->Position.x+BlockSize;
        int newY=role2->Position.y;
        if(CheckSpaceValid(newX,newY)) {
            role2->Position.x += BlockSize;
            TakeTool(role2);
        }
    }else if(keyCode ==ALLEGRO_KEY_SPACE){
         PutBomb(role2->Position.x,role2->Position.y);
     }
    /**********/
        // TODO: [CUSTOM-TURRET]: Make specific key to create the turret.
    else if (keyCode >= ALLEGRO_KEY_0 && keyCode <= ALLEGRO_KEY_9) {
        // Hotkey for Speed up.
        SpeedMult = keyCode - ALLEGRO_KEY_0;
    }
}
//need but hte same problem to the next function
void OurGameScene::Hit() {

    if (0) {
        Engine::GameEngine::GetInstance().ChangeScene("lose-scene");
        //debug
        Engine::GameEngine::GetInstance().ChangeScene("lose");
    }
}

//done
void OurGameScene::ReadMap() {
    std::string filename = std::string("Resource/our_map")  + ".txt";
    // Read map file.
    char c;
    std::vector<int> mapData;
    std::ifstream fin(filename);
    while (fin >> c) {
        switch (c) {
            case '0': mapData.push_back(0); break;
            case '1': mapData.push_back(1); break;
            case '2': mapData.push_back(2); break;
            case '3': mapData.push_back(3); break;
            case '4': mapData.push_back(4); break;
            case '5': mapData.push_back(5); break;
            case '6': mapData.push_back(6); break;
            case '\n':
            case '\r':
                if (static_cast<int>(mapData.size()) / MapWidth != 0)
                    throw std::ios_base::failure("Map data is corrupted.");
                break;
            default: throw std::ios_base::failure("Map data is corrupted.");
        }
    }
    fin.close();
    // Validate map data.
    if (static_cast<int>(mapData.size()) != MapWidth * MapHeight)
        throw std::ios_base::failure("Map data is corrupted.");
    // Store map in 2d array.
    mapState = std::vector<std::vector<TileType>>(MapHeight, std::vector<TileType>(MapWidth));
    for (int i = 0; i < MapHeight; i++) {
        for (int j = 0; j < MapWidth; j++) {
            const int num = mapData[i * MapWidth + j];



           // mapState[i][j] = num ? TILE_FLOOR : TILE_DIRT;
           //chage to the following
            if(num==0) mapState[i][j]=TILE_FLOOR;
            else if(num==1) mapState[i][j]=TILE_WALL;
            else if(num==2) mapState[i][j]=TILE_OCCUPIED;
            else if(num==3) mapState[i][j]=TILE_TOOL_BOMB;
            else if(num==4) mapState[i][j]=TILE_TOOL_FIREARM;
            else if(num==5) mapState[i][j]=TILE_TOOL_HAMMER;
            else mapState[i][j]=TILE_BLOCK;


            if (num==0) {
                TileMapGroup->AddNewObject(new Engine::Image("our_game/floor.png", j * BlockSize, i * BlockSize, BlockSize, BlockSize));
            }else if(num==1) {
                TileMapGroup->AddNewObject(new Engine::Image("our_game/wall3.png", j * BlockSize, i * BlockSize, BlockSize, BlockSize));
            }else if(num==2){
                //TileMapGroup->AddNewObject(new Engine::Image("our_game/dirt.png", j * BlockSize, i * BlockSize, BlockSize, BlockSize));
            }else if(num==3){
                TileMapGroup->AddNewObject(new Engine::Image("our_game/floor.png", j * BlockSize, i * BlockSize, BlockSize, BlockSize));
                Bubble* bubble=new Bubble(j * BlockSize+40, i * BlockSize+28);
                InstrumentGroup->AddNewObject(bubble);
                mapBubble[i][j]=bubble;

                ToolBomb* toolbomb=new ToolBomb(j * BlockSize+40, i * BlockSize+28);
                InstrumentGroup->AddNewObject(toolbomb);
                mapToolBomb[i][j]=toolbomb;
            }else if(num==4){
                TileMapGroup->AddNewObject(new Engine::Image("our_game/floor.png", j * BlockSize, i * BlockSize, BlockSize, BlockSize));

                Bubble* bubble=new Bubble(j * BlockSize+40, i * BlockSize+28);
                InstrumentGroup->AddNewObject(bubble);
                mapBubble[i][j]=bubble;

                Firearm* firearm=new Firearm(j * BlockSize+40, i * BlockSize+28);
                InstrumentGroup->AddNewObject(firearm);
                mapFirearm[i][j]= firearm;
            }else if(num==5){
                TileMapGroup->AddNewObject(new Engine::Image("our_game/floor.png", j * BlockSize, i * BlockSize, BlockSize, BlockSize));
                Bubble* bubble=new Bubble(j * BlockSize+40, i * BlockSize+28);
                InstrumentGroup->AddNewObject(bubble);
                mapBubble[i][j]=bubble;

                Hammer* hammer=new Hammer(j * BlockSize+40, i * BlockSize+28);
                InstrumentGroup->AddNewObject(hammer);
                mapHammer[i][j]=hammer;
            }else if(num==6){
                TileMapGroup->AddNewObject(new Engine::Image("our_game/floor.png", j * BlockSize, i * BlockSize, BlockSize, BlockSize));
                Box* box=new Box(j * BlockSize+40, i * BlockSize+28);
                InstrumentGroup->AddNewObject(box);
                mapBox[i][j]= box;

            }
        }
    }
}

void OurGameScene::ConstructUI() {
    // Background
    // UIGroup->AddNewObject(new Engine::Image("play/sand.png", 1280, 0, 320, 832));
    // Text
    /*
    UIGroup->AddNewObject(new Engine::Label(std::string("Stage ") + std::to_string(MapId), "pirulen.ttf", 32, 1294, 0));
    UIGroup->AddNewObject(UIMoney = new Engine::Label(std::string("$") + std::to_string(money), "pirulen.ttf", 24, 1294, 48));
    UIGroup->AddNewObject(UILives = new Engine::Label(std::string("Life ") + std::to_string(lives), "pirulen.ttf", 24, 1294, 88));
    UIGroup->AddNewObject(UIScore = new Engine::Label(std::string("Score ") + std::to_string(score), "pirulen.ttf", 24, 1294, 128));
    TurretButton* btn;
*/
    // Button 1
    /*
    btn = new TurretButton("play/floor.png", "play/dirt.png",
                           Engine::Sprite("play/tower-base.png", 1294, 136+40, 0, 0, 0, 0),
                           Engine::Sprite("play/turret-1.png", 1294, 136 - 8+40, 0, 0, 0, 0)
            , 1294, 136+40, MachineGunTurret::Price);
    // Reference: Class Member Function Pointer and std::bind.
    btn->SetOnClickCallback(std::bind(&PlayScene::UIBtnClicked, this, 0));
    UIGroup->AddNewControlObject(btn);
    // Button 2
    btn = new TurretButton("play/floor.png", "play/dirt.png",
                           Engine::Sprite("play/tower-base.png", 1370, 136+40, 0, 0, 0, 0),
                           Engine::Sprite("play/turret-2.png", 1370, 136 - 8+40, 0, 0, 0, 0)
            , 1370, 136+40, LaserTurret::Price);
    btn->SetOnClickCallback(std::bind(&PlayScene::UIBtnClicked, this, 1));
    UIGroup->AddNewControlObject(btn);
    // Button 3
    btn = new TurretButton("play/floor.png", "play/dirt.png",
                           Engine::Sprite("play/tower-base.png", 1446, 136+40, 0, 0, 0, 0),
                           Engine::Sprite("play/turret-3.png", 1446, 136+40, 0, 0, 0, 0)
            , 1446, 136+40, MissileTurret::Price);
    btn->SetOnClickCallback(std::bind(&PlayScene::UIBtnClicked, this, 2));
    UIGroup->AddNewControlObject(btn);
    // TODO: [CUSTOM-TURRET]: Create a button to support constructing the turret.
    //button 4
    btn = new TurretButton("play/floor.png", "play/dirt.png",
                           Engine::Sprite("play/tower-base.png", 1522, 136+40, 0, 0, 0, 0),
                           Engine::Sprite("play/turret-4.png", 1522, 136+40, 0, 0, 0, 0)
            , 1522, 136+40, Turret4::Price);
    btn->SetOnClickCallback(std::bind(&PlayScene::UIBtnClicked, this, 3));
    UIGroup->AddNewControlObject(btn);
    //button 5
    btn = new TurretButton("play/floor.png", "play/dirt.png",
                           Engine::Sprite("play/tower-base.png", 1294, 212+40, 0, 0, 0, 0),
                           Engine::Sprite("play/turret-5.png", 1294, 212+40, 0, 0, 0, 0)
            , 1294, 212+40, Turret5::Price);
    btn->SetOnClickCallback(std::bind(&PlayScene::UIBtnClicked, this, 4));
    UIGroup->AddNewControlObject(btn);
    //button 6
    btn = new TurretButton("play/floor.png", "play/dirt.png",
                           Engine::Sprite("play/tower-base.png", 1370, 212+40, 0, 0, 0, 0),
                           Engine::Sprite("play/turret-6.png", 1370, 212+40, 0, 0, 0, 0)
            , 1370, 212+40, Turret6::Price);
    btn->SetOnClickCallback(std::bind(&PlayScene::UIBtnClicked, this, 5));
    UIGroup->AddNewControlObject(btn);
    //button 7
    btn = new TurretButton("play/floor.png", "play/dirt.png",
                           Engine::Sprite("play/tower-base.png", 1446, 212+40, 0, 0, 0, 0),
                           Engine::Sprite("play/turret-7.png", 1446, 212+40, 0, 0, 0, 0)
            , 1446, 212+40, Turret7::Price);
    btn->SetOnClickCallback(std::bind(&PlayScene::UIBtnClicked, this, 6));
    UIGroup->AddNewControlObject(btn);

    ResurrectButton* btn2;
    //button 8 for tool to resurrect
    btn2 = new ResurrectButton("play/floor.png", "play/dirt.png",
                               Engine::Sprite("play/tower-base.png", 1294+130, 68, 0, 0, 0, 0),
                               Engine::Sprite("play/resurrect.png", 1294+130, 68, 0, 0, 0, 0)
            , 1294+130, 68, Resurrect::Price);
    btn2->SetOnClickCallback(std::bind(&PlayScene::ResurrectOnclick, this));
    UIGroup->AddNewControlObject(btn2);
*/

//the tool on the map can be taken when the player on the same font



    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int shift = 135 + 25;
    dangerIndicator = new Engine::Sprite("play/benjamin.png", w - shift, h - shift);
    dangerIndicator->Tint.a = 0;
    UIGroup->AddNewObject(dangerIndicator);
}

//should be changed to check wheather the space can go through, if tool or wall there can't go but the enemy can go
bool OurGameScene::CheckSpaceValid(int x, int y) {
    int j=x/64;
    int i=y/64;
    std::cout<<"i = "<<i<<" j= "<<j<<std::endl;
    if(/*mapState[i][j]==TILE_FLOOR &&*/ i>0 && j>0 && j<24 && i<12 ) {
        if(mapState[i][j]==TILE_FLOOR || mapState[i][j]==TILE_TOOL_FIREARM || mapState[i][j]==TILE_TOOL_BOMB || mapState[i][j]==TILE_TOOL_HAMMER) {
            return true;
        }
    }
    return false;
}

void OurGameScene::PutBomb(int x,int y){
    //set the mapState[i][j] to TILE_OCCUPIED
    int i=y/64;
    int j=x/64;
    mapState[i][j]=TILE_OCCUPIED;
    //
    Bomb1* bomb=new Bomb1(x,y);
    BombGroup->AddNewObject(bomb);

}
void OurGameScene::ClearBomb(int x,int y,int radius){
    int i=y/64;
    int j=x/64;
    mapState[i][j]=TILE_FLOOR;
    int dir[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
    for(int k=0;k<4;k++){
        int I=i;
        int J=j;
        for(int h=0;h<radius;h++) {
            I +=  dir[k][0];
            J += dir[k][1];
            if (I > 0 && J > 0 && I < 13 && J < 25) {
                //check the player
                CheckDie(I,J);
                if (mapState[I][J] == TILE_BLOCK) {
                    std::cout<<"to remove\n";
                    Box* tmp=mapBox[I][J];
                    InstrumentGroup->RemoveObject(tmp->GetObjectIterator());
                    mapState[I][J] = TILE_FLOOR;
                }
            }
        }
    }
}
void OurGameScene::TakeTool(Role* r){
    int i=r->Position.y/64;
    int j=r->Position.x/64;
    if(mapState[i][j] == TILE_TOOL_FIREARM){
        Firearm* tmp=mapFirearm[i][j];
        InstrumentGroup->RemoveObject(tmp->GetObjectIterator());
        mapState[i][j]=TILE_FLOOR;

        Bubble* tmp2=mapBubble[i][j];
        InstrumentGroup->RemoveObject(tmp2->GetObjectIterator());
    }
    else if(mapState[i][j] == TILE_TOOL_HAMMER){
        Hammer* tmp=mapHammer[i][j];
        InstrumentGroup->RemoveObject(tmp->GetObjectIterator());
        mapState[i][j]=TILE_FLOOR;

        Bubble* tmp2=mapBubble[i][j];
        InstrumentGroup->RemoveObject(tmp2->GetObjectIterator());
    }
    else if(mapState[i][j] == TILE_TOOL_BOMB){
        ToolBomb* tmp=mapToolBomb[i][j];
        InstrumentGroup->RemoveObject(tmp->GetObjectIterator());
        mapState[i][j]=TILE_FLOOR;

        Bubble* tmp2=mapBubble[i][j];
        InstrumentGroup->RemoveObject(tmp2->GetObjectIterator());
    }
}
void OurGameScene::CheckDie(int i,int j){
    int x_l=j*64-32;
    int x_r=j*64+32;
    int y_u=i*64-32;
    int y_d=i*64+32;
    std::cout<<"x= "<<x_l<<" y="<<y_u<<std::endl;
    std::cout<<"role1->Position.x"<<role1->Position.x;
    std::cout<<"   role1->Position.y"<<role1->Position.y;
    std::cout<<std::endl;
    if((role1->Position.x >= x_l  && role1->Position.x <= x_r )&& (role1->Position.y >= y_u && role1->Position.y <= y_d)){
        Engine::GameEngine::GetInstance().ChangeScene("lose");
    }
    if((role2->Position.x >= x_l  && role2->Position.x <= x_r )&& (role2->Position.y >= y_u && role2->Position.y <= y_d)){
        Engine::GameEngine::GetInstance().ChangeScene("lose");
    }
}