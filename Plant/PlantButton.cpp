#include <allegro5/color.h>

#include "Engine/GameEngine.hpp"
#include "Engine/IScene.hpp"
#include "Scene/FarmScene.hpp"
#include "PlantButton.hpp"

FarmScene* PlantButton::getFarmScene() {
	return dynamic_cast<FarmScene*>(Engine::GameEngine::GetInstance().GetActiveScene());
}
PlantButton::PlantButton(std::string img, std::string imgIn, Engine::Sprite Base, Engine::Sprite Plant, float x, float y, int seed) :
	ImageButton(img, imgIn, x, y), seed(seed), Base(Base), Plant(Plant) {
}
void PlantButton::Update(float deltaTime) {
	/*ImageButton::Update(deltaTime);
	if (getFarmScene()->Getseed() >= seed) {
		Enabled = true;
		Base.Tint = Plant.Tint = al_map_rgba(255, 255, 255, 255);
	} else {
		Enabled = false;
		Base.Tint = Plant.Tint = al_map_rgba(0, 0, 0, 160);
	}*/
}
void PlantButton::Draw() const {
	ImageButton::Draw();
	Base.Draw();
	Plant.Draw();
}
