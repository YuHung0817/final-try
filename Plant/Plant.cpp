#include <allegro5/color.h>
#include <allegro5/allegro_primitives.h>
#include <cmath>
#include <utility>

#include "Engine/GameEngine.hpp"
#include "Engine/Group.hpp"
#include "Engine/IObject.hpp"
#include "Engine/IScene.hpp"
#include "Engine/Point.hpp"
#include "Engine/Resources.hpp"
#include "Plant/Plant.hpp"
#include "Scene/FarmScene.hpp"

#include <iostream>
using namespace std;
//bool harvest;

FarmScene* Plant::getFarmScene() {
	return dynamic_cast<FarmScene*>(Engine::GameEngine::GetInstance().GetActiveScene());
}
Plant::Plant(std::string imgBase, std::string imgPlant, float x, float y, int price, float coolDown, float harvestTime, float harvestTimer) :
	Sprite(imgPlant, x, y), coolDown(coolDown), imgBase(imgBase, x, y), price(price), harvestTime(harvestTime), harvestTimer(harvestTimer){
	//cout << "Seed" << endl;
	//CollisionRadius = radius;
	//cout << "pTimer: " << harvestTimer << endl;
	bool harvest = false;
    if (imgPlant.find("Seed1") != std::string::npos)
        plantName = "wheat";
    else if (imgPlant.find("Seed2") != std::string::npos)
        plantName = "vegetable";
    else if (imgPlant.find("Seed3") != std::string::npos)
        plantName = "apple";
    else plantName = "flower";
}
void Plant::Update(float deltaTime) {
	imgBase.Position = Position;
	if (!Enabled)
		return;
	harvestTimer += deltaTime;

	//cout << "harvestTimer: " << harvestTimer << endl;
	//cout << "harvestTime: " << harvestTime << endl;
	//cout << "harvest" << harvest << endl;
	if (harvestTimer >= harvestTime) {
		//cout << "true" << endl;
		//Harvest();
		harvest = true;

		//cout << "plant: " << plantName << " H: " << harvest << endl;
		//cout << plantName << endl;
        if (plantName == "wheat")
            bmp = Engine::Resources::GetInstance().GetBitmap("farm/wheat.png");
        else if (plantName == "vegetable")
            bmp = Engine::Resources::GetInstance().GetBitmap("farm/vegetable.png");
        else if (plantName == "apple")
            bmp = Engine::Resources::GetInstance().GetBitmap("farm/apple.png");
        else if (plantName == "flower")
			bmp = Engine::Resources::GetInstance().GetBitmap("farm/flower.png");
	}
    Sprite::Update(deltaTime);
}
void Plant::Draw() const {
	/*if (Preview) {
		al_draw_filled_circle(Position.x, Position.y, CollisionRadius, al_map_rgba(0, 255, 0, 50));
	}*/
	//imgBase.Draw();
	Sprite::Draw();
	//al_draw_circle(Position.x, Position.y, CollisionRadius, al_map_rgb(0, 0, 255), 2);}
}

void Plant::Harvest() {
	//FarmScene* scene = getFarmScene();
	harvest = true;
}

int Plant::getPrice() {
	return price;
}

