#include "Fruit.h"
using namespace std;
Fruit::Fruit(): Food(){

}
Fruit::Fruit(string name, long price, Timestamp* ts):Food(name,price,ts){

}
Fruit::Fruit(Fruit& f):Food(f){

}
Fruit::~Fruit(){

}
string Fruit::getCategory(){
    return "fruit";
}