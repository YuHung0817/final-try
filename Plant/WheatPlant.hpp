#ifndef WHEATPLANT_HPP
#define WHEATPLANT_HPP
#include "Plant.hpp"

class WheatPlant: public Plant {
public:
	static const int HarvestTime;
    WheatPlant(float x, float y);

	int Harvest();
};
#endif // WHEATPLANT_HPP
