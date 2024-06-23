#include "SeedStoreScene.h"
#include <functional>
#include <string>
#include <fstream>
#include <sstream>
#include "Engine/GameEngine.hpp"
#include "UI/Component/Image.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Window.h"
#include "UI/Component/Label.hpp"
#include "LoseScene.hpp"
#include "PlayScene.hpp"
#include "Engine/Point.hpp"
#include "Engine/LOG.hpp"



void SeedStoreScene::ReadMoney() {
    std::string filename = std::string("../Resource/money.txt");
    std::ifstream fin(filename);
    std::string line;

    std::getline(fin, line);
    std::stringstream ss(line);
    ss >> money1 >> money2;
    //Engine::LOG(Engine::DEBUGGING) <<money1;
}
void SeedStoreScene::Initialize() {
    AddNewObject(WindowGroup = new Group());
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;

    //AddNewObject(new Engine::Image("Potion/background.png", halfW, halfH * 1 / 2, 0, 0, 0.5, 0.5));
    AddNewObject(new Engine::Image("Seed/top.png", halfW, halfH * 1 / 2, 0, 0, 0.5, 0.92));
    AddNewObject(new Engine::Label("Seed store", "pirulen.ttf", 70, halfW, halfH * 1 / 4 + 20, 0, 0, 0, 255, 0.5, 0.5));
    AddNewObject(new Engine::Label("Player 1", "pirulen.ttf", 48, halfW * 1 / 2, halfH * 7 / 4, 255, 255, 255, 255, 0.5, 0.5));
    AddNewObject(new Engine::Label("Player 2", "pirulen.ttf", 48, halfW * 3 / 2, halfH * 7 / 4, 255, 255, 255, 255, 0.5, 0.5));

    AddNewControlObject(new Engine::Window(1, "Seed/Seed2.png", "Seed/window1.png", "Wheat", halfW* 1 / 5, halfH-70, 0, 0, 0.5, 0.5));
    AddNewControlObject(new Engine::Window(1, "Seed/Seed1.png", "Seed/window2.png", "vegetable", halfW* 3 / 5, halfH-70, 0, 0, 0.5, 0.5));
    AddNewControlObject(new Engine::Window(1, "Seed/Seed3.png", "Seed/window3.png", "Apple",halfW* 1 / 5, halfH+120, 0, 0, 0.5, 0.5));
    AddNewControlObject(new Engine::Window(1, "Seed/Seed4.png", "Seed/window4.png", "Flower", halfW* 3 / 5, halfH+120, 0, 0, 0.5, 0.5));
    AddNewControlObject(new Engine::Window(1, "Seed/Seed2.png", "Seed/window1.png", "Wheat", halfW* 7 / 5, halfH-70, 0, 0, 0.5, 0.5));
    AddNewControlObject(new Engine::Window(1, "Seed/Seed1.png", "Seed/window2.png", "vegetable", halfW* 9 / 5, halfH-70, 0, 0, 0.5, 0.5));
    AddNewControlObject(new Engine::Window(1, "Seed/Seed3.png", "Seed/window3.png", "Apple",halfW* 7 / 5, halfH+120, 0, 0, 0.5, 0.5));
    AddNewControlObject(new Engine::Window(1, "Seed/Seed4.png", "Seed/window4.png", "Flower", halfW* 9 / 5, halfH+120, 0, 0, 0.5, 0.5));

    Engine::ImageButton* btn;
    btn = new Engine::ImageButton("Seed/dirt.png", "Seed/floor.png", halfW - 100, halfH * 7 / 4 - 25, 200, 50);
    btn->SetOnClickCallback(std::bind(&SeedStoreScene::NextOnClick, this, 2));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Next", "pirulen.ttf", 24, halfW, halfH * 7 / 4, 0, 0, 0, 255, 0.5, 0.5));
    ReadMoney();
    //buy button
    //player1
    btn = new Engine::ImageButton("Seed/dirt.png", "Seed/floor.png", halfW * 1 / 5 - 75, halfH-25, 150, 50);
    btn->SetOnClickCallback(std::bind(&SeedStoreScene::BuyOnClick, this, 1, 0));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Get", "pirulen.ttf", 24, halfW* 1 / 5, halfH, 0, 0, 0, 255, 0.5, 0.5));

    if(money1>=5) {
    btn = new Engine::ImageButton("Seed/dirt.png", "Seed/floor.png", halfW * 3 / 5 - 75, halfH-25, 150, 50);
    btn->SetOnClickCallback(std::bind(&SeedStoreScene::BuyOnClick, this, 1, 5));
    AddNewControlObject(btn);
    }else AddNewObject(new Engine::Image("Potion/gray.png", halfW * 3 / 5 - 75, halfH+-25, 150, 50));
    AddNewObject(new Engine::Label("$5", "pirulen.ttf", 24, halfW* 3 / 5, halfH+0, 0, 0, 0, 255, 0.5, 0.5));

    if(money1 >= 10) {
        btn = new Engine::ImageButton("Seed/dirt.png", "Seed/floor.png", halfW * 1 / 5 - 75, halfH + 200 - 25, 150, 50);
        btn->SetOnClickCallback(std::bind(&SeedStoreScene::BuyOnClick, this, 1, 10));
        AddNewControlObject(btn);
    } else AddNewObject(new Engine::Image("Potion/gray.png", halfW * 1 / 5 - 75, halfH + 200 - 25, 150, 50));
    AddNewObject(new Engine::Label("$10", "pirulen.ttf", 24, halfW * 1 / 5, halfH + 200, 0, 0, 0, 255, 0.5, 0.5));

    if(money1 >= 60) {
        btn = new Engine::ImageButton("Seed/dirt.png", "Seed/floor.png", halfW * 3 / 5 - 75, halfH + 200 - 25, 150, 50);
        btn->SetOnClickCallback(std::bind(&SeedStoreScene::BuyOnClick, this, 1, 60));
        AddNewControlObject(btn);
        } else AddNewObject(new Engine::Image("Potion/gray.png", halfW * 3 / 5 - 75, halfH + 200 - 25, 150, 50));
    AddNewObject(new Engine::Label("$60", "pirulen.ttf", 24, halfW * 3 / 5, halfH + 200, 0, 0, 0, 255, 0.5, 0.5));

    // player2
    btn = new Engine::ImageButton("Seed/dirt.png", "Seed/floor.png", halfW * 7 / 5 - 75, halfH - 25, 150, 50);
    btn->SetOnClickCallback(std::bind(&SeedStoreScene::BuyOnClick, this, 2, 0));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Get", "pirulen.ttf", 24, halfW * 7 / 5, halfH, 0, 0, 0, 255, 0.5, 0.5));

    if(money2 >= 5) {
        btn = new Engine::ImageButton("Seed/dirt.png", "Seed/floor.png", halfW * 9 / 5 - 75, halfH - 25, 150, 50);
        btn->SetOnClickCallback(std::bind(&SeedStoreScene::BuyOnClick, this, 2, 5));
        AddNewControlObject(btn);
        }else AddNewObject(new Engine::Image("Potion/gray.png", halfW * 9 / 5 - 75, halfH - 25, 150, 50));
    AddNewObject(new Engine::Label("$5", "pirulen.ttf", 24, halfW * 9 / 5, halfH, 0, 0, 0, 255, 0.5, 0.5));

    if(money2 >= 10) {
        btn = new Engine::ImageButton("Seed/dirt.png", "Seed/floor.png", halfW * 7 / 5 - 75, halfH + 200 - 25, 150, 50);
        btn->SetOnClickCallback(std::bind(&SeedStoreScene::BuyOnClick, this, 2, 10));
        AddNewControlObject(btn);
    } else AddNewObject(new Engine::Image("Potion/gray.png", halfW * 7 / 5 - 75, halfH + 200 - 25, 150, 50));
    AddNewObject(new Engine::Label("$10", "pirulen.ttf", 24, halfW * 7 / 5, halfH + 200, 0, 0, 0, 255, 0.5, 0.5));

    if(money2 >= 60) {
        btn = new Engine::ImageButton("Seed/dirt.png", "Seed/floor.png", halfW * 9 / 5 - 75, halfH + 200 - 25, 150, 50);
        btn->SetOnClickCallback(std::bind(&SeedStoreScene::BuyOnClick, this, 2, 60));
        AddNewControlObject(btn);
    } else AddNewObject(new Engine::Image("Potion/gray.png", halfW * 9 / 5 - 75, halfH + 200 - 25, 150, 50));
    AddNewObject(new Engine::Label("$60", "pirulen.ttf", 24, halfW * 9 / 5, halfH + 200, 0, 0, 0, 255, 0.5, 0.5));

    std::string output_money_1 = "$"+std::to_string(money1);
    std::string output_money_2 = "$"+std::to_string(money2);
    AddNewObject(new Engine::Label( output_money_1,"pirulen.ttf", 30, halfW * 1 / 2 - 300, halfH * 3 / 5, 150, 0, 0, 255, 0.5, 0.5));
    AddNewObject(new Engine::Label( output_money_2,"pirulen.ttf", 30, halfW * 3 / 2 + 300, halfH * 3 / 5, 150, 0, 0, 255, 0.5, 0.5));
}

void SeedStoreScene::NextOnClick(int stage) {
    Engine::GameEngine::GetInstance().ChangeScene("farm-select");
}

void SeedStoreScene::BuyOnClick(int player, int money) {
    if(player==1) money1-= money;
    else money2 -= money;
    //Engine::LOG(Engine::DEBUGGING) << money1 << money2;
    switch (money) {
        case 0:
            table[player][0]++;
        break;
        case 5:
            table[player][1]++;
        break;
        case 10:
            table[player][2]++;
        break;
        case 60:
            table[player][3]++;
        break;
    }
    Engine::LOG(Engine::DEBUGGING) <<"num1 "<< table[1][0];
    Engine::LOG(Engine::DEBUGGING) <<"num1 "<<table[2][0];
    std::string filename = std::string("../Resource/money.txt");
    std::ofstream outfile(filename, std::ios::trunc);
    outfile << std::to_string(money1) + " " + std::to_string(money2)  << std::endl;
    outfile.flush();
    outfile.close();
    Engine::GameEngine::GetInstance().ChangeScene("seed-store");
}

int SeedStoreScene::GetSeedNumber(int player, int seed) {
    return table[player][seed];
}

int SeedStoreScene::CostMoney(int player, int seed){
    std::cout<<"here"<<std::endl;
    table[player][seed]--;
    std::cout<<table[player][0]<<std::endl;
}