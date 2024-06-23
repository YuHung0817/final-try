#ifndef PLANTBUTTON_HPP
#define PLANTBUTTON_HPP
#include <string>

#include "UI/Component/ImageButton.hpp"
#include "Engine/Sprite.hpp"

class FarmScene;

class PlantButton : public Engine::ImageButton {
protected:
    FarmScene* getFarmScene();
public:
	int seed;
	Engine::Sprite Base;
	Engine::Sprite Plant;
	PlantButton(std::string img, std::string imgIn, Engine::Sprite Base, Engine::Sprite Plant, float x, float y, int seed);
	void Update(float deltaTime) override;
	void Draw() const override;
};
#endif // PLANTBUTTON_HPP
