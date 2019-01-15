//DECLARATIONS
#include "BinarySearchTree.h"
#include "../memleak/debug_new.h"
#include <iostream>
using namespace std;

BinarySearchTree::BinarySearchTree(){
	root = NULL;
}

//DESTRUCTOR
BinarySearchTree::~BinarySearchTree(){
	TreeElement* currentElement = root;
	TreeElement* toDelete = NULL;

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
void BinarySearchTree::printTree() {
	if (root != NULL) {
		printTreeElement(0,0,root);
	}
}
Product* BinarySearchTree::get(const long clientID) {
	TreeElement* previousTreeElement = root;

	if (previousTreeElement == NULL) {
		return NULL;
	}
	while (previousTreeElement!=NULL){
		if (clientID == previousTreeElement->getValue()->getClientID()) {
			return previousTreeElement->getValue()->getValue();
		} else if (clientID < previousTreeElement->getValue()->getClientID()) {
			previousTreeElement = previousTreeElement->getLeftTree();
		} else if (clientID > previousTreeElement->getValue()->getClientID()) {
			previousTreeElement = previousTreeElement->getRightTree();
		}
	}
	return NULL;
}

void BinarySearchTree::put(long clientID, Product* e)  {
	Element* currentElement = this->getElement(clientID);

	if (currentElement == NULL) {
		Element* element = new Element(clientID, e);
		TreeElement* te = new TreeElement(element);

		if (root == NULL) {
			root = te;
		} else {
			TreeElement* parentTreeElement = getParentTreeElement(clientID);
			te->setParent(parentTreeElement);
			if (clientID < parentTreeElement->getValue()->getClientID()) {
				parentTreeElement->setLeftTree(te);
			} else {
				parentTreeElement->setRightTree(te);
			}
			rotate(te);
		}
	} else {
		Element* newElement = new Element(clientID, e);
		while (currentElement->getNextElement() != NULL) {
			currentElement = currentElement->getNextElement();
		}
		currentElement->setNextElement(newElement);
	}
}

Product* BinarySearchTree::remove(const long clientID) {
	TreeElement* treeElement = getTreeElement(clientID);
	Product* Product = NULL;
	if (treeElement->getValue() != NULL) {
		Product = treeElement->getValue()->getValue();
		Element* el = treeElement->getValue();
		treeElement->setValue(treeElement->getValue()->getNextElement());
		delete el;
		if (treeElement->getValue() == NULL) {
			removeTreeElement(treeElement);
		}
	} else {
		removeTreeElement(treeElement);
	}
	return Product;
}

//PRIVATE METHODS
TreeElement* BinarySearchTree::getParentTreeElement(const long clientID) {
	TreeElement* previousTreeElement = root;

	while (previousTreeElement != NULL) {
		if (clientID < previousTreeElement->getValue()->getClientID() && previousTreeElement->getLeftTree() != NULL) {
			previousTreeElement = previousTreeElement->getLeftTree();
		} else if (clientID < previousTreeElement->getValue()->getClientID() && previousTreeElement->getLeftTree() == NULL) {
			return previousTreeElement;
		} else if (clientID > previousTreeElement->getValue()->getClientID() && previousTreeElement->getRightTree() != NULL) {
			previousTreeElement = previousTreeElement->getRightTree();
		} else {
			return previousTreeElement;
		}
	}
	return NULL;
}

TreeElement* BinarySearchTree::getTreeElement(const long clientID) {
	TreeElement* previousTreeElement = root;

	while (previousTreeElement != NULL) {

		if (clientID == previousTreeElement->getValue()->getClientID()) {
			return previousTreeElement;
		} else if (clientID < previousTreeElement->getValue()->getClientID()) {
			previousTreeElement = previousTreeElement->getLeftTree();
		} else if (clientID > previousTreeElement->getValue()->getClientID()) {
			previousTreeElement = previousTreeElement->getRightTree();
		}
	}
	return NULL;
}

Element* BinarySearchTree::getElement(const long clientID) {
	if (getTreeElement(clientID) != NULL) {
		return getTreeElement(clientID)->getValue();
	} else {
		return NULL;
	}
}

void BinarySearchTree::printTreeElement(int posX, int posY, TreeElement* treeElement) {
	Element* element;
	int linkedListElementPosition = 0;

	cout << "(X,Y) == (" << posX << "," << posY << ")\n";
	if (treeElement->getValue() != NULL) {
		cout << "--> key(postition): " << treeElement->getValue()->getClientID() << " (" << linkedListElementPosition << ")\n";
		cout << "--> Product: " << *(treeElement->getValue()->getValue()) << "\n";
		element = treeElement->getValue();
		while(element->getNextElement() != NULL) {
			linkedListElementPosition++;
			element = element->getNextElement();
			cout << "--> key(postition): " << element->getClientID() << " (" << linkedListElementPosition << ")\n";
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

void BinarySearchTree::rotate(TreeElement* axis) {
	TreeElement* parent = axis->getParent();
	TreeElement* parentLeft = axis->getParent()->getLeftTree();
	TreeElement* parentRight = axis->getParent()->getRightTree();
	TreeElement* axisLeft = axis->getLeftTree();
	TreeElement* axisRight = axis->getRightTree();
	TreeElement* parentParent = parent->getParent();

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

void BinarySearchTree::removeTreeElement(TreeElement* toBeRemoved) {
	TreeElement* newRootElement = toBeRemoved;

	if (toBeRemoved->getRightTree() != NULL) {
		newRootElement = toBeRemoved->getRightTree();
		cout << newRootElement->getValue()->getClientID() << "\n";
		while (newRootElement->getLeftTree() != NULL) {
			newRootElement = newRootElement->getLeftTree();
		}

		while (newRootElement->getParent() != toBeRemoved) {
			TreeElement* parent = newRootElement->getParent();
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
