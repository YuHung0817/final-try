#ifndef APPLEPLANT_HPP
#define APPLEPLANT_HPP
#include "Plant.hpp"

class ApplePlant: public Plant {
protected:
    static const int Price;

public:
    ApplePlant(float x, float y);
    int Harvest();
    //float harvestTimer;
    static const float HarvestTime;
};
#endif // APPLEPLANT_HPP
