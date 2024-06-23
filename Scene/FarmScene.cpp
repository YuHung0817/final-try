#include <allegro5/allegro.h>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <functional>
#include <vector>
#include <queue>
#include <string>
#include <memory>

#include "Engine/AudioHelper.hpp"
#include "UI/Animation/DirtyEffect.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Group.hpp"
#include "UI/Component/Label.hpp"
#include "Engine/Resources.hpp"

#include "Scene/FarmScene.hpp"
#include "Plant/Plant.hpp"
#include "Plant/PlantButton.hpp"
#include "Plant/WheatPlant.hpp"
#include "Plant/VegetablePlant.hpp"
#include "Plant/ApplePlant.hpp"
#include "Plant/FlowerPlant.hpp"
#include "Plant/SicklePlant.hpp"
#include "Scene/SeedStoreScene.h"

#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

int UpTime = 0;
const int FarmScene::FieldWidth = 3, FarmScene::FieldHeight = 3;
const int FarmScene::MapWidth = 20, FarmScene::MapHeight = 13;
const int FarmScene::BlockSize = 64;
//const Engine::Point FarmScene::SpawnGridPoint = Engine::Point(-1, 0);
const Engine::Point FarmScene::EndGridPoint = Engine::Point(FieldWidth, FieldHeight - 1);
Engine::Point FarmScene::GetClientSize() {
	return Engine::Point(FieldWidth * BlockSize, FieldHeight * BlockSize);
}

SeedStoreScene* getSeedScene() {
    return dynamic_cast<SeedStoreScene*>(Engine::GameEngine::GetInstance().GetScene("seed-store"));
}

void FarmScene::Initialize() {
	int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;

	//cout << "!!!" << endl;
    fieldState.clear();
    ticks = 0; // time
    AddNewObject(TileFieldGroup = new Group());
	AddNewObject(GroundEffectGroup = new Group());
	AddNewObject(PlantGroup = new Group());
	AddNewObject(EffectGroup = new Group());
	AddNewObject(UpGroup = new Group());
	AddNewControlObject(UIGroup = new Group());
	ReadTime();
	ReadField();
    ConstructUI(); 
	imgTarget = new Engine::Image("play/target.png", 0, 0); //顯示目標圖像
	imgTarget->Visible = false;
	preview = nullptr; //預覽將要放置的作物。它被用來暫時顯示在遊戲場景中，以便玩家可以在放置之前看到其位置和外觀。
	UIGroup->AddNewObject(imgTarget);

	Engine::ImageButton* btn;
    btn = new Engine::ImageButton("stage-select/back.png", "stage-select/on.png", 1310, halfH + 270 , 260, 90);
    btn->SetOnClickCallback(std::bind(&FarmScene::BackOnClick, this));
    AddNewControlObject(btn);

    AddNewObject(new Engine::Label("Back", "pirulen.ttf", 46, 1445, halfH + 315, 0, 0, 0, 255, 0.5, 0.5));
	bgmId = AudioHelper::PlayAudio("farm.wav");
}
void FarmScene::Terminate() {
	AudioHelper::StopBGM(bgmId);
	//AudioHelper::StopSample(deathBGMInstance);
	//deathBGMInstance = std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE>();
	IScene::Terminate();
}
void FarmScene::Update(float deltaTime) {
	IScene::Update(deltaTime); // 呼叫全部的scene update
	//PlantButton->Update(deltaTime);
	
	for (auto& it : PlantGroup->GetObjects()) {
		Plant* plant = dynamic_cast<Plant*>(it);
		plant->Update(deltaTime);
	}
	// If we use deltaTime directly, then we might have Bullet-through-paper problem.
	if (preview) {
		preview->Position = Engine::GameEngine::GetInstance().GetMousePosition();
		// To keep responding when paused.
		preview->Update(deltaTime);
	}

	for (auto& it : UpGroup->GetObjects()) {
		if (UpTime == 15) {
			UIGroup->RemoveObject(it->GetObjectIterator());

			UpTime = 0;
		} else {
			UpTime++;
		}
	}
}

void FarmScene::BackOnClick() {
	WritetoField();
	WritetoTime();
	//cout << "timer!!!" << endl;
	Engine::GameEngine::GetInstance().ChangeScene("stage-select");
}

void FarmScene::WritetoField() {
	string filename = string("./Resource/farmfield") + std::to_string(FieldId) + ".txt";
	ofstream outfile(filename, ios::trunc);

	char c;
	for (int i = 0; i < FieldWidth; i++) {
		for (int j = 0; j < FieldHeight; j++) {
			switch (fieldState[i][j]) {
				case TILE_DIRT: c = 'd'; break;
				case TILE_WHEAT: c = 'w'; break;
				case TILE_VEGETABLE: c = 'v'; break;
				case TILE_APPLE: c = 'a'; break;
				case TILE_FLOWER: c = 'f'; break;
			}
			outfile << c;
		}
		outfile << '\n';
	}
	outfile.close();
}

void FarmScene::WritetoTime() {
	string filename = string("./Resource/farmtime") + std::to_string(FieldId) + ".txt";
	ofstream outfile(filename, ios::trunc);

	for (int a = 0; a < 9; a++) {
		timer.push_back(0.0);
	}

	/*for(int i = 0; i < 9; i++) 
		cout << timer[i] << endl;*/

	for (auto& it : PlantGroup->GetObjects()) {
		Plant* plant = dynamic_cast<Plant*>(it);
		int i = floor(plant->Position.x / BlockSize) - 9;
		int j = floor(plant->Position.y / BlockSize) - 5;
		timer[i * 3 + j] = plant->harvestTimer;
		//cout << timer[i * 3 + j] << endl;
		//cout << plant->harvestTimer << endl;
	}
	
	for (int i = 0; i < 9; i++) {
		outfile << timer[i] << " ";
	}
	// 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0
	timer.clear();
	outfile.close();
}

void FarmScene::Draw() const {
	//cout << "Draw" << endl;
	IScene::Draw();
	/*for (int i = 0; i < FieldHeight; i++) {
		for (int j = 0; j < FieldWidth; j++) {
			// Not elegant nor efficient, but it's quite enough for debugging.
			Engine::Label label(std::to_string(mapDistance[i][j]), "pirulen.ttf", 32, (j + 0.5) * BlockSize, (i + 0.5) * BlockSize);
			label.Anchor = Engine::Point(0.5, 0.5);
			label.Draw();
		}
	}*/
	//cout << "Draw Success" << endl;
}

void FarmScene::ReadTime() {
    string filename = string("./Resource/farmtime") + std::to_string(FieldId) + ".txt";
	ifstream fin(filename);

	if (!fin.is_open()) {
		cout << "Failed to open" << endl;
	}
	// Read time file.
	timeData.clear();

	float ftime;
	string time;

	while(fin >> time) {
		//cout << "time: " << time << endl;
		ftime = std::stof(time);
		timeData.push_back(ftime);
	}
	fin.close();

	for (int i = 0; i < 9; i++) {
		//cout << "timeData: " << timeData[i] << endl;
	}
}
/* timeDate
[0][3][6]
[1][4][7]
[2][5][8]
*/
float FarmScene::getTimeData(int i, int j) {
	return timeData[j * 3 + i];
}

void FarmScene::ReadField() {
	string filename = string("./Resource/farmfield") + std::to_string(FieldId) + ".txt"; // ../ 上一層目錄、./ 這一層目錄
	// Read field file.
	char c;
	std::vector<char> fieldData;
	std::ifstream fin(filename);

    while (fin >> c) {
		switch (c) {
		case 'd': {
			fieldData.push_back('0');
			break;
		} 
		case 'w': fieldData.push_back('1'); break;
		case 'v': fieldData.push_back('2'); break;
		case 'a': fieldData.push_back('3'); break;
		case 'f': fieldData.push_back('4'); break;
		case '\n':
		case '\r':
			//if (static_cast<int>(fieldData.size()) / Width != 0)
				//throw std::ios_base::failure("Map data is corrupted.");
			break;
		default: throw std::ios_base::failure("Map data is corrupted.");
		}
    } 
	fin.close();

	/*cout << "size: " << fieldData.size() << endl;
	for(int a = 0; a < fieldData.size(); a++) {
		cout << fieldData[a] << " ";
	}
	cout << endl;*/

	// Validate field data.
	if (static_cast<int>(fieldData.size()) != FieldWidth * FieldHeight)
		throw std::ios_base::failure("Map data is corrupted!");

	// Store field in 2d array.
	fieldState = vector<vector<TileType>>(FieldHeight, vector<TileType>(FieldWidth));
	// y == i, x == j => fieldState[y][x] x變是j變

	//cout << "MapHeight: " << (Engine::GameEngine::GetInstance().GetScreenSize().x) << endl;
	//cout << "MapWidth: " << (Engine::GameEngine::GetInstance().GetScreenSize().y) << endl;

	for (int i = 0; i < MapHeight; i++) {
		for (int j = 0; j < MapWidth; j++) {
			const char type = fieldData[i * FieldWidth + j];
			if (4 < i && i < 8 &&  8 < j && j < 12) {
				//fieldState[i][j] = TILE_DIRT;
            	TileFieldGroup->AddNewObject(new Engine::Image("farm/soil.png", j * BlockSize, i * BlockSize, BlockSize, BlockSize));
				//cout << "B: " << j * BlockSize << " " << i * BlockSize << endl;
			} else {
				//fieldState[i][j] = TILE_DIRT;
            	TileFieldGroup->AddNewObject(new Engine::Image("farm/grass.png", j * BlockSize, i * BlockSize, BlockSize, BlockSize));
				//cout << "B: " << j * BlockSize << " " << i * BlockSize << endl;
			}
        }
	}



	// y == i, x == j => fieldstate[y][x]
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			const char type = fieldData[i * FieldWidth + j];
			//cout << "type: " << type << endl;
			if (type == '0') {
                fieldState[i][j] = TILE_DIRT;
            } else if (type == '1') {
                fieldState[i][j] = TILE_WHEAT;
				PlantGroup->AddNewObject(new Plant("play/tower-base.png", "farm/Seed1.png", (j + 9) * BlockSize, (i + 5) * BlockSize, 10, 0.0, 10.0, getTimeData(i, j)));
				//cout << "newTimer: " << getTimeData(i, j) << endl;
			} else if (type == '2') {
                fieldState[i][j] = TILE_VEGETABLE;
				PlantGroup->AddNewObject(new Plant("play/tower-base.png", "farm/Seed2.png", (j + 9) * BlockSize, (i + 5) * BlockSize, 20, 0.0, 20.0, getTimeData(i, j)));
				//cout << "newTimer: " << getTimeData(i, j) << endl;
			} else if (type == '3') {
                fieldState[i][j] = TILE_APPLE;
				PlantGroup->AddNewObject(new Plant("play/tower-base.png", "farm/Seed3.png", (j + 9) * BlockSize, (i + 5) * BlockSize, 30, 0.0, 40.0, getTimeData(i, j)));
				//cout << "newTimer: " << getTimeData(i, j) << endl;
			} else if (type == '4') {
                fieldState[i][j] = TILE_FLOWER;
				PlantGroup->AddNewObject(new Plant("play/tower-base.png", "farm/Seed4.png", (j + 9) * BlockSize, (i + 5) * BlockSize, 100, 0.0, 60.0, getTimeData(i, j)));
				//cout << "newTimer: " << getTimeData(i, j) << endl;
			} else {
                throw std::ios_base::failure("Map data is corrupted.");
            }
		}
	}
	/*for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << fieldState[i][j];
		}
		cout << endl;
	}*/
	/*fieldState[i][j]
	[0][1][2]
	[3][4][5]
	[6][7][8]
	*/
	for (auto& it : PlantGroup->GetObjects()) {
		it->Position.x += 32;
		it->Position.y += 32;
	}
}

void FarmScene::ConstructUI() {  
    // Background
	if (FieldId == 1)
		AddNewObject(new Engine::Label("Player 1", "pirulen.ttf", 34, 1295, 20));
	else
		AddNewObject(new Engine::Label("Player 2", "pirulen.ttf", 34, 1295, 20));
	UIGroup->AddNewObject(new Engine::Image("stage-select/background.png", 1280, 0, 320, 832));
	UIGroup->AddNewObject(UIMoney = new Engine::Label(std::string("$") + std::to_string(GetMoney()), "pirulen.ttf", 26, 1295, 75));
	PlantButton* btn;
	// Button 1
	btn = new PlantButton("play/floor.png", "play/dirt.png",
		Engine::Sprite("play/tower-base.png", 1294, 136, 0, 0, 0, 0),
		Engine::Sprite("farm/wheat.png", 1294, 136 - 8, 0, 0, 0, 0)
		, 1294, 136, getSeedScene()->GetSeedNumber(FieldId, 0));
	// Reference: Class Member Function Pointer and std::bind.
	btn->SetOnClickCallback(std::bind(&FarmScene::UIBtnClicked, this, 0));
	UIGroup->AddNewControlObject(btn);
	// Button 2
	btn = new PlantButton("play/floor.png", "play/dirt.png",
		Engine::Sprite("play/tower-base.png", 1370, 136, 0, 0, 0, 0),
		Engine::Sprite("farm/vegetable.png", 1370, 136 - 8, 0, 0, 0, 0)
		, 1370, 136, getSeedScene()->GetSeedNumber(FieldId, 1));
	btn->SetOnClickCallback(std::bind(&FarmScene::UIBtnClicked, this, 1));
	UIGroup->AddNewControlObject(btn);
	// Button 3
	btn = new PlantButton("play/floor.png", "play/dirt.png",
		Engine::Sprite("play/tower-base.png", 1446, 136, 0, 0, 0, 0),
		Engine::Sprite("farm/apple.png", 1446, 136, 0, 0, 0, 0)
		, 1446, 136, getSeedScene()->GetSeedNumber(FieldId, 2));
	btn->SetOnClickCallback(std::bind(&FarmScene::UIBtnClicked, this, 2));
	UIGroup->AddNewControlObject(btn);
	// Button 4
	btn = new PlantButton("play/floor.png", "play/dirt.png",
		Engine::Sprite("play/tower-base.png", 1522, 136, 0, 0, 0, 0),
		Engine::Sprite("farm/flower.png", 1522, 136, 0, 0, 0, 0)
		, 1522, 136, getSeedScene()->GetSeedNumber(FieldId, 3));
	btn->SetOnClickCallback(std::bind(&FarmScene::UIBtnClicked, this, 3));
	UIGroup->AddNewControlObject(btn);
	// Sickle
	btn = new PlantButton("play/floor.png", "play/dirt.png",
		Engine::Sprite("play/tower-base.png", 1294, 220, 0, 0, 0, 0),
		Engine::Sprite("farm/sickle.png", 1294, 220, 0, 0, 0, 0)
		, 1294, 220, 1);
    btn->SetOnClickCallback(std::bind(&FarmScene::UIBtnClicked, this, 4));
    UIGroup->AddNewControlObject(btn);

	//int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
	//int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
	//int shift = 135 + 25;
}

void FarmScene::UIBtnClicked(int id) {
	if (preview)
		UIGroup->RemoveObject(preview->GetObjectIterator());
    // TODO: [CUSTOM-TURRET]: On callback, create the turret.
	//cout<<"here "<<getSeedScene()->GetSeedNumber(FieldId, 0);
	//cout << "f" << endl;
	if (id == 0) {
		if (getSeedScene()->GetSeedNumber(FieldId, 0) > 0) {
			preview = new WheatPlant(0, 0);
			preview->state = 1;
		} else {
			AudioHelper::PlayAudio("false.wav");
		}
		
	} else if (id == 1 ) {
		if(getSeedScene()->GetSeedNumber(FieldId, 1) > 0){
			preview = new VegetablePlant(0, 0);
			preview->state = 2;
		}else AudioHelper::PlayAudio("false.wav");
		
		//cout << "f" << endl;
	} else if (id == 2){
		if(getSeedScene()->GetSeedNumber(FieldId, 2) > 0){
			preview = new ApplePlant(0, 0);
			preview->state = 3;
		}else AudioHelper::PlayAudio("false.wav");
		
	} else if (id == 3) {
		if(getSeedScene()->GetSeedNumber(FieldId, 3) > 0){
			preview = new FlowerPlant(0, 0);
			preview->state = 4;
		}else AudioHelper::PlayAudio("false.wav");
		
	} else if (id == 4) {
		preview = new SicklePlant(0, 0);
		preview->state = 5;
	}

	if (!preview)
		return;
	preview->Position = Engine::GameEngine::GetInstance().GetMousePosition();
	preview->Tint = al_map_rgba(255, 255, 255, 200);
	preview->Enabled = false;
	preview->Preview = true;
	UIGroup->AddNewObject(preview);
	OnMouseMove(Engine::GameEngine::GetInstance().GetMousePosition().x, Engine::GameEngine::GetInstance().GetMousePosition().y);
}

bool FarmScene::CheckSpaceValid(int x, int y) {
	/*for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++)
			cout << fieldState[i][j] << "!" << endl;*/

	if ( x < 9 || 11 < x || y < 5 || 7 < y) { // 9 <= x <= 11, 5 <= y <= 7
		return false;
	}	
	else if (fieldState[y - 5][x - 9] != TILE_DIRT) {
		return false;
	}
	else
		return true;
}

void FarmScene::OnMouseDown(int button, int mx, int my) {
	if ((button & 1) && !imgTarget->Visible && preview) {
		// Cancel plant construct.
		UIGroup->RemoveObject(preview->GetObjectIterator());
		preview = nullptr;
	}
	IScene::OnMouseDown(button, mx, my);
}

void FarmScene::OnMouseMove(int mx, int my) {
	IScene::OnMouseMove(mx, my);
	const int x = mx / BlockSize;
	const int y = my / BlockSize;
	if (!preview || x < 9 || 11 < x || y < 5 || 7 < y) {
		imgTarget->Visible = false;
		return;
	}
	imgTarget->Visible = true;
	imgTarget->Position.x = x * BlockSize;
	imgTarget->Position.y = y * BlockSize;
}

void FarmScene::OnMouseUp(int button, int mx, int my) {
	IScene::OnMouseUp(button, mx, my);
	if (!imgTarget->Visible)
		return;
	const int x = mx / BlockSize;
	const int y = my / BlockSize;

	//cout << "xx: " << x << " yy: " << y << endl;
	if (button & 1) {
		//cout << x << " " << y << endl;
		if (fieldState[y - 5][x - 9] == TILE_DIRT)
		{
			//cout << "== TILE_DIRT" << endl;
			if (!preview) // 沒有預覽作物
				return;
			if (preview->state == 5) // Sickle
				return;
			// Check if valid.
			if (!CheckSpaceValid(x, y)) // invalid
			{
				cout << "invalid" << endl;
				Engine::Sprite* sprite;
				GroundEffectGroup->AddNewObject(sprite = new DirtyEffect("play/target-invalid.png", 1, x * BlockSize + BlockSize / 2, y * BlockSize + BlockSize / 2));
				
				return;
			}
			// Purchase.
			//EarnMoney(preview->GetPrice());
			// Remove Preview.
			preview->GetObjectIterator()->first = false;
			UIGroup->RemoveObject(preview->GetObjectIterator());
			// Construct real plant.
			preview->Position.x = x * BlockSize + BlockSize / 2;
			preview->Position.y = y * BlockSize + BlockSize / 2;
			preview->Enabled = true;
			preview->Preview = false;
			preview->Tint = al_map_rgba(255, 255, 255, 255);
			PlantGroup->AddNewObject(preview);
			AudioHelper::PlayAudio("planting.wav");
			// To keep responding when paused.
			preview->Update(0);

			//cout << "Position.x: " << preview->Position.x << " Position.y: " << preview->Position.y << endl;
			// add new crop's fieldstate
			switch (preview->state) {
				case 1: {
					fieldState[y - 5][x - 9] = TILE_WHEAT;
					getSeedScene()->CostMoney(FieldId, 0);
					break;
				}
				case 2: {
					fieldState[y - 5][x - 9] = TILE_VEGETABLE;
					getSeedScene()->CostMoney(FieldId, 1);
					break;
				}
				case 3: {
					fieldState[y - 5][x - 9] = TILE_APPLE;
					getSeedScene()->CostMoney(FieldId, 2);
					break;
				}
				case 4: {
					fieldState[y - 5][x - 9] = TILE_FLOWER;
					getSeedScene()->CostMoney(FieldId, 3);
					break;
				}
			}

			// Remove Preview.
			preview = nullptr;
			OnMouseMove(mx, my);

			/*for(int i = 0; i < 3; i++)
				for(int j = 0; j < 3; j++)
					cout << fieldState[i][j] << "!!!" << endl;*/

			/*for (auto& it : PlantGroup->GetObjects()) {
				cout << "it->Position.x: " << it->Position.x << endl;
				cout <<  "it->Position.y: " << it->Position.y << endl;
			}*/

		} else if (fieldState[y - 5][x - 9] != TILE_DIRT) {
			
			if (preview->state != 5)
				return;
			//cout << "!= TILE_DIRT " << y - 5 << " " << x - 9 << endl;
			// 採收植物
			for (auto& it : PlantGroup->GetObjects()) {
				Plant* plant = dynamic_cast<Plant*>(it);

				//cout << "plant->harvest " << plant->harvest << endl;
				/*if (!(plant->harvest)) {
					cout << "timer: " << plant->harvestTimer << " time: " << plant->harvestTime << endl;
					cout << "!" << endl;
					break;
				} else {
					cout << "YE!" << endl;
				}*/
				Engine::Point pnt;
				pnt.x = x * BlockSize + BlockSize / 2;
				pnt.y = y * BlockSize + BlockSize / 2;

				//cout << "x: " << x << "y: " << y << endl;
				//cout << "pnt.x: " << pnt.x << endl;
				//cout <<  "pnt.y: " << pnt.y << endl;
				//cout << "it->Position.x: " << it->Position.x << endl;
				//cout <<  "it->Position.y: " << it->Position.y << endl;

				if (it->Position.x == pnt.x && it->Position.y == pnt.y && plant->harvestTimer >= plant->harvestTime) {
					UpGroup->AddNewObject(new Engine::Image("farm/Up.png", 576, 192, 192, 192));
					preview->GetObjectIterator()->first = true; // It is a eraser tool, the preview tool must be deleted after it delete the specified turret on the map
					UIGroup->RemoveObject(preview->GetObjectIterator()); // Remove the tool object from UIGroup and also delete the object instance(memory) because we don't need the tool any more
					// 增加金錢、更新timer
					AudioHelper::PlayAudio("swing.wav");
					EarnMoney(plant->getPrice());
					plant->harvestTimer = 0.0;
					it->GetObjectIterator()->first = true;
					PlantGroup->RemoveObject(it->GetObjectIterator());
					preview = nullptr;
					// 更新植物狀態
					fieldState[y - 5][x - 9] = TILE_DIRT;
					break;
				}
			}
			OnMouseMove(mx, my);
		}	
	}
}

void FarmScene::EarnMoney(int money) {
	int money1, money2;
	// Read money
	string filename = string("../Resource/money.txt");
    ifstream fin(filename);
    string line;
    getline(fin, line);
    stringstream ss(line);
    ss >> money1 >> money2;

	if (FieldId == 1) {
		money1 += money;
		UIMoney->Text = std::string("$") + std::to_string(money1);
	} else {
		money2 += money;
		UIMoney->Text = std::string("$") + std::to_string(money2);
	}

	// Write
    ofstream outfile(filename, std::ios::trunc);
    outfile << std::to_string(money1) + " " + std::to_string(money2)  << std::endl;
    outfile.flush();
    outfile.close();
}

int FarmScene::GetMoney() {
	int money1, money2;
	string filename = string("../Resource/money.txt");
    ifstream fin(filename);
    string line;
    getline(fin, line);
    stringstream ss(line);
    ss >> money1 >> money2;
	fin.close();

	if (FieldId == 1) {
		return money1;
	} else {
		return money2;
	}
}