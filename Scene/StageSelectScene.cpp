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
    Engine::ImageButton* btn;
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 200, halfH * 3 / 2 - 50, 400, 100);
    btn->SetOnClickCallback(std::bind(&StageSelectScene::BackOnClick, this, 1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Back", "pirulen.ttf", 48, halfW, halfH * 3 / 2, 0, 0, 0, 255, 0.5, 0.5));

    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 200, halfH / 2 - 50, 400, 100);
    btn->SetOnClickCallback(std::bind(&StageSelectScene::PlayOnClick, this, 1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Stage 1", "pirulen.ttf", 48, halfW, halfH / 2, 0, 0, 0, 255, 0.5, 0.5));
    
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 200, halfH / 2 + 100, 400, 100);
    btn->SetOnClickCallback(std::bind(&StageSelectScene::PlayOnClick, this, 2));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Stage 2", "pirulen.ttf", 48, halfW, halfH / 2 +150, 0, 0, 0, 255, 0.5, 0.5));

    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 200, halfH / 2 + 250, 400, 100);
    btn->SetOnClickCallback(std::bind(&StageSelectScene::ScoreboardOnClick, this));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Scoreboard", "pirulen.ttf", 36, halfW, halfH / 2 + 300, 0, 0, 0, 255, 0.5, 0.5));
    //
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 200, halfH * 3 / 2 + 70, 400, 100);
    btn->SetOnClickCallback(std::bind(&StageSelectScene::FarmOnClick, this));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Farm", "pirulen.ttf", 36, halfW, halfH * 3 / 2 + 120, 100, 0, 0, 255, 0.5, 0.5));

    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW/2 - 200, halfH * 3 / 2 - 50, 400, 100);
    btn->SetOnClickCallback(std::bind(&StageSelectScene::GameOnClick, this));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Game", "pirulen.ttf", 36, halfW / 2, halfH * 3 / 2 , 100, 0, 0, 255, 0.5, 0.5));


    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 200 , halfH * 3 / 2 - 50, 400, 100);
    btn->SetOnClickCallback(std::bind(&StageSelectScene::StorePotionOnClick, this));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("store", "pirulen.ttf", 36, halfW, halfH * 3 / 2, 100, 0, 0, 255, 0.5, 0.5));

    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW * 3 / 2 - 200, halfH * 3 / 2 - 50, 400, 100);
    btn->SetOnClickCallback(std::bind(&StageSelectScene::StoreSeedOnClick, this));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("seed", "pirulen.ttf", 36, halfW * 3 / 2, halfH * 3 / 2, 100, 0, 0, 255, 0.5, 0.5));
    // Not safe if release resource while playing, however we only free while change scene, so it's fine.
	bgmInstance = AudioHelper::PlaySample("select.ogg", true, AudioHelper::BGMVolume);
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
