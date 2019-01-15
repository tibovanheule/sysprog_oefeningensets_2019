//DECLARATIONS
#include "BinarySearchTreeSTL.h"
#include "../memleak/debug_new.h"
#include <iostream>
using namespace std;

//CONSTRUCTOR
template <class T>
BinarySearchTreeSTL<T>::BinarySearchTreeSTL(){
	root = NULL;
}
//
//DESTRUCTOR
template <class T>
BinarySearchTreeSTL<T>::~BinarySearchTreeSTL(){
	TreeElementSTL<T>* currentElement = root;
	TreeElementSTL<T>* toDelete = NULL;

	if (root != NULL) {
		while (root->getLeftTree() != NULL || root->getRightTree() != NULL) {
			while (currentElement->getLeftTree() != NULL) {
				currentElement = currentElement->getLeftTree();
			}
			if (currentElement->getRightTree() != NULL) {
				currentElement = currentElement->getRightTree();
			} else {
				toDelete = currentElement;
				currentElement = currentElement->getParent();
				if (currentElement->getLeftTree() != NULL) {
					currentElement->setLeftTree(NULL);
				} else {
					currentElement->setRightTree(NULL);
				}
				delete toDelete;
			}
		}
	}
	delete root;
}

//PUBLIC METHODS
template<class T>
void BinarySearchTreeSTL<T>::printTree() {
	if (root != NULL) {
		printTreeElement(0,0,root);
	}
}

template<class T>
T* BinarySearchTreeSTL<T>::get(const long clientID) {

	TreeElementSTL<T>* previousTreeElement = root;

	if (previousTreeElement == NULL) {
		return NULL;
	} else if (clientID == previousTreeElement->getValueList().front()->getClientID()) {
		return previousTreeElement->getValueList().front()->getValue();
	} else if (clientID < previousTreeElement->getValueList().front()->getClientID()) {
		previousTreeElement = previousTreeElement->getLeftTree();
	} else if (clientID > previousTreeElement->getValueList().front()->getClientID()) {
		previousTreeElement = previousTreeElement->getRightTree();
	}
	return NULL;
}

template<class T>
void BinarySearchTreeSTL<T>::put(long clientID, T* e)  {
	ElementSTL<T>* currentElement = this->getElement(clientID);

	if (currentElement == NULL) {
		ElementSTL<T>* element = new ElementSTL<T>(clientID, e);
		TreeElementSTL<T>* te = new TreeElementSTL<T>(element);

		if (root == NULL) {
			root = te;
		} else {
			TreeElementSTL<T>* parentTreeElement = getParentTreeElement(clientID);
			te->setParent(parentTreeElement);
			if (clientID < parentTreeElement->getValueList().front()->getClientID()) {
				parentTreeElement->setLeftTree(te);
			} else {
				parentTreeElement->setRightTree(te);
			}
			rotate(te);
		}
	} else {
		TreeElementSTL<T>* treeElement = this->getTreeElement(clientID);
		ElementSTL<T>* newElement = new ElementSTL<T>(clientID, e);
		treeElement->put(newElement);
	}
}

template<class T>
list< ElementSTL<T>* > BinarySearchTreeSTL<T>::getAllElements(const long clientID)  {
	return getTreeElement(clientID)->getValueList();
}


template<class T>
T* BinarySearchTreeSTL<T>::remove(const long clientID) {
	TreeElementSTL<T>* treeElement = getTreeElement(clientID);
	T* parameterValue = NULL;
	if (treeElement->getValueList().size() != 0) {
		parameterValue = treeElement->getValueList().front()->getValue();
		ElementSTL<T>* element = treeElement->getValueList().front();
		treeElement->pop();
		delete element;
		if (treeElement->getValueList().size() == 0) {
			removeTreeElement(treeElement);
		}
	} else {
		removeTreeElement(treeElement);
	}
	return parameterValue;
}

//PRIVATE METHODS
template<class T>
TreeElementSTL<T>* BinarySearchTreeSTL<T>::getParentTreeElement(const long clientID) {
	TreeElementSTL<T>* previousTreeElement = root;

	while (previousTreeElement != NULL) {
		if (clientID < previousTreeElement->getValueList().front()->getClientID() && previousTreeElement->getLeftTree() != NULL) {
			previousTreeElement = previousTreeElement->getLeftTree();
		} else if (clientID < previousTreeElement->getValueList().front()->getClientID() && previousTreeElement->getLeftTree() == NULL) {
			return previousTreeElement;
		} else if (clientID > previousTreeElement->getValueList().front()->getClientID() && previousTreeElement->getRightTree() != NULL) {
			previousTreeElement = previousTreeElement->getRightTree();
		} else {
			return previousTreeElement;
		}
	}
	return NULL;
}

template<class T>
TreeElementSTL<T>* BinarySearchTreeSTL<T>::getTreeElement(const long clientID) {

	TreeElementSTL<T>* previousTreeElement = root;

	while (previousTreeElement != NULL) {

		if (clientID == previousTreeElement->getValueList().front()->getClientID()) {
			return previousTreeElement;
		} else if (clientID < previousTreeElement->getValueList().front()->getClientID()) {
			previousTreeElement = previousTreeElement->getLeftTree();
		} else if (clientID > previousTreeElement->getValueList().front()->getClientID()) {
			previousTreeElement = previousTreeElement->getRightTree();
		}
	}
	return NULL;
}

template<class T>
ElementSTL<T>* BinarySearchTreeSTL<T>::getElement(const long clientID) {
	if (getTreeElement(clientID) != NULL) {
		return getTreeElement(clientID)->getValueList().front();
	} else {
		return NULL;
	}
	return NULL;
}

template<class T>
void BinarySearchTreeSTL<T>::printTreeElement(int posX, int posY, TreeElementSTL<T>* tElement) {
	cout << "(X,Y) == (" << posX << "," << posY << ")\n";
	if (tElement->getValueList().size() != 0) {
		tElement->printTreeElement();
	}
	if (tElement->getLeftTree() != NULL) {
		printTreeElement(posX+1, 0, tElement->getLeftTree());
	}
	if (tElement->getRightTree() != NULL) {
		printTreeElement(posX+1, 1, tElement->getRightTree());
	}
}

template<class T>
void BinarySearchTreeSTL<T>::rotate(TreeElementSTL<T>* axis) {
	TreeElementSTL<T>* parent = axis->getParent();
	TreeElementSTL<T>* parentLeft = axis->getParent()->getLeftTree();
	TreeElementSTL<T>* parentRight = axis->getParent()->getRightTree();
	TreeElementSTL<T>* axisLeft = axis->getLeftTree();
	TreeElementSTL<T>* axisRight = axis->getRightTree();
	TreeElementSTL<T>* parentParent = parent->getParent();

	if (axis == parentLeft) {
		axis->setRightTree(parent);
		axis->setParent(parent->getParent());
		parent->setLeftTree(axisRight);
		parent->setParent(axis);
		if (axisRight != NULL) {
			axisRight->setParent(parent);
		}

		if (parentParent != NULL) {
			if (parentParent->getRightTree() == parent) {
				parentParent->setRightTree(axis);
			} else {
				parentParent->setLeftTree(axis);
			}
		}
	}
	else if (axis == parentRight) {
		axis->setLeftTree(parent);
		axis->setParent(parent->getParent());
		parent->setRightTree(axisLeft);
		parent->setParent(axis);
		if (axisLeft != NULL) {
			axisLeft->setParent(parent);
		}

		if (parentParent != NULL) {
			if (parentParent->getRightTree() == parent) {
				parentParent->setRightTree(axis);
			} else {
				parentParent->setLeftTree(axis);
			}
		}
	}

	if (parent != root) {
		rotate(axis);
	} else {
		root = axis;
	}

}

template<class T>
void BinarySearchTreeSTL<T>::removeTreeElement(TreeElementSTL<T>* toBeRemoved) {
	TreeElementSTL<T>* newRootElement = toBeRemoved;

	if (toBeRemoved->getRightTree() != NULL) {
		newRootElement = toBeRemoved->getRightTree();
		while (newRootElement->getLeftTree() != NULL) {
			newRootElement = newRootElement->getLeftTree();
		}

		while (newRootElement->getParent() != toBeRemoved) {
			TreeElementSTL<T>* parent = newRootElement->getParent();
			newRootElement->setRightTree(parent);
			newRootElement->setParent(parent->getParent());
			parent->setParent(newRootElement);
		}

		newRootElement->setLeftTree(toBeRemoved->getLeftTree());
		if (toBeRemoved->getLeftTree() != NULL) {
			toBeRemoved->getLeftTree()->setParent(newRootElement);
		}
		if (toBeRemoved != root) {
			newRootElement->setParent(toBeRemoved->getParent());
			newRootElement->getParent()->setLeftTree(newRootElement);
		} else {
			root = newRootElement;
		}
	}

	if (toBeRemoved->getRightTree() == NULL && toBeRemoved != root) {
		toBeRemoved->getParent()->setLeftTree(toBeRemoved->getLeftTree());
		toBeRemoved->getLeftTree()->setParent(toBeRemoved->getParent());
		if (toBeRemoved->getLeftTree() != NULL) {
			toBeRemoved->getLeftTree()->setParent(toBeRemoved->getParent());
		}
	}

	if (toBeRemoved == root) {
		root = toBeRemoved->getLeftTree();
	}

	toBeRemoved->setLeftTree(NULL);
	toBeRemoved->setRightTree(NULL);
	toBeRemoved->setParent(NULL);

	delete toBeRemoved;
}

template class BinarySearchTreeSTL<Product>;