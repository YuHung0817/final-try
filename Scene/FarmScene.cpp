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
using namespace std;

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
	AddNewControlObject(UIGroup = new Group());
	ReadField();
	cout << "1" << endl;
	//ReadTime();
	cout << "2" << endl;
    ConstructUI(); 
	imgTarget = new Engine::Image("play/target.png", 0, 0); //顯示目標圖像
	imgTarget->Visible = false;
	preview = nullptr; //預覽將要放置的作物。它被用來暫時顯示在遊戲場景中，以便玩家可以在放置之前看到其位置和外觀。
	UIGroup->AddNewObject(imgTarget);

	if (FieldId == 1)
		AddNewObject(new Engine::Label("Player 1", "pirulen.ttf", 38, 1320, 48));
	else
		AddNewObject(new Engine::Label("Player 2", "pirulen.ttf", 38, 1320, 48));

	Engine::ImageButton* btn;
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", 1310, halfH + 270 , 260, 90);
    btn->SetOnClickCallback(std::bind(&FarmScene::BackOnClick, this));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Back", "pirulen.ttf", 46, 1445, halfH + 315, 0, 0, 0, 255, 0.5, 0.5));
}
void FarmScene::Terminate() {
	//AudioHelper::StopBGM(bgmId);
	//AudioHelper::StopSample(deathBGMInstance);
	//deathBGMInstance = std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE>();
	IScene::Terminate();
}
void FarmScene::Update(float deltaTime) {
	// If we use deltaTime directly, then we might have Bullet-through-paper problem.
	//cout << "Update" << endl;
	//Plant* plant;
	// Compensate the time lost.
	// 將過去的時間 ticks 傳遞給植物對象的 Update 方法，讓植物更新它的內部狀態。
	//plant->Update(ticks);
	if (preview) {
		preview->Position = Engine::GameEngine::GetInstance().GetMousePosition();
		// To keep responding when paused.
		preview->Update(deltaTime);
	}
	//cout << "Update Success" << endl;
}

void FarmScene::BackOnClick() {
	WritetoField();
	//WritetoTime();
	Engine::GameEngine::GetInstance().ChangeScene("stage-select");
}

void FarmScene::WritetoField() {
	std::ofstream fout;
	string filename = string("Resource/farmfield") + std::to_string(FieldId) + ".txt";
	/*if (fout.good()) {
		remove();
	}*/
	fout.open(filename);
	cout << "Write1" << endl;
	//刪掉裡面的資料
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
			fout << c;
			cout << "Write2" << endl;
		}
		fout << '\n';
	}
	cout << "Write3" << endl;
	fout.close();
	cout << "Write4" << endl;
}

void FarmScene::WritetoTime() {
	std::ofstream fout;
	string filename = string("Resource/farmtime") + std::to_string(FieldId) + ".txt";
	fout.open(filename);
	cout << "Write1" << endl;
	
	//刪掉
	/*for (int i = 0; i < FieldWidth * FieldHeight; i++) {
		fout << timer[i];
		cout << "timer " << i << ": " << timer[i] << endl;
	}*/

	for (auto& it : PlantGroup->GetObjects()) {
		Plant* plant = dynamic_cast<Plant*>(it);
		int i = floor(plant->Position.x / BlockSize);
		int j = floor(plant->Position.y / BlockSize) - 1;

		fout << (timer[i * 3 + j] = plant->harvestTimer);
		cout << "timer " << i * 3 + j << ": " << timer[i * 3 + j] << endl;

		for (int k = 0; k < 9; k++) {
			if (timer[k] == 0)
				fout << (timer[k] = -1.0);
		}
	}
	timer.clear();

	cout << "Write3" << endl;
	fout.close();
	cout << "Write4" << endl;
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
    std::string filename = std::string("Resource/farmtime") + std::to_string(FieldId) + ".txt";
	// Read time file.
	float time;
	timeData.clear();
	std::ifstream fin(filename);
	while (fin >> time) {
		timeData.emplace_back(time);
		cout << "2.5" << endl;
	}
	fin.close();
	cout << "3" << endl;
	for (auto& it : PlantGroup->GetObjects()) {
		Plant* plant = dynamic_cast<Plant*>(it);
		int i = floor(plant->Position.x / BlockSize);
		int j = floor(plant->Position.y / BlockSize);

		if (timeData[i * 3 + j] != -1.0)
			plant->harvestTimer = timeData[i * 3 + j];
	}
	cout << "4" << endl;
}

void FarmScene::ReadField() {
	string filename = string("Resource/farmfield") + std::to_string(FieldId) + ".txt";
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
			if (type == '0') {
                fieldState[i][j] = TILE_DIRT;
            } else if (type == '1') {
                fieldState[i][j] = TILE_WHEAT;
				//TileFieldGroup->AddNewObject(new Engine::Image("farm/wheat.png", (j + 9) * BlockSize, (i + 5) * BlockSize, BlockSize, BlockSize, ((j + 9) * BlockSize + BlockSize / 2) / 1600, ((i + 5) * BlockSize + BlockSize / 2) / 832));
				//PlantGroup->AddNewObject(new Engine::Image("farm/wheat.png", (j + 9) * BlockSize, (i + 5) * BlockSize, BlockSize, BlockSize));
				PlantGroup->AddNewObject(new Engine::Image("farm/wheat.png", (j + 9) * BlockSize, (i + 5) * BlockSize, BlockSize, BlockSize, ((j + 9) * BlockSize + BlockSize / 2) / 1600, ((i + 5) * BlockSize + BlockSize / 2) / 832));
            } else if (type == '2') {
                fieldState[i][j] = TILE_VEGETABLE;
				//TileFieldGroup->AddNewObject(new Engine::Image("farm/wheat.png", (j + 9) * BlockSize, (i + 5) * BlockSize, BlockSize, BlockSize, ((j + 9) * BlockSize + BlockSize / 2) / 1600, ((i + 5) * BlockSize + BlockSize / 2) / 832));
                //PlantGroup->AddNewObject(new Engine::Image("farm/wheat.png", (j + 9) * BlockSize, (i + 5) * BlockSize, BlockSize, BlockSize));
				PlantGroup->AddNewObject(new Engine::Image("farm/vegetable.png", (j + 9) * BlockSize, (i + 5) * BlockSize, BlockSize, BlockSize, ((j + 9) * BlockSize + BlockSize / 2) / 1600, ((i + 5) * BlockSize + BlockSize / 2) / 832));
            } else if (type == '3') {
                fieldState[i][j] = TILE_APPLE;
				//TileFieldGroup->AddNewObject(new Engine::Image("farm/wheat.png", (j + 9) * BlockSize, (i + 5) * BlockSize, BlockSize, BlockSize, ((j + 9) * BlockSize + BlockSize / 2) / 1600, ((i + 5) * BlockSize + BlockSize / 2) / 832));
                //PlantGroup->AddNewObject(new Engine::Image("farm/apple.png", (j + 9) * BlockSize, (i + 5) * BlockSize, BlockSize, BlockSize));
				PlantGroup->AddNewObject(new Engine::Image("farm/apple.png", (j + 9) * BlockSize, (i + 5) * BlockSize, BlockSize, BlockSize, ((j + 9) * BlockSize + BlockSize / 2) / 1600, ((i + 5) * BlockSize + BlockSize / 2) / 832));
            } else if (type == '4') {
                fieldState[i][j] = TILE_FLOWER;
				//TileFieldGroup->AddNewObject(new Engine::Image("farm/wheat.png", (j + 9) * BlockSize, (i + 5) * BlockSize, BlockSize, BlockSize, ((j + 9) * BlockSize + BlockSize / 2) / 1600, ((i + 5) * BlockSize + BlockSize / 2) / 832));
                //PlantGroup->AddNewObject(new Engine::Image("farm/flower.png", (j + 9) * BlockSize, (i + 5) * BlockSize, BlockSize, BlockSize));
				PlantGroup->AddNewObject(new Engine::Image("farm/flower.png", (j + 9) * BlockSize, (i + 5) * BlockSize, BlockSize, BlockSize, ((j + 9) * BlockSize + BlockSize / 2) / 1600, ((i + 5) * BlockSize + BlockSize / 2) / 832));
            } else {
                //throw std::ios_base::failure("Map data is corrupted.");
            }
		}
	}

	/*for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++)
			cout << "Read: " << fieldState[j][i] << "!!" << endl;*/
}

void FarmScene::ConstructUI() {  
    // Background
	UIGroup->AddNewObject(new Engine::Image("play/sand.png", 1280, 0, 320, 832));
	PlantButton* btn;
	// Button 1
	btn = new PlantButton("play/floor.png", "play/dirt.png",
		Engine::Sprite("play/tower-base.png", 1294, 136, 0, 0, 0, 0),
		Engine::Sprite("farm/wheat.png", 1294, 136 - 8, 0, 0, 0, 0)
		, 1294, 136, WheatPlant::HarvestTime);
	// Reference: Class Member Function Pointer and std::bind.
	btn->SetOnClickCallback(std::bind(&FarmScene::UIBtnClicked, this, 0));
	UIGroup->AddNewControlObject(btn);
	// Button 2
	btn = new PlantButton("play/floor.png", "play/dirt.png",
		Engine::Sprite("play/tower-base.png", 1370, 136, 0, 0, 0, 0),
		Engine::Sprite("farm/vegetable.png", 1370, 136 - 8, 0, 0, 0, 0)
		, 1370, 136, VegetablePlant::HarvestTime);
	btn->SetOnClickCallback(std::bind(&FarmScene::UIBtnClicked, this, 1));
	UIGroup->AddNewControlObject(btn);
	// Button 3
	btn = new PlantButton("play/floor.png", "play/dirt.png",
		Engine::Sprite("play/tower-base.png", 1446, 136, 0, 0, 0, 0),
		Engine::Sprite("farm/apple.png", 1446, 136, 0, 0, 0, 0)
		, 1446, 136, ApplePlant::HarvestTime);
	btn->SetOnClickCallback(std::bind(&FarmScene::UIBtnClicked, this, 2));
	UIGroup->AddNewControlObject(btn);
	// Button 4
	btn = new PlantButton("play/floor.png", "play/dirt.png",
		Engine::Sprite("play/tower-base.png", 1522, 136, 0, 0, 0, 0),
		Engine::Sprite("farm/flower.png", 1522, 136, 0, 0, 0, 0)
		, 1522, 136, FlowerPlant::HarvestTime);
	btn->SetOnClickCallback(std::bind(&FarmScene::UIBtnClicked, this, 3));
	UIGroup->AddNewControlObject(btn);

	// Sickle
	btn = new PlantButton("play/floor.png", "play/dirt.png",
		Engine::Sprite("play/tower-base.png", 1294, 220, 0, 0, 0, 0),
		Engine::Sprite("farm/sickle.png", 1294, 220, 0, 0, 0, 0)
		, 1294, 220, SicklePlant::HarvestTime);
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
	cout<<"here "<<getSeedScene()->GetSeedNumber(FieldId, 0);
	if (id == 0 && getSeedScene()->GetSeedNumber(FieldId, 0) > 0) {
		preview = new WheatPlant(0, 0);
		preview->state = 1;
	} else if (id == 1 && getSeedScene()->GetSeedNumber(FieldId, 1) > 0) {
		preview = new VegetablePlant(0, 0);
		preview->state = 2;
	} else if (id == 2 && getSeedScene()->GetSeedNumber(FieldId, 2) > 0){
		preview = new ApplePlant(0, 0);
		preview->state = 3;
	} else if (id == 3 && getSeedScene()->GetSeedNumber(FieldId, 3) > 0) {
		preview = new FlowerPlant(0, 0);
		preview->state = 4;
	} else if (id == 4) {
		preview = new SicklePlant(0, 0);
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
		//cout << "CSV1" << endl;
		return false;
	}	
	else if (fieldState[y - 5][x - 9] != TILE_DIRT) {
		cout << "CSV2" << endl;
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
	if (button & 1) {
		//cout << x << " " << y << endl;
		if (fieldState[y - 5][x - 9] == TILE_DIRT)
		{
			cout << "== TILE_DIRT" << endl;
			if (!preview) // 沒有預覽作物
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
			// To keep responding when paused.
			preview->Update(0);

			cout << "Position.x: " << preview->Position.x << " Position.y: " << preview->Position.y << endl;
			// add new crop's fieldstate
			switch (preview->state) {
				case 1: {
					
					fieldState[y - 5][x - 9] = TILE_WHEAT;
					cout << "!!!!!!!!" << endl;
					getSeedScene()->CostMoney(FieldId, 0);
					cout << "!000" << endl;
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

			for(int i = 0; i < 3; i++)
				for(int j = 0; j < 3; j++)
					cout << fieldState[i][j] << "!!!" << endl;
		} else if (fieldState[y - 5][x - 9] != TILE_DIRT) {
			//cout << "!= TILE_DIRT " << y - 5 << " " << x - 9 << endl;
			// 採收植物
			Engine::Point pnt;
			//pnt.x = x * BlockSize + BlockSize / 2;
			//pnt.y = y * BlockSize + BlockSize / 2;
			preview->GetObjectIterator()->first = true; // It is a eraser tool, the preview tool must be deleted after it delete the specified turret on the map
            UIGroup->RemoveObject(preview->GetObjectIterator()); // Remove the tool object from UIGroup and also delete the object instance(memory) because we don't need the tool any more

			for (auto& it : PlantGroup->GetObjects()) {
				Plant* plant = dynamic_cast<Plant*>(it);
				// && plant->harvest
				cout << "Position.x: " << Position.x << " Position.y: " << Position.y << endl;
				cout << "pnt.x: " << pnt.x << " pnt.y: " << pnt.y << endl;
				if ((it->Position.x) == pnt.x && (it->Position.y) == pnt.y) {
					cout << "uuuuu" << endl;
					// 增加金錢、更新timer
					// Remove the plant from the group
					///EarnMoney(plant->getPrice());
					//plant->harvestTimer = -1.0;
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