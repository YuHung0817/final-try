#include <functional>
#include <string>

#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "UI/Component/Image.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "PlayScene.hpp"
#include "Engine/Point.hpp"
#include "WinScene.hpp"
// Yu start
#include "allegro5/allegro.h"
#include "allegro5/allegro_primitives.h"
#include <fstream>
#include <iostream>
#include <chrono>
#include <ctime>
using namespace std;
// Yu end

void WinScene::Initialize() {
	ticks = 0;
	w = Engine::GameEngine::GetInstance().GetScreenSize().x;
	h = Engine::GameEngine::GetInstance().GetScreenSize().y;
	halfW = w / 2;
	halfH = h / 2;
	AddNewObject(new Engine::Image("win/benjamin-sad.png", halfW, halfH, 0, 0, 0.5, 0.5));
	AddNewObject(new Engine::Label("You Win!", "pirulen.ttf", 48, halfW, halfH / 4 -10, 255, 255, 255, 255, 0.5, 0.5));
	Engine::ImageButton* btn;
	btn = new Engine::ImageButton("win/dirt.png", "win/floor.png", halfW - 200, halfH * 7 / 4 - 50, 400, 100);
	btn->SetOnClickCallback(std::bind(&WinScene::BackOnClick, this, 2));
	AddNewControlObject(btn);
	AddNewObject(new Engine::Label("Back", "pirulen.ttf", 48, halfW, halfH * 7 / 4, 0, 0, 0, 255, 0.5, 0.5));
	bgmId = AudioHelper::PlayAudio("lose.wav");
}
void WinScene::Terminate() {
	IScene::Terminate();
	AudioHelper::StopBGM(bgmId);
}
void WinScene::Update(float deltaTime) {
	ticks += deltaTime;
	if (ticks > 4 && ticks < 100 &&
		dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetScene("play"))->MapId == 2) {
		ticks = 100;
		bgmId = AudioHelper::PlayBGM("happy.ogg");
	}
}
void WinScene::BackOnClick(int stage) {
	// Change to select scene.
	Engine::GameEngine::GetInstance().ChangeScene("stage-select");
}
// Yu start
void WinScene::Draw() const {
	IScene::Draw();
	al_draw_rectangle(halfW - 200, halfH / 4 + 20, halfW + 200, halfH / 4 + 70, al_map_rgb(255, 255, 255), 2);
	if (winnerName.length() > 0) {
		Engine::Label label(winnerName, "pirulen.ttf", 32, halfW - 195,halfH / 4 + 25, 255, 255, 255, 255, 0, 0);
		label.Draw();
	}
}
void WinScene::OnKeyDown(int keyCode) {
	if (keyCode == ALLEGRO_KEY_BACKSPACE) {
		if (winnerName.length() > 0) {
			winnerName.pop_back();
		}
	} else if (keyCode == ALLEGRO_KEY_ENTER) {
		char buf[30];
		const time_t currentTime = chrono::system_clock::to_time_t(chrono::system_clock::now());
		struct tm tstruct = *localtime(&currentTime);
		string filename = string("Resource/scoreboard.txt");

		// write
		ofstream fout(filename, std::ios::app);
		strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
		fout << winnerName << " " << to_string(dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetScene("play"))->GetMoney()) << " " << buf << endl;
		fout.close();
		winnerName.clear();
		Engine::GameEngine::GetInstance().ChangeScene("stage-select");
		
	} else if (ALLEGRO_KEY_A <= keyCode && keyCode <= ALLEGRO_KEY_Z) {
		winnerName.push_back(*al_keycode_to_name(keyCode));
	} else {
		//IScene::OnKeyDown(keyCode);
		//return;
	}
}
// Yu end
