#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "Engine/AudioHelper.hpp"
#include "Engine/Group.hpp"
#include "ApplePlant.hpp"
#include "Scene/FarmScene.hpp"
#include "Engine/Point.hpp"

const int ApplePlant::HarvestTime = 60; // 60 seconds
ApplePlant::ApplePlant(float x, float y) :
	Plant("play/tower-base.png", "farm/apple.png", x, y, 200, HarvestTime, 0.5) {
	// Move center downward, since we the turret head is slightly biased upward.
	Anchor.y += 8.0f / GetBitmapHeight();
}

