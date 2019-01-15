#include <stdio.h>

#include "Product.h"
#include "Computer.h"
#include "Food.h"
#include "Fruit.h"
#include "Vegetable.h"
#include "BinarySearchTree.h"
#include "BinarySearchTreeTemplate.h"
#include "BinarySearchTreeSTL.h"
#include "../memleak/debug_new.h"


int main(){
	//BinarySearchTree* bst = new BinarySearchTree();
	//BinarySearchTreeTemplate<Product>* bst = new BinarySearchTreeTemplate<Product>();
	BinarySearchTreeSTL<Product>* bst = new BinarySearchTreeSTL<Product>();

	Timestamp* ts = new Timestamp(10, 12, 2014);

	Product* p = new Computer("Dell",1500);
	Product* p2 = new Computer("Acer",1240);
	Product* p3 = new Fruit("Banana", 1, ts);


	bst->put(1,p);
	bst->put(20, p);
	bst->put(5, p2);
	bst->put(5, p);
	bst->put(15, p3);

	bst->printTree();

	delete bst;
	delete p;
	delete p2;
	delete p3;

	//Wait for user to press ENTER before closing
	getchar();
}
