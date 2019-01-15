#ifndef FOOD_H
#define FOOD_H
#include "Product.h"
#include "Timestamp.h"
class Food : public Product{
    public:
        Food();
        ~Food();
        Food(string name, long price, Timestamp* ts);
        Food(Food& comp);

        virtual string getCategory()=0;
    private:
        Timestamp* before;

};
#endif