#ifndef VEGETABLE_H
#define VEGETABLE_H

#include "Food.h"

class Vegetable : public Food{
public:
	Vegetable();
	Vegetable(std::string name, long price, Timestamp* ts);
	Vegetable(Vegetable& f);
	~Vegetable();

	virtual std::string getCategory();
};

#endif