#include "LinkedListElement.h"

LinkedListElement::LinkedListElement(Tweet tweet):tweet(tweet),next(NULL){

}
LinkedListElement::LinkedListElement(const LinkedListElement& copy){
tweet = copy.tweet;
	if (copy.next != NULL){
		next = new LinkedListElement(*(copy.next));
	}
	else{
		next = NULL;
	}
}
Tweet LinkedListElement::getTweet() const{
    return this->tweet;
}
LinkedListElement* LinkedListElement::getNext() const{
    return this->next;
}
void LinkedListElement::append(LinkedListElement* node){
    //als men al een node hierchter hebben dan zal deze achter de nieuwe node komen
    node->next = this->next;
    this->next = node;

}
LinkedListElement* LinkedListElement::removeFromList(LinkedListElement* anchor){
    LinkedListElement* new_head = anchor;
	if (this == anchor){
		new_head = next;
		next = NULL;
	}
	else{
		LinkedListElement* prev = anchor;
		LinkedListElement* cur = anchor->next;
		while (cur != NULL && cur != this){
			prev = cur;
			cur = cur->next;
		}
		if (cur == this){
			prev->next = next;
			next = NULL;
		}
	}

	return new_head;
}