#ifndef PRODUCT_H
#define PRODUCT_H
#include <string>
#include <ostream>
using namespace std;
class Product{
    private:
        string name;
        long prijs;
    public:
        virtual string getCategory() = 0;

        Product();
        Product(std::string name, long price);
        Product(Product& prod);
        virtual ~Product();

        void setName(std::string name);
        void setPrice(long price);

        string getName() const;
        long getPrice() const;
        friend ostream& operator<< (ostream& out,const Product& product);
};  
#endif