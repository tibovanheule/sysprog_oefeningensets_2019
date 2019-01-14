#include <sstream>
#include "Tweet.h"
#include "../memleak/debug_new.h"
#include "time.h"
Tweet::Tweet(){

}
Tweet::Tweet(int id, string user, int timestamp, string message, string tags[], int count){
    this->hashtagcount = count;
    this->id = id;
    this->user =user;
    this->timestamp = timestamp;
    this->message = message;
    for (int i =0; i< count;i++){
        this->tags[i] = tags[i];
    }
}
Tweet::~Tweet(){

}
int Tweet::getID(){
    return this->id;
}
string Tweet::getTweeter(){
    return this->user;
}
string Tweet::getHashtag(int nr){
    if(nr > this->getNumHashtags()){
        exit(1);
    }
    return this->tags[nr];
}
int Tweet::getDate(){
    return this->timestamp;
}
string Tweet::getTweet(){
    return this->message;
}
int Tweet::getNumHashtags(){
    return this->hashtagcount;
}
string Tweet::getTextualDate() const{
    // dit is aangepast naar windows gebruik, het kan dus zijn dat dit terug aangepast moet worden naar linux
    // gebruik localtime_r voor linux
	stringstream ss;
	tm * ltm = localtime((const time_t *)&timestamp);
	ss << ltm->tm_mday << "/" << (ltm->tm_mon) << "/" << 1900 + ltm->tm_year << " " << ltm->tm_hour << ":" << ltm->tm_min << ":" << ltm->tm_sec;
	return ss.str();
}

ostream& operator<<(ostream& outputStream, const Tweet& tweet){
	outputStream << tweet.message << " (" << tweet.getTextualDate() << ", " << tweet.user << ")";
	return outputStream;
}