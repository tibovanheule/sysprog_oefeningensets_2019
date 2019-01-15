#include "Product.h"

Product::Product():name(NULL),prijs(0){

}
Product::~Product(){}
Product::Product(std::string name, long price):name(name),prijs(price){
}
Product::Product(Product& prod){
    this->name = prod.name;
    this->prijs = prod.prijs;
}
void Product::setName(std::string name){
    this->name = name;
}
void Product::setPrice(long price){
    this->prijs =price;
}
string Product::getName() const{
	return name;
}

long Product::getPrice() const{
	return prijs;
}
ostream& operator<< (ostream& out, const Product& product){
    out << "[";
	out << product.getName() << " ";
	out << product.getPrice();
	out << "]";
	return out;
}