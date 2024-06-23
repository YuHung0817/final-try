#ifndef FLOWERLANT_HPP
#define FLOWERLANT_HPP
#include "Plant.hpp"

class FlowerPlant: public Plant {
public:
	static const int HarvestTime;
    FlowerPlant(float x, float y);
};
#endif // FLOWERPLANT_HPP
