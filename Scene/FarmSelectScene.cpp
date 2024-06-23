#include <allegro5/allegro_audio.h>
#include <functional>
#include <memory>
#include <string>

#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "Engine/Point.hpp"
#include "Engine/Resources.hpp"
#include "FarmScene.hpp"
#include "FarmSelectScene.hpp"
// Yu start
#include <iostream>
using namespace std;
// Yu end

void FarmSelectScene::Initialize() {
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    Engine::ImageButton* btn;
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 200, halfH * 3 / 2 - 50, 400, 100);
    btn->SetOnClickCallback(std::bind(&FarmSelectScene::BackOnClick, this, 1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Back", "pirulen.ttf", 48, halfW, halfH * 3 / 2, 0, 0, 0, 255, 0.5, 0.5));

    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 200, halfH / 2 - 50, 400, 100);
    btn->SetOnClickCallback(std::bind(&FarmSelectScene::PlayerOnClick, this, 1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Player 1", "pirulen.ttf", 48, halfW, halfH / 2, 0, 0, 0, 255, 0.5, 0.5));
    
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 200, halfH / 2 + 100, 400, 100);
    btn->SetOnClickCallback(std::bind(&FarmSelectScene::PlayerOnClick, this, 2));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Player 2", "pirulen.ttf", 48, halfW, halfH / 2 +150, 0, 0, 0, 255, 0.5, 0.5));
    // Not safe if release resource while playing, however we only free while change scene, so it's fine.
	//bgmInstance = AudioHelper::PlaySample("select.ogg", true, AudioHelper::BGMVolume);
}
void FarmSelectScene::Terminate() {
	//AudioHelper::StopSample(bgmInstance);
	//bgmInstance = std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE>();
	IScene::Terminate();
}
void FarmSelectScene::BackOnClick(int player) {
    Engine::GameEngine::GetInstance().ChangeScene("stage-select");
}
void FarmSelectScene::PlayerOnClick(int player) {
    FarmScene* scene = dynamic_cast<FarmScene*>(Engine::GameEngine::GetInstance().GetScene("farm"));
    scene->FieldId = player;
    Engine::GameEngine::GetInstance().ChangeScene("farm");
}