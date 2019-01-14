#ifndef INDEXELEMENT_H
#define INDEXELEMENT_H
#define TWEETSIZE  10;
#include <string>
#include "Tweet.h"
#include "LinkedListElement.h"

class IndexElement{
    private:
        int count;
        string hashtag;
        LinkedListElement* tweets;
    public:
        IndexElement(string tag);
        IndexElement(const IndexElement& copy);
        string getHashTag() const;
        void addTweet(Tweet tweet);
        int getNumTweets() const;
        Tweet getTweet(int i) const;
        ~IndexElement();
};

#endif