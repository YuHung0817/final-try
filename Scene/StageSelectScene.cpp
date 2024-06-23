#include <allegro5/allegro_audio.h>
#include <functional>
#include <memory>
#include <string>

#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "PlayScene.hpp"
#include "Engine/Point.hpp"
#include "Engine/Resources.hpp"
#include "UI/Component/Slider.hpp"
#include "StageSelectScene.hpp"
#include "OurGameScene.hpp"
// Yu start
#include <iostream>
using namespace std;
// Yu end

void StageSelectScene::Initialize() {
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    AddNewObject(new Engine::Image("reset/select.png", 0, 0, 1700, 1100));
    Engine::ImageButton* btn;
    btn = new Engine::ImageButton("stage-select/back.png", "stage-select/on.png", halfW - 200, halfH * 3 / 2 - 120, 400, 100);
    btn->SetOnClickCallback(std::bind(&StageSelectScene::BackOnClick, this, 1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Back", "pirulen.ttf", 36, halfW, halfH * 3 / 2-70, 0, 0, 0, 255, 0.5, 0.5));


    btn = new Engine::ImageButton("stage-select/back.png", "stage-select/on.png", halfW - 200, halfH * 1 / 2+30, 400, 100);
    btn->SetOnClickCallback(std::bind(&StageSelectScene::FarmOnClick, this));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Farm", "pirulen.ttf", 36, halfW, halfH * 1 / 2 + 80, 0, 0, 0, 255, 0.5, 0.5));

    btn = new Engine::ImageButton("stage-select/back.png", "stage-select/on.png", halfW - 200, halfH / 2 - 100, 400, 100);
    btn->SetOnClickCallback(std::bind(&StageSelectScene::GameOnClick, this));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Game", "pirulen.ttf", 36, halfW, halfH / 2-50, 0, 0, 0, 255, 0.5, 0.5));


    btn = new Engine::ImageButton("stage-select/back.png", "stage-select/on.png", halfW * 1 / 2 - 200+150, halfH -50, 400, 100);
    btn->SetOnClickCallback(std::bind(&StageSelectScene::StorePotionOnClick, this));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("potion store", "pirulen.ttf", 36, halfW* 1 / 2+150, halfH, 0, 0, 0, 255, 0.5, 0.5));

    btn = new Engine::ImageButton("stage-select/back.png", "stage-select/on.png", halfW * 3 / 2 - 200-150 , halfH -50, 400, 100);
    btn->SetOnClickCallback(std::bind(&StageSelectScene::StoreSeedOnClick, this));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("seed store", "pirulen.ttf", 36, halfW* 3 / 2-150, halfH, 0, 0, 0, 255, 0.5, 0.55));
    // Not safe if release resource while playing, however we only free while change scene, so it's fine.
	bgmInstance = AudioHelper::PlaySample("moo.wav", true, AudioHelper::BGMVolume);
}

void StageSelectScene::GameOnClick() {
    OurGameScene* scene = dynamic_cast<OurGameScene*>(Engine::GameEngine::GetInstance().GetScene("ourgame-scene"));
    //std::cout<<"scene==?"<<scene<<std::endl;
    //scene->MapId=1;
   // std::cout<<"here2\n";
    Engine::GameEngine::GetInstance().ChangeScene("ourgame-scene");
}
void StageSelectScene::StorePotionOnClick() {
    Engine::GameEngine::GetInstance().ChangeScene("potion-store");
}
void StageSelectScene::StoreSeedOnClick() {
    Engine::GameEngine::GetInstance().ChangeScene("seed-store");
}

void StageSelectScene::Terminate() {
	AudioHelper::StopSample(bgmInstance);
	bgmInstance = std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE>();
	IScene::Terminate();
    //cout << "StageSelectTerminate" << std::endl;
}
void StageSelectScene::BackOnClick(int stage) {
    Engine::GameEngine::GetInstance().ChangeScene("start");
}
void StageSelectScene::PlayOnClick(int stage) {
    PlayScene* scene = dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetScene("play"));
    scene->MapId = stage;
    //cout << "Play!!!";
    Engine::GameEngine::GetInstance().ChangeScene("play");
}
void StageSelectScene::ScoreboardOnClick() {
    Engine::GameEngine::GetInstance().ChangeScene("scoreboard");
}
void StageSelectScene::FarmOnClick() {
    Engine::GameEngine::GetInstance().ChangeScene("farm-select");
}
