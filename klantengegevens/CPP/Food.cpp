#include "Food.h"
Food::Food(): Product(){
    this->before = NULL;
}
Food::~Food(){
    delete this->before;
}
Food::Food(string name, long price, Timestamp* ts): Product(name,price){
    this->before = ts;
}
Food::Food(Food& food): Product(food){
    this->before = new Timestamp(*(food.before));
}
