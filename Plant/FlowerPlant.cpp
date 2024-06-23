#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "Engine/AudioHelper.hpp"
#include "Engine/Group.hpp"
#include "FlowerPlant.hpp"
#include "Scene/FarmScene.hpp"
#include "Engine/Point.hpp"

const int FlowerPlant::HarvestTime = 60; // 60 seconds
FlowerPlant::FlowerPlant(float x, float y) :
	Plant("play/tower-base.png", "farm/flower.png", x, y, 200, 0.5, HarvestTime) {
	// Move center downward, since we the turret head is slightly biased upward.
	Anchor.y += 8.0f / GetBitmapHeight();
}
