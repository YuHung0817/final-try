#include <allegro5/allegro.h>
#include <algorithm>
#include <random>
#include <cmath>
#include <fstream>
#include <functional>
#include <vector>
#include <queue>
#include <string>
#include <memory>
#include <iostream>
#include <array>

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
#include "UI/Animation/Plane.hpp"
#include "Scene/OurGameScene.hpp"
#include "Scene/PotionStoreScene.h"
#include "Engine/Resources.hpp"
#include "Turret/TurretButton.hpp"
#include "Engine/IScene.hpp"
#include "Engine/Point.hpp"
#include "Bomb/Bomb.hpp"
#include "Bomb/Bomb1.hpp"
#include "Bomb/FireEffect.hpp"
#include "Bomb/FirearmEffect.hpp"
#include "Bomb/HammerEffect.hpp"
#include "Instrument/Instrument.hpp"
#include "Instrument/Box.hpp"
#include "Instrument/Firearm.hpp"
#include "Instrument/Bubble.hpp"
#include "Instrument/Hammer.hpp"
#include "Instrument/ToolBomb.hpp"

int OurGameScene::winner=0;
float OurGameScene::timer1=0;
float OurGameScene::timer2=0;
float OurGameScene::timer3=0;
float OurGameScene::timer4=0;
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

PotionStoreScene* getPotionScene() {
    return dynamic_cast<PotionStoreScene*>(Engine::GameEngine::GetInstance().GetScene("potion-store"));
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
    //SpeedMult = 1;
    // Add groups from bottom to top.
    AddNewObject(TileMapGroup = new Group());
    AddNewObject(GroundEffectGroup = new Group());
    AddNewObject(DebugIndicatorGroup = new Group());
    AddNewObject(BombGroup = new Group());
    AddNewObject(FireEffectGroup = new Group());
    AddNewObject(FirearmEffectGroup = new Group());
    AddNewObject(HammerEffectGroup = new Group());
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
    UILive=NULL;
    UILive2=NULL;
    // Preload Lose Scene
    deathBGMInstance = Engine::Resources::GetInstance().GetSampleInstance("lose.wav");
    Engine::Resources::GetInstance().GetBitmap("lose/benjamin-happy.png");
    // Start BGM.
    bgmId = AudioHelper::PlayBGM("farming.wav");

    //add new role
    role1 = new Role1(1 * BlockSize, 1 * BlockSize);
    RoleGroup->AddNewObject(role1);
    //add new role
    role2 = new Role2(23 * BlockSize, 11 * BlockSize);
    RoleGroup->AddNewObject(role2);

    role1->init();
    role2->init();
    SetRole1();
    SetRole2();

    if(role1->speedMult<=0) role1->speedMult=1;
    if(role2->speedMult<=0) role2->speedMult=1;

}

void OurGameScene::SetRole1(){
    if(getPotionScene()->GetPotionNumber(1,1)>0){
        int T=getPotionScene()->GetPotionNumber(1,1);
        while(T--){
            role1->speedMult*=2;
        }
    }
    if(getPotionScene()->GetPotionNumber(1,0)>0){
        int T=getPotionScene()->GetPotionNumber(1,0);
        while(T--){
            role1->live+=1;
        }
    }
    if(getPotionScene()->GetPotionNumber(1,2)>0){
        int T=getPotionScene()->GetPotionNumber(1,2);
        while(T--){
            role2->speedMult-=1;
        }
    }
}
void OurGameScene::SetRole2(){
    if(getPotionScene()->GetPotionNumber(2,1)>0){
        int T=getPotionScene()->GetPotionNumber(2,1);
        while(T--){
            role2->speedMult*=2;
        }
    }
    if(getPotionScene()->GetPotionNumber(2,0)>0){
        int T=getPotionScene()->GetPotionNumber(2,0);
        while(T--){
            role2->live+=1;
        }
    }
    if(getPotionScene()->GetPotionNumber(2,2)>0){
        int T=getPotionScene()->GetPotionNumber(2,2);
        while(T--){
            role1->speedMult-=1;
        }
    }
}
void OurGameScene::Terminate() {
    AudioHelper::StopBGM(bgmId);
    AudioHelper::StopSample(deathBGMInstance);
    deathBGMInstance = std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE>();
    IScene::Terminate();
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

void OurGameScene::Update(float deltaTime) {
    timer3-=deltaTime;
    timer4-=deltaTime;
    if(timer3<=3.0 && UILive!=NULL){
        UIGroup->RemoveObject(UILive->GetObjectIterator());
        UILive=NULL;
    }
    if(timer4<=3.0 && UILive2!=NULL){
        UIGroup->RemoveObject(UILive2->GetObjectIterator());
        UILive2=NULL;
    }

    //std::cout<<"timer3: "<<timer3<<" timer4: "<<timer4<<std::endl;
    IScene::Update(deltaTime);

    // Update roles
    role1->Update(deltaTime);
    role2->Update(deltaTime);
    timer1+=deltaTime*(role1->speedMult);
    timer2+=deltaTime*(role2->speedMult);
    // Continuous key handling for role1
    if(timer1>=0.3) {
        if (keys[ALLEGRO_KEY_UP]) {
            int newX = role1->Position.x;
            int newY = role1->Position.y - BlockSize/4;
            if (CheckSpaceValid(newX, newY)) {
                role1->SetDir(3);
                role1->change = true;
                role1->Position.y -= BlockSize/4;
                TakeTool(role1);
            }
        }
        if (keys[ALLEGRO_KEY_DOWN]) {
            int newX = role1->Position.x;
            int newY = role1->Position.y + BlockSize/4;
            if (CheckSpaceValid(newX, newY)) {
                role1->SetDir(2);
                role1->change = true;
                role1->Position.y += BlockSize/4;
                TakeTool(role1);
            }
        }
        if (keys[ALLEGRO_KEY_LEFT]) {
            int newX = role1->Position.x - BlockSize/4;
            int newY = role1->Position.y;
            if (CheckSpaceValid(newX, newY)) {
                role1->SetDir(0);
                role1->change = true;
                role1->Position.x -= BlockSize/4;
                TakeTool(role1);
            }
        }
        if (keys[ALLEGRO_KEY_RIGHT]) {
            int newX = role1->Position.x + BlockSize/4;
            int newY = role1->Position.y;
            if (CheckSpaceValid(newX, newY)) {
                role1->SetDir(1);
                role1->change = true;
                role1->Position.x += BlockSize/4;
                TakeTool(role1);
            }
        }
        timer1=0;
    }
    if(timer2>=0.3){
        // Continuous key handling for role2
        if (keys[ALLEGRO_KEY_W]) {
            int newX = role2->Position.x;
            int newY = role2->Position.y - BlockSize/4 ;
            if (CheckSpaceValid(newX, newY)) {
                role2->SetDir(3);
                role2->change = true;
                role2->Position.y -= BlockSize/4;
                TakeTool(role2);
            }
        }
        if (keys[ALLEGRO_KEY_S]) {
            int newX = role2->Position.x;
            int newY = role2->Position.y + BlockSize/4;
            if (CheckSpaceValid(newX, newY)) {
                role2->SetDir(2);
                role2->change = true;
                role2->Position.y += BlockSize/4;
                TakeTool(role2);
            }
        }
        if (keys[ALLEGRO_KEY_A]) {
            int newX = role2->Position.x - BlockSize/4;
            int newY = role2->Position.y;
            if (CheckSpaceValid(newX, newY)) {
                role2->SetDir(0);
                role2->change = true;
                role2->Position.x -= BlockSize/4 ;
                TakeTool(role2);
            }
        }
        if (keys[ALLEGRO_KEY_D]) {
            int newX = role2->Position.x + BlockSize/4 ;
            int newY = role2->Position.y;
            if (CheckSpaceValid(newX, newY)) {
                role2->SetDir(1);
                role2->change = true;
                role2->Position.x += BlockSize/4;
                TakeTool(role2);
            }
        }
        timer2=0;
    }

}
void OurGameScene::OnKeyDown(int keyCode) {
    keys[keyCode] = true;
    // Check code
    keyStrokes.push_back(keyCode);
    if (keyStrokes.size() > code.size()) {
        keyStrokes.pop_front();
    }
    if (std::deque<int>(keyStrokes.begin(), keyStrokes.end()) == std::deque<int>(code.begin(), code.end())) {
        EffectGroup->AddNewObject(new Plane());
        keyStrokes.clear();
    }
    if (keyCode== ALLEGRO_KEY_ENTER){
        //no other on the hand ,put bomb
        //or put the first get tool
        std::string tmp=role1->UseTool();
        if(tmp=="") PutBomb(role1->Position.x,role1->Position.y,role1);
        else if(tmp=="Firearm"){
            firearmEffect(role1->Position.x,role1->Position.y,role1);
        }else if(tmp=="Hammer"){
            hammerEffect(role1->Position.x,role1->Position.y,role1);
        }
    }
    if(keyCode ==ALLEGRO_KEY_SPACE){

        std::string tmp=role2->UseTool();
        if(tmp=="") PutBomb(role2->Position.x,role2->Position.y,role2);
        else if(tmp=="Firearm"){
            firearmEffect(role2->Position.x,role2->Position.y,role2);
        }else if(tmp=="Hammer"){
            hammerEffect(role2->Position.x,role2->Position.y,role2);
        }
    }

    if (keyCode >= ALLEGRO_KEY_0 && keyCode <= ALLEGRO_KEY_9) {
        // Hotkey for Speed up.
        SpeedMult = keyCode - ALLEGRO_KEY_0;
    }
}

void OurGameScene::OnKeyUp(int keyCode) {
    keys[keyCode] = false;
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
    ValidState = std::vector<std::vector<bool>>(MapHeight*4 , std::vector<bool>(MapWidth*4));
    for (int i = 0; i < MapHeight; i++) {
        for (int j = 0; j < MapWidth; j++) {
            const int num = mapData[i * MapWidth + j];



           // mapState[i][j] = num ? TILE_FLOOR : TILE_DIRT;
           //chage to the following
            for(int p=0;p<4;p++) {
                for(int q=0;q<4;q++) {
                    ValidState[i*4+p][j*4+q] = true;
                }
            }

            if(num==0) {
                mapState[i][j] = TILE_FLOOR;
            }
            else if(num==1) {
                mapState[i][j] = TILE_WALL;
                for(int p=0;p<4;p++) {
                    for(int q=0;q<4;q++) {
                        ValidState[i*4+p][j*4+q] = false;
                    }
                }
            }
            else if(num==2) mapState[i][j]=TILE_OCCUPIED;
            else if(num==3) mapState[i][j]=TILE_TOOL_BOMB;
            else if(num==4) mapState[i][j]=TILE_TOOL_FIREARM;
            else if(num==5) mapState[i][j]=TILE_TOOL_HAMMER;
            else{
                mapState[i][j]=TILE_BLOCK;
                //64/8=8
                for(int p=0;p<4;p++) {
                    for(int q=0;q<4;q++) {
                        ValidState[i*4+p][j*4+q] = false;
                    }
                }
            }



            TileMapGroup->AddNewObject(new Engine::Image("our_game/floor7.png", j * BlockSize, i * BlockSize, BlockSize, BlockSize));
            if(num==0){
               // TileMapGroup->AddNewObject(new Engine::Image("our_game/snow.png", j * BlockSize, i * BlockSize, BlockSize, BlockSize));
            }else if(num==1) {
                //wall
                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_int_distribution<> dis(1, 8);
                int random_number = dis(gen);
                std::string random_number_str = std::to_string(random_number);
                std::string flower_wall="our_game/flower"+random_number_str+".png";
                TileMapGroup->AddNewObject(new Engine::Image(flower_wall, j * BlockSize, i * BlockSize, BlockSize, BlockSize));
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
                /*std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_int_distribution<> dis(1, 3);
                int random_number = dis(gen);
                std::string random_number_str = std::to_string(random_number);
                std::string box_home="our_game/home"+random_number_str+".png";*/
                Box* box=new Box("our_game/scarecrow4.png",j * BlockSize+40, i * BlockSize+28);
                InstrumentGroup->AddNewObject(box);
                mapBox[i][j]= box;

            }
        }
    }
}

void OurGameScene::ConstructUI() {
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int shift = 135 + 25;
    dangerIndicator = new Engine::Sprite("play/benjamin.png", w - shift, h - shift);
    dangerIndicator->Tint.a = 0;
    UIGroup->AddNewObject(dangerIndicator);
}

//should be changed to check wheather the space can go through, if tool or wall there can't go but the enemy can go
bool OurGameScene::CheckSpaceValid(int x, int y) {
   // if(x/64)
    int q=x/16;
    int p=y/16;
    int i=y/64;
    int j=x/64;

    if (i > 0 && j > 0 && j < 24 && i < 12) {
        /*if (mapState[p][q] == TILE_FLOOR || mapState[p][q] == TILE_OCCUPIED ||
            mapState[p][q] == TILE_TOOL_FIREARM || mapState[p][q] == TILE_TOOL_BOMB ||
            mapState[p][q] == TILE_TOOL_HAMMER) {
            return true;
        }*/
        if( ValidState[p][q] ) return true;
    }

    return false;
}

void OurGameScene::PutBomb(int x,int y,Role* r){
    //set the mapState[i][j] to TILE_OCCUPIED
    int i=y/64;
    int j=x/64;
    mapState[i][j]=TILE_OCCUPIED;
    //
    Bomb1* bomb=new Bomb1(j*64+40,i*64+40,3.0);
    std::cout<<"r->bombRange: "<<r->bombRange<<std::endl;
    bomb->CollisionRadius=r->bombRange;
    BombGroup->AddNewObject(bomb);

}
void OurGameScene::ClearBomb(int x,int y,int radius){
    int i=y/64;
    int j=x/64;
    mapState[i][j]=TILE_FLOOR;
    FireEffect* fireeffect=new FireEffect(j*64+40,i*64+40,1.0);
    FireEffectGroup->AddNewObject(fireeffect);
    int dir[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
    for(int k=0;k<4;k++){
        int I=i;
        int J=j;
        for(int h=0;h<radius;h++) {
            I +=  dir[k][0];
            J += dir[k][1];
            if (I > 0 && J > 0 && I < 13 && J < 25) {
                //check the player
                if(mapState[I][J]!=TILE_WALL){
                    FireEffect* fireeffect=new FireEffect(J*64+40,I*64+40,1.0);
                    FireEffectGroup->AddNewObject(fireeffect);
                }else break;
                CheckDie(I,J);

                if (mapState[I][J] == TILE_BLOCK) {
                    Box* tmp=mapBox[I][J];
                    InstrumentGroup->RemoveObject(tmp->GetObjectIterator());
                    mapState[I][J] = TILE_FLOOR;
                    for(int p=0;p<4;p++){
                        for(int q=0;q<4;q++){
                            ValidState[I*4+p][J*4+q]=true;
                        }
                    }
                    //break;
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

        r->gettool("Firearm");
    }
    else if(mapState[i][j] == TILE_TOOL_HAMMER){
        Hammer* tmp=mapHammer[i][j];
        InstrumentGroup->RemoveObject(tmp->GetObjectIterator());
        mapState[i][j]=TILE_FLOOR;

        Bubble* tmp2=mapBubble[i][j];
        InstrumentGroup->RemoveObject(tmp2->GetObjectIterator());

        r->gettool("Hammer");
    }
    else if(mapState[i][j] == TILE_TOOL_BOMB){
        ToolBomb* tmp=mapToolBomb[i][j];
        InstrumentGroup->RemoveObject(tmp->GetObjectIterator());
        mapState[i][j]=TILE_FLOOR;

        Bubble* tmp2=mapBubble[i][j];
        InstrumentGroup->RemoveObject(tmp2->GetObjectIterator());

        r->gettool("ToolBomb");
    }
}
void OurGameScene::CheckDie(int i,int j){
    std::cout<<"check\n";
    std::cout<<"timer4: "<<timer4<<std::endl;
    int x_l=j*64-32;
    int x_r=j*64+32;
    int y_u=i*64-32;
    int y_d=i*64+32;
    int same1=0;
    int same2=0;
    if((role1->Position.x >= x_l  && role1->Position.x <= x_r )&& (role1->Position.y >= y_u && role1->Position.y <= y_d)){
        std::cout<<"live:"<<role1->live<<std::endl;
        if(role1->live>0 && timer3<=0) {
            timer3=5.0;
            UIGroup->AddNewObject(UILive = new Engine::Label( std::to_string(role2->live), "pirulen.ttf", 40, role1->Position.x, role1->Position.y));
            role1->live--;
            UILive->Text =   std::to_string(role1->live);
            AudioHelper::PlayAudio("life.wav");
        }
        else if(role1->live<1){
            winner=2;
            //Engine::GameEngine::GetInstance().ChangeScene("lose");
            same1=1;
        }
    }
    if((role2->Position.x >= x_l  && role2->Position.x <= x_r )&& (role2->Position.y >= y_u && role2->Position.y <= y_d)){
        std::cout<<"live:"<<role2->live<<std::endl;
        if(role2->live>0 && timer4<=0) {
            timer4=5.0;
            UIGroup->AddNewObject(UILive2 = new Engine::Label( std::to_string(role2->live), "pirulen.ttf", 40, role2->Position.x, role2->Position.y));
            role2->live--;
            AudioHelper::PlayAudio("life.wav");
            UILive2->Text =   std::to_string(role2->live);
            //UIGroup->RemoveObject(UILive->GetObjectIterator());
        }
        else if(role2->live<1) {
            winner=1;
            //Engine::GameEngine::GetInstance().ChangeScene("lose");
            same2=1;
        }
    }
    if(same1 && same2){
        winner=0;
        Engine::GameEngine::GetInstance().ChangeScene("lose");
    }else if(same1 || same2){
        Engine::GameEngine::GetInstance().ChangeScene("lose");
    }

}

void OurGameScene::firearmEffect(int x,int y,Role* r){
    std::cout<<"firearmEffect function\n";
    int j=x/64;
    int i=y/64;
    int T=3;
    int d=r->ReturnDir();
    int i_d,j_d;

    if(d==0){
        //left
        i_d=0; j_d=-1;
    }else if(d==1){
        //right
        i_d=0; j_d=1;
    }else if(d==2){
        //down
        i_d=1; j_d=0;
    }else if(d==3){
        //up
        i_d=-1; j_d=0;
    }
    i+=i_d;
    j+=j_d;
    while(T--){
        i+=i_d;
        j+=j_d;
        if(mapState[i][j]!=TILE_WALL){
            FirearmEffect* firearmeffect=new FirearmEffect(j*64+40,i*64+40,3.0);
            FirearmEffectGroup->AddNewObject(firearmeffect);
        }
        //CheckDie(i,j);

        if (mapState[i][j] == TILE_BLOCK) {
            Box* tmp=mapBox[i][j];
            InstrumentGroup->RemoveObject(tmp->GetObjectIterator());
            mapState[i][j] = TILE_FLOOR;
            for(int p=0;p<4;p++){
                for(int q=0;q<4;q++){
                    ValidState[i*4+p][j*4+q]=true;
                }
            }
           // break;
        }
        //else break;
    }
}

void OurGameScene::hammerEffect(int x,int y,Role* r){
    int j=x/64;
    int i=y/64;
    std::cout<<"ioioioi\n";
    int d=r->ReturnDir();
    int i_d,j_d;
    std::cout<<"ioioioi\n";
    if(d==0){
        //left
        i_d=0; j_d=-1;
    }else if(d==1){
        //right
        i_d=0; j_d=1;
    }else if(d==2){
        //down
        i_d=1; j_d=0;
    }else if(d==3){
        //up
        i_d=-1; j_d=0;
    }
    i+=i_d*2;
    j+=j_d*2;
    std::cout<<"Yes1\n";
    if(mapState[i][j]!=TILE_WALL){
        std::cout<<"Yes2\n";
        HammerEffect* hammereffect=new HammerEffect(j*64+40,i*64+40,4.0);
        HammerEffectGroup->AddNewObject(hammereffect);
    }

}
