#ifndef TWEET_H
#define TWEET_H
#include <string>
using namespace std;

class Tweet{
    public:
        Tweet();
        Tweet(int id, string user, int timestamp, string message, string tags[], int count);
        ~Tweet();
        int getID();
        string getTweeter();
        string getHashtag(int nr);
        int getDate();
        string getTweet();
        int getNumHashtags();

        friend std::ostream& operator<<(std::ostream& outputStream, const Tweet& tweet);
    private:
        string getTextualDate() const;
        int id;
        string user;
        int timestamp;
        string message;
        int hashtagcount;
        string tags[5];

        
};
#endif