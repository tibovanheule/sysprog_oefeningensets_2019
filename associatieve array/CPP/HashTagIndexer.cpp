#include "HashTagIndexer.h"

HashTagIndexer::HashTagIndexer():count(0),elements(NULL){

}
HashTagIndexer::HashTagIndexer(const HashTagIndexer& copy){
    this->count = copy.count;
	elements = new IndexElement*[this->count];
	for (int i = 0; i < count; i++){
		elements[i] = new IndexElement(*(copy.elements[i]));
	}
}
int HashTagIndexer::getNumHashTags() const{
    return this->count;
}

HashTagIndexer::~HashTagIndexer(){
    if (this->elements != NULL){
		for (int i = 0; i < this->count; i++){
			delete this->elements[i];
		}
		delete[] elements;
		elements = NULL;
	}
}
void HashTagIndexer::addTweet(Tweet tweet)
{
	int tagcount = tweet.getNumHashtags();
	for (int i = 0; i < tagcount; i++){
		string hashtag = tweet.getHashtag(i);
		int location = this->binarySearch(hashtag);
		if (location < this->count && this->elements[location]->getHashTag() == hashtag){
			elements[location]->addTweet(tweet);
		}
		else{
			IndexElement** new_elements = new IndexElement*[count + 1];
			
			for (int i = 0; i < location; i++){
				new_elements[i] = elements[i];
			}
			new_elements[location] = new IndexElement(hashtag);
			new_elements[location]->addTweet(tweet);

			for (int i = location; i < count; i++){
				new_elements[i + 1] = elements[i];
			}
			delete[] elements;
			elements = new_elements;
			count++;
		}
	}
}

const HashTagIndexer HashTagIndexer::operator+ (const HashTagIndexer& secondOperand) const
{
	HashTagIndexer newIndexer(secondOperand);
	for (int i = 0; i < count; i++){
		int numtweets = elements[i]->getNumTweets();
		for (int j = 0; j < numtweets; j++){
			Tweet tweet = elements[i]->getTweet(j);
			newIndexer.addTweet(tweet);
		}
	}
	return newIndexer;
}

std::ostream& operator<<(std::ostream& outputStream, const HashTagIndexer& map)
{
	for (int i = 0; i < map.count; i++){
		IndexElement* element = map.elements[i];
		outputStream << "===" << endl;
		outputStream << element->getHashTag() << endl;
		outputStream << "===" << endl;
		for (int j = 0; j < element->getNumTweets(); j++){
			Tweet tweet = element->getTweet(j);
			outputStream << " * " << tweet << endl;
		}
		outputStream << endl;
	}
	return outputStream;
}

int HashTagIndexer::binarySearch(std::string hashtag)
{
	int lower = 0;
	int upper = count;
	while (upper >= lower && lower < count){
		int mid = lower + ((upper - lower) / 2);
		if (elements[mid]->getHashTag() == hashtag){
			return mid;
		}
		else if (elements[mid]->getHashTag() < hashtag){
			lower = mid + 1;
		}
		else{
			upper = mid - 1;
		}
	}

	return lower;
}

IndexElement* HashTagIndexer::operator[](std::string hashtag)
{
	int index = binarySearch(hashtag);
	if (index < count && elements[index]->getHashTag() == hashtag){
		return elements[index];
	}
	else{
		return NULL;
	}
}