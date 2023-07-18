#include <string>

using namespace std;

struct wordNode{
    string info;
    wordNode *prev;
    wordNode *link;
};

class wordLadder{
    private:
        int count;
        wordNode *first;
        wordNode *ladderEnd;
        bool isOneApart(const string, const string) const;
        void insertWord(const string newItem);
        wordNode * searchPtr(const string& searchItem) const;
    
    public:
        wordLadder();
        ~wordLadder();
        bool readDictionary(const char *);
        bool findLadder(const string, const string);
        bool validWord(const string) const;
        void printLadder() const;
        void resetLadder();
};