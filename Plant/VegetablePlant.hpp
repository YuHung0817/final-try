#ifndef VEGETABLEPLANT_HPP
#define VEGETABLEPLANT_HPP
#include "Plant.hpp"

class VegetablePlant: public Plant {
protected:
    static const int Price;
public:
    VegetablePlant(float x, float y);
    int Harvest();
    //float harvestTimer;
    static const float HarvestTime;
};
#endif // VEGETABLEPLANT_HPP
