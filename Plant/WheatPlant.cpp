#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "Engine/AudioHelper.hpp"
#include "Engine/Group.hpp"
#include "WheatPlant.hpp"
#include "Scene/FarmScene.hpp"
#include "Engine/Point.hpp"

const int WheatPlant::Price = 10;
const float WheatPlant::HarvestTime = 10.0; // seconds

WheatPlant::WheatPlant(float x, float y) :
	Plant("play/tower-base.png", "farm/Seed1.png", x, y, Price, 0.0, HarvestTime, 0.0) {
	// Move center downward, since we the turret head is slightly biased upward.
	//Anchor.y += 8.0f / GetBitmapHeight();
}

int WheatPlant::Harvest() {
	return HarvestTime;
}
/*void WheatPlant::HarvestTimerUpdate(int deltaTime) {
	HarvestTimer += deltaTime;
}*/

