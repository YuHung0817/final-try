#include <allegro5/color.h>
#include <allegro5/allegro_primitives.h>
#include <cmath>
#include <utility>

#include "Engine/GameEngine.hpp"
#include "Engine/Group.hpp"
#include "Engine/IObject.hpp"
#include "Engine/IScene.hpp"
#include "Engine/Point.hpp"
#include "Plant/Plant.hpp"
#include "Scene/FarmScene.hpp"

#include <iostream>
using namespace std;

bool harvest = false;

FarmScene* Plant::getFarmScene() {
	return dynamic_cast<FarmScene*>(Engine::GameEngine::GetInstance().GetActiveScene());
}
Plant::Plant(std::string imgBase, std::string imgPlant, float x, float y, int price, float coolDown, float harvestTime) :
	Sprite(imgPlant, x, y), coolDown(coolDown), imgBase(imgBase, x, y), harvestTime(harvestTime) {
	//CollisionRadius = radius;
}
void Plant::Update(float deltaTime) {
	Sprite::Update(deltaTime);
	FarmScene* scene = getFarmScene();
	imgBase.Position = Position;
	cout << "Position.x: " << Position.x << "Position.y: " << Position.y << endl;
	imgBase.Tint = Tint;
	if (!Enabled)
		return;

	harvestTimer += deltaTime;
	if (harvestTimer >= harvestTime) {
		Harvest();
		harvestTimer = 0.0;
	}
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
	FarmScene* scene = getFarmScene();
	/*if (scene) {
		scene->EarnMoney(price);
	}*/
	harvest = true;
}

int Plant::getPrice() {
	return price;
}

