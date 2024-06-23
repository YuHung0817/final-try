#include <allegro5/color.h>

#include "Engine/GameEngine.hpp"
#include "Engine/IScene.hpp"
#include "Scene/FarmScene.hpp"
#include "PlantButton.hpp"
#include "Scene/SeedStoreScene.h"
#include <iostream>
using namespace std;


FarmScene* PlantButton::getFarmScene() {
	return dynamic_cast<FarmScene*>(Engine::GameEngine::GetInstance().GetScene("farm"));
}
SeedStoreScene* PlantButton::getSeedScene() {
    return dynamic_cast<SeedStoreScene*>(Engine::GameEngine::GetInstance().GetScene("seed-store"));
}

PlantButton::PlantButton(std::string img, std::string imgIn, Engine::Sprite Base, Engine::Sprite Plant, float x, float y, int seed) :
	ImageButton(img, imgIn, x, y), Base(Base), Plant(Plant), seed(seed) {
}
void PlantButton::Update(float deltaTime) {
	ImageButton::Update(deltaTime);
	//int seed number = cout << getSeedScene()->GetSeedNumber(getFarmScene()->FieldId, seedtype) << endl;
	//if (dynamic_cast<SeedStoreScene*>(Engine::GameEngine::GetInstance().GetScene("seed-store"))->GetSeedNumber(getFarmScene()->FieldId, seedtype) > 0) {
	//int seedNumber = getSeedScene()->GetSeedNumber(getFarmScene()->FieldId, seedtype);
	//cout << "seedNumber: " << seedNumber << endl;
	//cout << "seedtype: " << seedtype << endl;
	if (seed > 0) {
		//cout << "()()" << endl;
		Enabled = true;
		Base.Tint = Plant.Tint = al_map_rgba(255, 255, 255, 255);
		//cout << "()" << endl;
	} else {
		Enabled = false;
		Base.Tint = Plant.Tint = al_map_rgba(0, 0, 0, 150);
		//cout << "False" << endl;
	}
}
void PlantButton::Draw() const {
	ImageButton::Draw();
	Base.Draw();
	Plant.Draw();
}
