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
// Yu start
#include "ScoreboardScene.hpp"
#include <string>
#include <fstream>
#include <algorithm>
#include <tuple>
#include <iostream>
using namespace std;
/*bool cmp(std::pair<int, std::string> a, std::pair<int, std::string> b) {
    return a.first > b.first;
}*/
// Yu end

int size;
int cur_page = 1;
int totalPages = 0;

void ScoreboardScene::Initialize() {
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;

    // Yu start
    ReadScoreRecord();
    AddNewObject(new Engine::Label("ScoreBoard", "pirulen.ttf", 60, halfW, halfH / 2 - 150, 0, 200, 0, 225/*顯色度*/, 0.5, 0.5));
    
    int size = ScoreData.size();
    if (size % 10 == 0)
        totalPages = size / 10;
    else
        totalPages = size / 10 + 1;

    int show_page = 0;
    int row = 0;
    for (auto& it : ScoreData){
    //for(std::list<std::tuple<std::string, int, std::string>>::iterator it = ScoreData.begin(); it != ScoreData.end(); it++) {
        if ( (cur_page - 1) * 10 <= show_page && show_page < cur_page * 10) {
            AddNewObject(new Engine::Label(std::get<0>(it), "pirulen.ttf", 38, halfW - 300, halfH / 3 + 48 * row, 0, 150, 0, 150, 0.5, 0.5));
            //std::string s_score = to_string(std::get<1>(it));
            AddNewObject(new Engine::Label(to_string(std::get<1>(it)), "pirulen.ttf", 38, halfW, halfH / 3 + 48 * row, 0, 150, 0, 150, 0.5, 0.5));
            AddNewObject(new Engine::Label(std::get<2>(it), "pirulen.ttf", 38, halfW + 360, halfH / 3 + 48 * row, 0, 150, 0, 150, 0.5, 0.5));
            row++;
        }
        show_page++;
    }
    // Yu end

    Engine::ImageButton* btn;
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 200, halfH * 3 / 2 + 50, 400, 100);
    btn->SetOnClickCallback(std::bind(&ScoreboardScene::BackOnClick, this, 1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Back", "pirulen.ttf", 48, halfW, halfH * 3 / 2 + 100, 0, 0, 0, 255, 0.5, 0.5));

    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 650, halfH * 3/2 + 50, 400, 100);
    btn->SetOnClickCallback(std::bind(&ScoreboardScene::PrevOnClick, this, 1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Prev Page", "pirulen.ttf", 48, halfW - 450, halfH * 3 / 2 + 100, 0, 0, 0, 255, 0.5, 0.5));

    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW + 250, halfH * 3/2 + 50, 400, 100);
    btn->SetOnClickCallback(std::bind(&ScoreboardScene::NextOnClick, this, 2));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Next Page", "pirulen.ttf", 48, halfW + 450, halfH * 3 / 2 + 100, 0, 0, 0, 255, 0.5, 0.5));
}
void ScoreboardScene::Terminate() {
	//bgmInstance = std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE>();
	IScene::Terminate();
    //std::cout << "ScoreboardTerminate" << std::endl;
}
//Yu start
void ScoreboardScene::ReadScoreRecord() {
    ScoreData.clear();
    string filename = string("Resource/scoreboard") + ".txt";
	// Read scoreboard file.
	string name, recordTime;
    int score;
	ifstream fin(filename);
	while (fin >> name && fin >> score && fin >> recordTime) {
        //ScoreData.push_back(make_tuple(score, name));
		ScoreData.emplace_back(make_tuple(name, score, recordTime));
        //std::cout << "Read Successfully! " << i << std::endl;
	}
	fin.close();

    sort(ScoreData.begin(), ScoreData.end(), compareScore());
}

void ScoreboardScene::PrevOnClick(int stage) {
    if (cur_page <= 1)
        return;
    cur_page--;
    Engine::GameEngine::GetInstance().ChangeScene("scoreboard");
}

void ScoreboardScene::NextOnClick(int stage) {
    if (cur_page >= totalPages)
        return;
    cur_page++;
    Engine::GameEngine::GetInstance().ChangeScene("scoreboard");
}
// Yu end
void ScoreboardScene::BackOnClick(int stage) {
    Engine::GameEngine::GetInstance().ChangeScene("stage-select");
}