#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "Engine/AudioHelper.hpp"
#include "Engine/Group.hpp"
#include "FlowerPlant.hpp"
#include "Scene/FarmScene.hpp"
#include "Engine/Point.hpp"

#include <iostream>
using namespace std;

const int FlowerPlant::Price = 100;
const float FlowerPlant::HarvestTime = 60.0; // seconds
FlowerPlant::FlowerPlant(float x, float y) :
	Plant("play/tower-base.png", "farm/Seed4.png", x, y, Price, 0.0, HarvestTime, 0.0) {
	// Move center downward, since we the turret head is slightly biased upward.
	//Anchor.y += 8.0f / GetBitmapHeight();
}
int FlowerPlant::Harvest() {
	return HarvestTime;
}
/*void FlowerPlant::HarvestTimerUpdate(int deltaTime) {
	HarvestTimer += deltaTime;
}*/