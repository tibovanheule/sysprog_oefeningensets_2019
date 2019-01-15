//DECLARATIONS
#include "BinarySearchTreeTemplate.h"
#include "../memleak/debug_new.h"
#include <iostream>
using namespace std;

//CONSTRUCTOR
template<class T>
BinarySearchTreeTemplate<T>::BinarySearchTreeTemplate(){
	root = NULL;
}

//DESTRUCTOR
template<class T>
BinarySearchTreeTemplate<T>::~BinarySearchTreeTemplate(){
	TreeElementTemplate<T>* currentElement = root;
	TreeElementTemplate<T>* toDelete = NULL;

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
void BinarySearchTreeTemplate<T>::printTree() {
	if (root != NULL) {
		printTreeElement(0,0,root);
	}
}
template<class T>
T* BinarySearchTreeTemplate<T>::get(const long clientID) {

	TreeElementTemplate<T>* previousTreeElement = root;

	if (previousTreeElement == NULL) {
		return NULL;
	} else if (clientID == previousTreeElement->getValue()->getPatientID()) {
		return previousTreeElement->getValue()->getValue();
	} else if (clientID < previousTreeElement->getValue()->getPatientID()) {
		previousTreeElement = previousTreeElement->getLeftTree();
	} else if (clientID > previousTreeElement->getValue()->getPatientID()) {
		previousTreeElement = previousTreeElement->getRightTree();
	}
	return NULL;
}
template<class T>
void BinarySearchTreeTemplate<T>::put(long clientID, T* e)  {
	ElementTemplate<T>* currentElement = this->getElement(clientID);

	if (currentElement == NULL) {
		ElementTemplate<T>* element = new ElementTemplate<T>(clientID, e);
		TreeElementTemplate<T>* te = new TreeElementTemplate<T>(element);

		if (root == NULL) {
			root = te;
		} else {
			TreeElementTemplate<T>* parentTreeElement = getParentTreeElement(clientID);
			te->setParent(parentTreeElement);
			if (clientID < parentTreeElement->getValue()->getPatientID()) {
				parentTreeElement->setLeftTree(te);
			} else {
				parentTreeElement->setRightTree(te);
			}
			rotate(te);
		}
	} else {
		ElementTemplate<T>* newElement = new ElementTemplate<T>(clientID, e);
		while (currentElement->getNextElement() != NULL) {
			currentElement = currentElement->getNextElement();
		}
		currentElement->setNextElement(newElement);
	}

}
template<class T>
T* BinarySearchTreeTemplate<T>::remove(const long clientID) {
	TreeElementTemplate<T>* treeElement = getTreeElement(clientID);
	T* parameterValue = NULL;
	if (treeElement->getValue() != NULL) {
		parameterValue = treeElement->getValue()->getValue();
		ElementTemplate<T>* el = treeElement->getValue();
		treeElement->setValue(treeElement->getValue()->getNextElement());
		delete el;
		if (treeElement->getValue() == NULL) {
			removeTreeElement(treeElement);
		}
	} else {
		removeTreeElement(treeElement);
	}
	return parameterValue;
}

//PRIVATE METHODS
template<class T>
TreeElementTemplate<T>* BinarySearchTreeTemplate<T>::getParentTreeElement(const long clientID) {
	TreeElementTemplate<T>* previousTreeElement = root;

	while (previousTreeElement != NULL) {
		if (clientID < previousTreeElement->getValue()->getPatientID() && previousTreeElement->getLeftTree() != NULL) {
			previousTreeElement = previousTreeElement->getLeftTree();
		} else if (clientID < previousTreeElement->getValue()->getPatientID() && previousTreeElement->getLeftTree() == NULL) {
			return previousTreeElement;
		} else if (clientID > previousTreeElement->getValue()->getPatientID() && previousTreeElement->getRightTree() != NULL) {
			previousTreeElement = previousTreeElement->getRightTree();
		} else {
			return previousTreeElement;
		}
	}
	return NULL;
}
template<class T>
TreeElementTemplate<T>* BinarySearchTreeTemplate<T>::getTreeElement(const long clientID) {

	TreeElementTemplate<T>* previousTreeElement = root;

	while (previousTreeElement != NULL) {

		if (clientID == previousTreeElement->getValue()->getPatientID()) {
			return previousTreeElement;
		} else if (clientID < previousTreeElement->getValue()->getPatientID()) {
			previousTreeElement = previousTreeElement->getLeftTree();
		} else if (clientID > previousTreeElement->getValue()->getPatientID()) {
			previousTreeElement = previousTreeElement->getRightTree();
		}
	}
	return NULL;
}
template<class T>
ElementTemplate<T>* BinarySearchTreeTemplate<T>::getElement(const long clientID) {
	if (getTreeElement(clientID) != NULL) {
		return getTreeElement(clientID)->getValue();
	} else {
		return NULL;
	}
}
template<class T>
void BinarySearchTreeTemplate<T>::printTreeElement(int posX, int posY, TreeElementTemplate<T>* treeElement) {
	ElementTemplate<T>* element;
	int linkedListElementPosition = 0;

	cout << "(X,Y) == (" << posX << "," << posY << ")\n";
	if (treeElement->getValue() != NULL) {
		cout << "--> key(postition): " << treeElement->getValue()->getPatientID() << " (" << linkedListElementPosition << ")\n";
		cout << "--> Product: " << *(treeElement->getValue()->getValue()) << "\n";
		element = treeElement->getValue();
		while(element->getNextElement() != NULL) {
			linkedListElementPosition++;
			element = element->getNextElement();
			cout << "--> key(postition): " << element->getPatientID() << " (" << linkedListElementPosition << ")\n";
			cout << "--> Product: " << *(element->getValue()) << "\n";
		}
	}
	if (treeElement->getLeftTree() != NULL) {
		printTreeElement(posX+1, 0, treeElement->getLeftTree());
	}
	if (treeElement->getRightTree() != NULL) {
		printTreeElement(posX+1, 1, treeElement->getRightTree());
	}
}
template<class T>
void BinarySearchTreeTemplate<T>::rotate(TreeElementTemplate<T>* axis) {
	TreeElementTemplate<T>* parent = axis->getParent();
	TreeElementTemplate<T>* parentLeft = axis->getParent()->getLeftTree();
	TreeElementTemplate<T>* parentRight = axis->getParent()->getRightTree();
	TreeElementTemplate<T>* axisLeft = axis->getLeftTree();
	TreeElementTemplate<T>* axisRight = axis->getRightTree();
	TreeElementTemplate<T>* parentParent = parent->getParent();

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
void BinarySearchTreeTemplate<T>::removeTreeElement(TreeElementTemplate<T>* toBeRemoved) {
	TreeElementTemplate<T>* newRootElement = toBeRemoved;

	if (toBeRemoved->getRightTree() != NULL) {
		newRootElement = toBeRemoved->getRightTree();
		while (newRootElement->getLeftTree() != NULL) {
			newRootElement = newRootElement->getLeftTree();
		}

		while (newRootElement->getParent() != toBeRemoved) {
			TreeElementTemplate<T>* parent = newRootElement->getParent();
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

template class BinarySearchTreeTemplate<Product>;