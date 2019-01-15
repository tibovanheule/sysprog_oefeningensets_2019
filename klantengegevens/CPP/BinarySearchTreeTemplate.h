#ifndef BINARYSEARCHTREETEMPLATE_H
#define BINARYSEARCHTREETEMPLATE_H
#include "Product.h"

template<class T>
class ElementTemplate{
private:
	long clientID;
	T* value;
	ElementTemplate<T>* nextElement;
public:
	ElementTemplate(long clientID, T* value): clientID(clientID), value(value) {nextElement = NULL;}; 
	~ElementTemplate(){};
	long getPatientID(){return clientID;};
	T* getValue(){return value;};
	void setNextElement(ElementTemplate* e){this->nextElement = e;};
	ElementTemplate<T>* getNextElement(){return this->nextElement;};
};

template<class T>
class TreeElementTemplate {
private:
	TreeElementTemplate<T>* leftTree;
	TreeElementTemplate<T>* rightTree;
	TreeElementTemplate<T>* parent;
	ElementTemplate<T>* value;
public:
	TreeElementTemplate<T>(ElementTemplate<T>* element){value = element; leftTree = NULL; rightTree = NULL; parent = NULL;};
	~TreeElementTemplate<T>() {
		ElementTemplate<T>* nextElement;
		if (value != NULL) {
			while (value->getNextElement() != NULL) {
				nextElement = value;
				value =	nextElement->getNextElement();
				delete nextElement;
			}
			delete value;
		}
	};
	TreeElementTemplate<T>* getLeftTree(){return this->leftTree;};
	TreeElementTemplate<T>* getRightTree(){return this->rightTree;};
	TreeElementTemplate<T>* getParent(){return this->parent;};
	ElementTemplate<T>* getValue(){return this->value;};

	void setLeftTree(TreeElementTemplate<T>* leftTree){this->leftTree = leftTree;};
	void setRightTree(TreeElementTemplate<T>* rightTree){this->rightTree = rightTree;};
	void setParent(TreeElementTemplate<T>* parent){this->parent = parent;};
	void setValue(ElementTemplate<T>* value){this->value = value;};
};

template<class T>
class BinarySearchTreeTemplate{
public:
	void put(long clientID, T* value);
	T* get(const long clientID);
	T* remove(const long clientID);
	void printTree();
	BinarySearchTreeTemplate();
	~BinarySearchTreeTemplate();
private:
	TreeElementTemplate<T>* root;
	ElementTemplate<T>* getElement(const long clientID);
	TreeElementTemplate<T>* getParentTreeElement(const long clientID);
	TreeElementTemplate<T>* getTreeElement(const long clientID);
	void printTreeElement(int posX, int posY, TreeElementTemplate<T>* treeElement);
	void rotate(TreeElementTemplate<T>* axis);
	void removeTreeElement(TreeElementTemplate<T>* treeElement);
};

#endif