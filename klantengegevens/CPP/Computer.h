#ifndef COMPUTER_H
#define COMPUTER_H

#include "Product.h"

class Computer : public Product{
public:
	Computer();
	Computer(std::string name, long price);
	Computer(Computer& comp);

	virtual std::string getCategory();
};

#endif