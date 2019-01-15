#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H
#include "Product.h"

class Element{
private:
	long clientID;
	Product* value;
	Element* nextElement;
public:
	Element(long clientID, Product* value): clientID(clientID), value(value) {nextElement = NULL;}; 
	~Element(){};
	long getClientID(){return clientID;};
	Product* getValue(){return value;};
	void setNextElement(Element* e){this->nextElement = e;};
	Element* getNextElement(){return this->nextElement;};
};

class TreeElement {
private:
	TreeElement* leftTree;
	TreeElement* rightTree;
	TreeElement* parent;
	Element* value;
public:
	TreeElement(Element* element){value = element; leftTree = NULL; rightTree = NULL; parent = NULL;};
	~TreeElement() {
		Element* nextElement;
		if (value != NULL) {
			while (value->getNextElement() != NULL) {
				nextElement = value;
				value =	nextElement->getNextElement();
				delete nextElement;
			}
			delete value;
		}
	};
	TreeElement* getLeftTree(){return this->leftTree;};
	TreeElement* getRightTree(){return this->rightTree;};
	TreeElement* getParent(){return this->parent;};
	Element* getValue(){return this->value;};

	void setLeftTree(TreeElement* leftTree){this->leftTree = leftTree;};
	void setRightTree(TreeElement* rightTree){this->rightTree = rightTree;};
	void setParent(TreeElement* parent){this->parent = parent;};
	void setValue(Element* value){this->value = value;};
};

class BinarySearchTree{
public:
	void put(long clientID, Product* value);
	Product* get(const long clientID);
	Product* remove(const long clientID);
	void printTree();
	BinarySearchTree();
	~BinarySearchTree();
private:
	TreeElement* root;
	Element* getElement(const long clientID);
	TreeElement* getParentTreeElement(const long clientID);
	TreeElement* getTreeElement(const long clientID);
	void printTreeElement(int posX, int posY, TreeElement* treeElement);
	void rotate(TreeElement* axis);
	void removeTreeElement(TreeElement* treeElement);
};

#endif