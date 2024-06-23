#ifndef FLOWERLANT_HPP
#define FLOWERLANT_HPP
#include "Plant.hpp"

class FlowerPlant: public Plant {
protected:
    static const int Price;
public:
    FlowerPlant(float x, float y);
    int Harvest();
    //float harvestTimer;
    static const float HarvestTime;
};
#endif // FLOWERPLANT_HPP
