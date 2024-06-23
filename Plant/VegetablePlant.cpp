#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "Engine/AudioHelper.hpp"
#include "Engine/Group.hpp"
#include "VegetablePlant.hpp"
#include "Scene/FarmScene.hpp"
#include "Engine/Point.hpp"

const int VegetablePlant::Price = 20;
const float VegetablePlant::HarvestTime = 20.0; // 60 seconds
VegetablePlant::VegetablePlant(float x, float y) :
	Plant("play/tower-base.png", "farm/Seed2.png", x, y, Price, 0.0, HarvestTime, 0.0) {
	// Move center downward, since we the turret head is slightly biased upward.
	//Anchor.y += 8.0f / GetBitmapHeight();
}

int VegetablePlant::Harvest() {
	return HarvestTime;
}
/*void VegetablePlant::HarvestTimerUpdate(int deltaTime) {
	HarvestTimer += deltaTime;
}*/