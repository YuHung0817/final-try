#include <functional>
#include <string>
#include <iostream>

#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "UI/Component/Image.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "LoseScene.hpp"
#include "PlayScene.hpp"
#include "Scene/OurGameScene.hpp"
#include "Engine/Point.hpp"

OurGameScene* getGameScene() {
    return dynamic_cast<OurGameScene*>(Engine::GameEngine::GetInstance().GetActiveScene());
}
void LoseScene::Initialize() {
	// TODO: [HACKATHON-1-SCENE] (1/4): You can imitate the 2 files: 'LoseScene.hpp', 'LoseScene.cpp' to implement your start scene.
	int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
	int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
	int halfW = w / 2;
	int halfH = h / 2;

   //std::string player=getGameScene()->getwinner();
   std::string tmp="";
   std::string img="";
    if(getGameScene()->winner==1) {
        tmp="player1 win";
        img="reset/Player1Win.png";
    }
    else if(getGameScene()->winner==2) {
        tmp = "player2 win";
        img="reset/Player2Win.png";
    }
    else {
        tmp = "both die";
        img="reset/BothDie.png";
    }
    //AddNewControlObject(UIGroup = new Group());
    //UIGroup->AddNewObject(new Engine::Image("our_game/background1.png", 0, 0, 1600, 800));
    AddNewObject(new Engine::Image(img, 0, 0, 1600,900));
    //std::cout<<"player: "<<player<<std::endl;
    //std::string tmp="";
    //if(player=="both die") tmp="both die";
    //else  tmp=player+" Win";
	AddNewObject(new Engine::Label(tmp, "pirulen.ttf", 48, halfW, halfH / 4 + 10, 0, 0, 0, 255, 0.5, 0.5));
	Engine::ImageButton* btn;
	btn = new Engine::ImageButton("stage-select/back.png", "stage-select/on.png", halfW - 200, halfH * 7 / 4 - 50, 400, 100);
	btn->SetOnClickCallback(std::bind(&LoseScene::BackOnClick, this, 2));
	AddNewControlObject(btn);
	AddNewObject(new Engine::Label("Back", "pirulen.ttf", 48, halfW, halfH * 7 / 4, 0, 0, 0, 255, 0.5, 0.5));
    bgmInstance = AudioHelper::PlaySample("lose.wav", false, AudioHelper::BGMVolume, PlayScene::DangerTime);
}
void LoseScene::Terminate() {
	AudioHelper::StopSample(bgmInstance);
	bgmInstance = std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE>();
	IScene::Terminate();
}
void LoseScene::BackOnClick(int stage) {
	// Change to select scene.
	Engine::GameEngine::GetInstance().ChangeScene("stage-select");
}
