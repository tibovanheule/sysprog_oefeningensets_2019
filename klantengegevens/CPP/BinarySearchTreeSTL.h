#ifndef BINARYSEARCHTREESTL_H
#define BINARYSEARCHTREESTL_H
#include "Product.h"
#include <list>
#include <iostream>

template <class T>
class ElementSTL{
private:
	long clientID;
	T* value;
public:
	ElementSTL(long clientID, T* value): clientID(clientID), value(value) {}; 
	~ElementSTL(){};
	long getClientID(){return clientID;};
	T* getValue(){return value;};
};

template<class T>
class TreeElementSTL {
private:
	TreeElementSTL<T>* leftTree;
	TreeElementSTL<T>* rightTree;
	TreeElementSTL<T>* parent;
	std::list< ElementSTL<T>* > valueList;
public:
	TreeElementSTL<T>(){}; 
	TreeElementSTL<T>(std::list< ElementSTL<T>* > elementList){valueList = elementList; leftTree = NULL; rightTree = NULL; parent = NULL;};
	TreeElementSTL<T>(ElementSTL<T>* element) {valueList.push_front(element); leftTree = NULL; rightTree = NULL; parent = NULL;};
	~TreeElementSTL<T>() {
		typename std::list< ElementSTL<T>* >::iterator i = valueList.begin();
		while (i != valueList.end()) {
			delete (*i);
			i++;
		}
		valueList.clear();
	};
	TreeElementSTL<T>* getLeftTree(){return this->leftTree;};
	TreeElementSTL<T>* getRightTree(){return this->rightTree;};
	TreeElementSTL<T>* getParent(){return this->parent;};
	std::list< ElementSTL<T>* > getValueList(){return this->valueList;};

	void setLeftTree(TreeElementSTL<T>* leftTree){this->leftTree = leftTree;};
	void setRightTree(TreeElementSTL<T>* rightTree){this->rightTree = rightTree;};
	void setParent(TreeElementSTL<T>* parent){this->parent = parent;};
	void setValueList(std::list< ElementSTL<T>* > valueList){this->valueList = valueList;};

	void printTreeElement() {
		int linkedListElementPosition = 0;
		typename std::list< ElementSTL<T>* >::const_iterator i = valueList.begin();
		while (i != valueList.end()) {
			std::cout << "--> key(postition): " << (*i)->getClientID() << " (" << linkedListElementPosition << ")\n";
			std::cout << "--> Product: " << *((*i)->getValue()) << "\n";
			linkedListElementPosition++;
			i++;
		}
	};

	void put(ElementSTL<T>* element) {valueList.push_front(element);};
	void pop() {valueList.pop_front();};
};

template<class T>
class BinarySearchTreeSTL{
public:
	void put(long clientID, T* value);
	T* get(const long clientID);
	std::list< ElementSTL<T>* > getAllElements(const long clientID);
	T* remove(const long clientID);
	void printTree();
	BinarySearchTreeSTL();
	~BinarySearchTreeSTL();
private:
	TreeElementSTL<T>* root;
	ElementSTL<T>* getElement(const long clientID);
	TreeElementSTL<T>* getParentTreeElement(const long clientID);
	TreeElementSTL<T>* getTreeElement(const long clientID);
	void printTreeElement(int posX, int posY, TreeElementSTL<T>* treeElement);
	void rotate(TreeElementSTL<T>* axis);
	void removeTreeElement(TreeElementSTL<T>* treeElement);
};

#endif