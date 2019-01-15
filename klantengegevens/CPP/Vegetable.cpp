#include "Vegetable.h"
#include "../memleak/debug_new.h"

using namespace std;

Vegetable::Vegetable() : Food() {}
Vegetable::Vegetable(string name, long price, Timestamp* ts) : Food(name, price, ts){}
Vegetable::Vegetable(Vegetable& f) : Food(f){}
Vegetable::~Vegetable(){}

string Vegetable::getCategory(){
	return "Vegetable";
}