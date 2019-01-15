#ifndef FRUIT_H
#define FRUIT_H

#include "Food.h"

class Fruit : public Food{
public:
	Fruit();
	Fruit(std::string name, long price, Timestamp* ts);
	Fruit(Fruit& f);
	~Fruit();

	virtual std::string getCategory();
};

#endif