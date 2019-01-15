#include "Computer.h"
using namespace std;
Computer::Computer() : Product(){}
Computer::Computer(string name, long price) : Product(name,price){}
Computer::Computer(Computer& comp) : Product(comp){}


string Computer::getCategory(){
    long price = this->getPrice();
    if (price > 1000){
		return "high-end";
	}
	else if (0 < price && price < 750){
		return "low-end";
	}
	else {
		return "mid";
	}
}