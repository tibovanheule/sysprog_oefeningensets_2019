#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "../memleak/debug_new.h"
#include "Tweet.h"
#include "IndexElement.h"
#include "HashTagIndexer.h"


/*TODO: Include the header file of all your classes here*/

using namespace std;

HashTagIndexer readFromFile(string file)
{
	HashTagIndexer indexer;
	ifstream infile(file.c_str());
	string line;
	if (infile.is_open()) {
		while (getline(infile, line)) {
			istringstream iss(line);
			string split[5];
			for (int i = 0; i < 5; i++) {
				getline(iss, split[i], ';');
			}

			int tagcount = 0;
			string tags[5];
			istringstream tss(split[4]);
			while (tagcount <= 5 && getline(tss, tags[tagcount], ',')) {
				tagcount++;
			}

			Tweet tweet(atoi(split[0].c_str()), split[1], atoi(split[2].c_str()), split[3], tags, tagcount);
			indexer.addTweet(tweet);
		}
		return indexer;
	}
	else {
		cerr << "Error opening file\n";
		exit(-1);
	}
}

/* Prints the result of a test to the console */
void printTestResult(string testname, bool testresult)
{
	cout << "Performed test '" << testname << "': ";
	if (testresult){
		cout << "Succeeded!" << endl;
	}
	else{
		cout << "FAILED!" << endl;
	}
}

/* BEGIN OF TEST FUNCTIONS TO IMPLEMENT */
bool getTweeterTweetTest()
{
	string tags[3] = { "tag1", "tag2", "tag3" };
	Tweet tweet(1, "Tweeter", 100, "Tweet", tags, 3);
	if (tweet.getTweeter() != "Tweeter")
		return false;
	return true;
}

bool getHashtagTweetTest()
{
	string tags[3] = { "tag1", "tag2", "tag3" };
	Tweet tweet(1, "Tweeter", 100, "Tweet", tags, 3);
	if (tweet.getHashtag(1) != "tag2")
		return false;
	return true;
}

bool addTweetIndexElementTest()
{
	IndexElement el("hashtag");
	string tags[3] = { "tag1", "tag2", "tag3" };
	Tweet tweet(1, "Tweeter", 100, "Tweet", tags, 3);
	el.addTweet(tweet);
	if (el.getNumTweets() != 1)
		return false;
	return true;
}

bool getTweetIndexElementTest()
{
	IndexElement el("hashtag");
	string tags[3] = { "tag1", "tag2", "tag3" };
	Tweet tweet(1, "Tweeter", 100, "Tweet", tags, 3);
	el.addTweet(tweet);
	Tweet test = el.getTweet(0);
	if (tweet.getID() != 1)
		return false;
	return true;
}

bool addTweetHashTagIndexerTest()
{
	HashTagIndexer indexer;
	if (indexer.getNumHashTags() != 0){
		return false;
	}
	string tags[5] = { "tag1", "tag2", "tag3", "tag4", "tag5" };
	for (int i = 1; i <= 5; i++){
		Tweet tw(i, "Tweeter", 100, "Tweet", tags, i);
		indexer.addTweet(tw);
		if (indexer.getNumHashTags() != i){
			return false;
		}
		indexer.addTweet(tw);
		if (indexer.getNumHashTags() != i){
			return false;
		}
	}
	return true;
}
/* END OF TEST FUNCTIONS TO IMPLEMENT */

/* BEGIN OF GIVEN TEST FUNCTIONS */
bool getIDTweetTest()
{
	string tags[3] = { "tag1", "tag2", "tag3" };
	Tweet tweet(1, "Tweeter", 100, "Tweet", tags, 3);
	if (tweet.getID() != 1)
		return false;
	return true;
}

bool getDateTweetTest()
{
	string tags[3] = { "tag1", "tag2", "tag3" };
	Tweet tweet(1, "Tweeter", 100, "Tweet", tags, 3);
	if (tweet.getDate() != 100)
		return false;
	return true;
}

bool getTweetTweetTest()
{
	string tags[3] = { "tag1", "tag2", "tag3" };
	Tweet tweet(1, "Tweeter", 100, "Tweet", tags, 3);
	if (tweet.getTweet() != "Tweet")
		return false;
	return true;
}

bool getNumHashtagsTweetTest()
{
	string tags[3] = { "tag1", "tag2", "tag3" };
	Tweet tweet(1, "Tweeter", 100, "Tweet", tags, 3);
	if (tweet.getNumHashtags() != 3)
		return false;
	return true;
}

bool getHashTagIndexElementTest()
{
	IndexElement el("hashtag");
	if (el.getHashTag() != "hashtag")
		return false;
	return true;
}

bool getNumTweetsIndexElementTest()
{
	IndexElement el("hashtag");
	string tags[3] = { "tag1", "tag2", "tag3" };
	if (el.getNumTweets() != 0)
		return false;
	for (int i = 1; i <= 30; i++){
		Tweet tw(i, "Tweeter", 100, "Tweet", tags, 3);
		el.addTweet(tw);
		if (el.getNumTweets() != i){
			return false;
		}
		el.addTweet(tw);
		if (el.getNumTweets() != i){
			return false;
		}
	}
	return true;
}
/* END OF GIVEN TEST FUNCTIONS */

/* Executes all individual tests and prints the result of each test: fail or success */
void runTests()
{
	printTestResult("getIDTweetTest", getIDTweetTest());
	printTestResult("getTweeterTweetTest", getTweeterTweetTest());
	printTestResult("getDateTweetTest", getDateTweetTest());
	printTestResult("getTweetTweetTest", getTweetTweetTest());
	printTestResult("getNumHashtagsTweetTest", getNumHashtagsTweetTest());
	printTestResult("getHashtagTweetTest", getHashtagTweetTest());
	printTestResult("getHashTagIndexElementTest", getHashTagIndexElementTest());
	printTestResult("addTweetIndexElementTest", addTweetIndexElementTest());
	printTestResult("getNumTweetsIndexElementTest", getNumTweetsIndexElementTest());
	printTestResult("getTweetIndexElementTest", getTweetIndexElementTest());
	printTestResult("addTweetHashTagIndexerTest", addTweetHashTagIndexerTest());
}

/* Performs a final test, reading the input from file, merging the indexers and printing them. */
void executeReadFile()
{
	//Creates a HashTagIndexer from the lorem ipsum tweet file
	HashTagIndexer ind1 = readFromFile("tweets_lorem.txt");
	//Creates a HashTagIndexer from the pangram tweet file
	HashTagIndexer ind2 = readFromFile("tweets_pangram.txt");
	//Merges the two HashTagIndexers using the +-operator
	HashTagIndexer ind3 = ind1 + ind2;
	//Prints the total HashTagIndexer to the console using the output operator
	cout << ind3 << endl << endl;
	IndexElement* el = ind3["#SOI"];
	cout << "Tweets with hashtag #SOI (" << el->getNumTweets() << " tweets):" << endl;
	if (el != NULL){
		for (int i = 0; i < el->getNumTweets(); i++){
			cout << " -" << el->getTweet(i) << endl;
		}
	}
}

void execute(){
	cout << "Tests will be performed: " << endl;
	runTests();
	cout << "------" << endl;
	cout << "All tests have been executed." << endl;
	cout << "Press a key to start the input from file...";
	getchar();
	cout << endl << endl;
	executeReadFile();
}

int main(int argc, const char* argv[]){
	execute();
	return 0;
}
