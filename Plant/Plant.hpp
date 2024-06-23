#ifndef PLANT_HPP
#define PLANT_HPP
#include <allegro5/base.h>
#include <list>
#include <string>

#include "Engine/Sprite.hpp"
//#include "Scene/FarmScene.hpp"

class FarmScene;

class Plant: public Engine::Sprite {
protected:
    float coolDown;
    float reload = 0;
    float rotateRadian = 2 * ALLEGRO_PI;

    int price;
    float harvestTime;
    Sprite imgBase;
    FarmScene* getFarmScene();

public:
    int state;
    bool Enabled = true;
    bool Preview = false;
    Plant(std::string imgBase, std::string imgPlant, float x, float y, int price, float coolDown, float harvestTime);
    void Update(float deltaTime) override;
    void Draw() const override;
    int getPrice();
    float harvestTimer;
    bool harvest;
    void Harvest();
};
#endif // PLANT_HPP
