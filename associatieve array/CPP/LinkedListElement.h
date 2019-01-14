#ifndef LinkedListElement_H
#define LinkedListElement_H
#include "Tweet.h"

class LinkedListElement{
    private:
        Tweet tweet;
        LinkedListElement* next;
    public:
        LinkedListElement(Tweet tweet);
        LinkedListElement(const LinkedListElement& copy);
        Tweet getTweet() const;
        LinkedListElement* getNext() const;
        void append(LinkedListElement* node);
        LinkedListElement* removeFromList(LinkedListElement* anchor);
};
#endif
