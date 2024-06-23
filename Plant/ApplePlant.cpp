#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "Engine/AudioHelper.hpp"
#include "Engine/Group.hpp"
#include "ApplePlant.hpp"
#include "Scene/FarmScene.hpp"
#include "Engine/Point.hpp"

const int ApplePlant::Price = 30;
const float ApplePlant::HarvestTime = 40.0; // seconds
ApplePlant::ApplePlant(float x, float y) :
	Plant("play/tower-base.png", "farm/Seed3.png", x, y, Price, 0, HarvestTime, 0.0) {
	// Move center downward, since we the turret head is slightly biased upward.
	//Anchor.y += 8.0f / GetBitmapHeight();
}
int ApplePlant::Harvest() {
	return HarvestTime;
}

