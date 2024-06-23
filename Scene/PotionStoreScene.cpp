#include "PotionStoreScene.h"
#include <functional>
#include <string>
#include <fstream>
#include <sstream>
#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "UI/Component/Image.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "LoseScene.hpp"
#include "PlayScene.hpp"
#include "Engine/Point.hpp"
#include "Engine/LOG.hpp"
#include "UI/Component/Window.h"

void PotionStoreScene::ReadMoney() {
    std::string filename = std::string("../Resource/money.txt");
    std::ifstream fin(filename);
    std::string line;

    std::getline(fin, line);
    std::stringstream ss(line);
    ss >> money1 >> money2;
    //Engine::LOG(Engine::DEBUGGING) <<money1;
}

void PotionStoreScene::Initialize() {
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    AddNewObject(new Engine::Image("stage-select/background.png", 0, 0, 1700, 1100));
    //AddNewObject(new Engine::Image("Potion/background.png", halfW, halfH * 1 / 2, 0, 0, 0.5, 0.5));
    AddNewObject(new Engine::Image("Potion/top.png", halfW, halfH * 1 / 2, 0, 0, 0.5, 0.92));
    AddNewObject(new Engine::Label("Potion store", "pirulen.ttf", 70, halfW, halfH * 1 / 4 + 20, 0, 0, 0, 255, 0.5, 0.5));
    AddNewObject(new Engine::Label("Player 1", "pirulen.ttf", 48, halfW * 1 / 2, halfH * 7 / 4, 0, 0, 0, 255, 0.5, 0.5));
    AddNewObject(new Engine::Label("Player 2", "pirulen.ttf", 48, halfW * 3 / 2, halfH * 7 / 4, 0, 0, 0, 255, 0.5, 0.5));

    AddNewControlObject(new Engine::Window(2, "Potion/potion1.png", "Potion/window1.png", "Resurrection", halfW* 1 / 7+50, halfH+50, 0, 0, 0.5, 0.5));
    AddNewControlObject(new Engine::Window(2, "Potion/potion2.png", "Potion/window2.png", "SpeedUp", halfW* 3 / 7, halfH+50, 0, 0, 0.5, 0.5));
    AddNewControlObject(new Engine::Window(2, "Potion/potion3.png", "Potion/window3.png", "SlowDown", halfW* 5 / 7-50, halfH+50, 0, 0, 0.5, 0.5));
    AddNewControlObject(new Engine::Window(2, "Potion/potion1.png", "Potion/window1.png", "Resurrection", halfW* 9 / 7+50, halfH+50, 0, 0, 0.5, 0.5));
    AddNewControlObject(new Engine::Window(2, "Potion/potion2.png", "Potion/window2.png", "SpeedUp", halfW* 11 / 7, halfH+50, 0, 0, 0.5, 0.5));
    AddNewControlObject(new Engine::Window(2, "Potion/potion3.png", "Potion/window3.png", "SlowDown", halfW* 13 / 7-50, halfH+50, 0, 0, 0.5, 0.5));

    Engine::ImageButton* btn;
    btn = new Engine::ImageButton("stage-select/back.png", "stage-select/on.png", halfW - 100, halfH * 7 / 4 - 25, 200, 50);
    btn->SetOnClickCallback(std::bind(&PotionStoreScene::NextOnClick, this, 2));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Next", "pirulen.ttf", 24, halfW, halfH * 7 / 4, 0, 0, 0, 255, 0.5, 0.5));

    btn = new Engine::ImageButton("stage-select/back.png", "stage-select/on.png", halfW - 100, halfH * 7 / 4 - 25-70, 200, 50);
    btn->SetOnClickCallback(std::bind(&PotionStoreScene::BackOnClick, this, 2));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Back", "pirulen.ttf", 24, halfW, halfH * 7 / 4-70, 0, 0, 0, 255, 0.5, 0.5));
    ReadMoney();
    //buy button
    //player1
    if(money1>=200) {
        btn = new Engine::ImageButton("stage-select/back.png", "stage-select/on.png", halfW * 1 / 7 - 75+50, halfH+200-25, 150, 50);
        btn->SetOnClickCallback(std::bind(&PotionStoreScene::BuyOnClick, this, 1, 200, 0));
        AddNewControlObject(btn);
    }else AddNewObject(new Engine::Image("Potion/gray.png", halfW * 1 / 7 - 75+50, halfH+200-25, 150, 50));
    AddNewObject(new Engine::Label("$200", "pirulen.ttf", 24, halfW* 1 / 7+50, halfH+200, 0, 0, 0, 255, 0.5, 0.5));

    if(money1>=150) {
        btn = new Engine::ImageButton("stage-select/back.png", "stage-select/on.png", halfW * 3 / 7 - 75, halfH+200-25, 150, 50);
        btn->SetOnClickCallback(std::bind(&PotionStoreScene::BuyOnClick, this, 1, 150, 1));
        AddNewControlObject(btn);
    }else AddNewObject(new Engine::Image("Potion/gray.png", halfW * 3 / 7 - 75, halfH+200-25, 150, 50));
    AddNewObject(new Engine::Label("$150", "pirulen.ttf", 24, halfW* 3 / 7, halfH+200, 0, 0, 0, 255, 0.5, 0.5));

    if(money1>=150) {
        btn = new Engine::ImageButton("stage-select/back.png", "stage-select/on.png", halfW * 5 / 7 - 75-50, halfH+200-25, 150, 50);
        btn->SetOnClickCallback(std::bind(&PotionStoreScene::BuyOnClick, this, 1, 150, 2));
        AddNewControlObject(btn);
    }else AddNewObject(new Engine::Image("Potion/gray.png", halfW * 5 / 7 - 75-50, halfH+200-25, 150, 50));
    AddNewObject(new Engine::Label("$150", "pirulen.ttf", 24, halfW* 5 / 7-50, halfH+200, 0, 0, 0, 255, 0.5, 0.5));

    //player2
    if(money2>=200) {
        btn = new Engine::ImageButton("stage-select/back.png", "stage-select/on.png", halfW * 9 / 7 - 75+50, halfH+200-25, 150, 50);
        btn->SetOnClickCallback(std::bind(&PotionStoreScene::BuyOnClick, this, 2, 200, 0));
        AddNewControlObject(btn);
    }else AddNewObject(new Engine::Image("Potion/gray.png", halfW * 9 / 7 - 75+50, halfH+200-25, 150, 50));
    AddNewObject(new Engine::Label("$200", "pirulen.ttf", 24, halfW* 9 / 7+50, halfH+200, 0, 0, 0, 255, 0.5, 0.5));

    if(money2>=150) {
        btn = new Engine::ImageButton("stage-select/back.png", "stage-select/on.png", halfW * 11 / 7 - 75, halfH+200-25, 150, 50);
        btn->SetOnClickCallback(std::bind(&PotionStoreScene::BuyOnClick, this, 2, 150, 1));
        AddNewControlObject(btn);
    }else AddNewObject(new Engine::Image("Potion/gray.png", halfW * 11 / 7 - 75, halfH+200-25, 150, 50));
    AddNewObject(new Engine::Label("$150", "pirulen.ttf", 24, halfW* 11 / 7, halfH+200, 0, 0, 0, 255, 0.5, 0.5));

    if(money2>=150) {
        btn = new Engine::ImageButton("stage-select/back.png", "stage-select/on.png", halfW * 13 / 7 - 75-50, halfH+200-25, 150, 50);
        btn->SetOnClickCallback(std::bind(&PotionStoreScene::BuyOnClick, this, 2, 150, 2));
        AddNewControlObject(btn);
    }else AddNewObject(new Engine::Image("Potion/gray.png", halfW * 13 / 7 - 75-50, halfH+200-25, 150, 50));
    AddNewObject(new Engine::Label("$150", "pirulen.ttf", 24, halfW* 13 / 7-50, halfH+200, 0, 0, 0, 255, 0.5, 0.5));

    std::string output_money_1 = "$"+std::to_string(money1);
    std::string output_money_2 = "$"+std::to_string(money2);
    AddNewObject(new Engine::Label( output_money_1,"pirulen.ttf", 30, halfW * 1 / 2 - 300, halfH * 3 / 5, 150, 0, 0, 255, 0.5, 0.5));
    AddNewObject(new Engine::Label( output_money_2,"pirulen.ttf", 30, halfW * 3 / 2 + 300, halfH * 3 / 5, 150, 0, 0, 255, 0.5, 0.5));
}

void PotionStoreScene::NextOnClick(int stage) {
    Engine::GameEngine::GetInstance().ChangeScene("ourgame-scene");
}
void PotionStoreScene::BackOnClick(int stage) {
    Engine::GameEngine::GetInstance().ChangeScene("stage-select");
}

void PotionStoreScene::BuyOnClick(int player, int money, int potion) {
    if(player==1) money1-= money;
    else money2 -= money;
    //Engine::LOG(Engine::DEBUGGING) << money1 << money2;
    table[player][potion]++;
    //Engine::LOG(Engine::DEBUGGING) <<"num1 "<< table[1][0];
    //Engine::LOG(Engine::DEBUGGING) <<"num1 "<<table[2][0];
    std::string filename = std::string("../Resource/money.txt");
    std::ofstream outfile(filename, std::ios::trunc);
    outfile << std::to_string(money1) + " " + std::to_string(money2)  << std::endl;
    outfile.flush();
    outfile.close();
    Engine::GameEngine::GetInstance().ChangeScene("potion-store");
    bgmId = AudioHelper::PlayAudio("money.wav");
}

int PotionStoreScene::GetPotionNumber(int player, int potion) const{
    return table[player][potion];
}

