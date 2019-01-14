#include "IndexElement.h"
#include "LinkedListElement.h"
IndexElement::IndexElement(string tag):count(0), hashtag(tag), tweets(NULL){

}
IndexElement::IndexElement(const IndexElement& copy){
    this->count = copy.count;
	this->hashtag = copy.hashtag;
	tweets = new LinkedListElement(*(copy.tweets));
}
IndexElement::~IndexElement(){
    LinkedListElement* tmp;
	while (tweets != NULL){
		tmp = tweets;
		tweets = tweets->removeFromList(tweets);
		delete tmp;
	}
}

string IndexElement::getHashTag() const{
    return this->hashtag;
}
void IndexElement::addTweet(Tweet tweet){
    bool present = false;
    LinkedListElement* tmp = this->tweets;
	while (tmp != NULL){
		Tweet tmpTweet = tmp->getTweet();
        if(tmpTweet.getID()==tweet.getID()){
            present = true;
            break;
        }
        if (tmp->getNext() == NULL){
			break;
		}
        tmp = tmp->getNext();
	}
    if (!present){
        LinkedListElement *el= new LinkedListElement(tweet);
        if (tmp != NULL){
            tmp->append(el);
        } else{
            this->tweets = el;
        }
        this->count++;
    }
}
int IndexElement::getNumTweets() const{
    return this->count;
}
Tweet IndexElement::getTweet(int i) const{
    LinkedListElement* tmp =  this->tweets;
    int j=0;
    while (tmp->getNext() != NULL && j < i){
		Tweet tmpTweet = tmp->getTweet();
        tmp = tmp->getNext();
        j++;
	}
    if ( j != i){
        string tags[1] = {""};
        Tweet tweet(0, "", 0, "", tags, 0);
        return tweet;
    }
    return tmp->getTweet();;
}