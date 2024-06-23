#ifndef WHEATPLANT_HPP
#define WHEATPLANT_HPP
#include "Plant.hpp"

class WheatPlant: public Plant {
protected:
	static const int Price;

public:
    WheatPlant(float x, float y);
	int Harvest();
    //float harvestTimer;
    static const float HarvestTime;
};
#endif // WHEATPLANT_HPP
