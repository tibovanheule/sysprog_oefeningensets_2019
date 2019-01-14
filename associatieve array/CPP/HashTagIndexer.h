#ifndef HashTagIndexer_H
#define HashTagIndexer_H
#include "Tweet.h"
#include "IndexElement.h"
#include "LinkedListElement.h"
#include <string>
#include <iostream>

class HashTagIndexer{
    public:
        HashTagIndexer();
        HashTagIndexer(const HashTagIndexer& copy);
        int getNumHashTags() const;
        void addTweet(Tweet tweet);
        ~HashTagIndexer();

        const HashTagIndexer operator+(const HashTagIndexer& secondOperand) const;
	    friend std::ostream& operator<<(std::ostream& outputStream, const HashTagIndexer& map);
	    IndexElement* operator[](std::string hashtag);
    private:
        int count;
        IndexElement** elements;
        int binarySearch(std::string hashtag);

};
#endif