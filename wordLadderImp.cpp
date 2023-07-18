/*Description: Program finds a word ladder between two words using linked
        lists, stacks, and queues
*/

/*Algorithm:
1. Make the construtor and destructor
2. read in the words.dat file with readDictionary using a try/catch block
    and storing the words in the linked list, adding to the count
3. make findLadder by following the algorithm in the pdf
4. reset the ladder by traversing the list and setting the prev value to
    nullptr
5. check if the passed word is valid by traversing the list and comparing
    the passed string to every word
6. print the ladder by storing the wordNodes in a stack and 
    poping the stack
7. make isOneApart by comparing the amount of different characters in the
    passed strings, returning true if it is only one
8. Find the pointer of the specified word by traversing wordNode in 
    searchPtr*/

#include <iostream>
#include <fstream>
#include "wordLadder.h"
#include "linkedStack.h"
#include "linkedQueue.h"

using namespace std;

/*wordLadder: initializes class variables
parameters: none
return type: none*/
wordLadder::wordLadder(){
    count=0;
    first=nullptr;
    ladderEnd=nullptr;
}

/*~wordLadder: deallocates the linked list
parameters: none
return type: none*/
wordLadder::~wordLadder(){
    wordNode * toDelete=nullptr;

    while(first != nullptr){
        toDelete=first; //temp pointer points to head
        first=first->link; //head moves to next value
        delete toDelete; //temp pointer is deleted
    }
    ladderEnd=nullptr;
    toDelete=nullptr;
    count=0;
}

/*readDictionary: reads in the text file/dictionary from the command line
        and stores the strings in a linked list
parameters: const char *
return type: bool*/
bool wordLadder::readDictionary(const char * file){
    ifstream inFile;
    wordNode * current=nullptr;
    wordNode * last=nullptr;
    try{
        inFile.open(file);
        if(!inFile.is_open())
            throw false; //goes to catch if file doesn't open
        while(!inFile.eof()){
            current=new wordNode;
            inFile>>current->info; //reads in word to node
            current->prev=nullptr;
            current->link=nullptr;
            if(first == nullptr){ //if new list, first/last are set as
                first=current;   //the first created node
                last=current;
            }
            else{
                last->link=current; //sets current as link to prev node
                if(current->info != ""){ //last line in file is blank, so
                    last=current;       //this stores every line except last
                    count++;
                }
                else //last line is deleted because it is blank/not counted
                    delete current;
                
            }
        }
        last->link=nullptr; //b/c last is deleted, this sets the end of list
        inFile.close();
    }
    catch(bool error){
        return error; //exits if file doesn't open
    }
    return true;
}

/*findLadder: finds the word ladder between the two words
parameters: const string, const string
return type: bool*/
bool wordLadder::findLadder(const string start, const string end){
    wordNode * startPointer=nullptr;
    wordNode * dequeued=nullptr;
    wordNode * current=nullptr;
    linkedQueue <wordNode *> queue;
    linkedStack <wordNode *> stack;

    if(!validWord(start) || !validWord(end))
        return false;

    ladderEnd=searchPtr(end); //sets end pointer to second word
    startPointer=searchPtr(start); //finds address of first word
    startPointer->prev=startPointer; //first word points to itself
    queue.enqueue(startPointer);
    while(!queue.isEmptyQueue()){
        dequeued=queue.dequeue();
        current=first;
        while(current != nullptr){ //loops through whole dictonary
            if(isOneApart(current->info, dequeued->info)){
                if(current->info == end){ //checks if word is one from end
                    current->prev=dequeued;
                    return true;
                }
                if(current->prev == nullptr){
                    current->prev=dequeued; //links this word to prev word
                    queue.enqueue(current); //enqueues next word to check
                }
            }
            current=current->link;
        }
    }
    return false;
}

/*resetLadder: resets the prev values in the wordNode list
parameters: none
return type: void*/
void wordLadder::resetLadder(){
    wordNode * current=nullptr;

    current=first;
    while(current != nullptr){ //traverses list and sets to nullptr
        current->prev=nullptr;
        current=current->link;
    }
}

/*vaildWord: checks if the passed string is a valid word
parameter: const string
return type: bool*/
bool wordLadder::validWord(const string word) const{
    wordNode * current=nullptr;
    bool valWord=false;

    current=first;
    while(current != nullptr){ //searches dictionary
        if(current->info == word)
            valWord=true;
        current=current->link;
    }
    if(valWord) //returns true if vaild word
        return true;
    return false;
}

/*printLadder: prints the word ladder 
parameter: none
return type: void*/
void wordLadder::printLadder() const{
    wordNode * current=nullptr;
    linkedStack <string> stack;
    bool endList=false;
    
    
    current=ladderEnd;
    while(!endList){
        stack.push(current->info);
        if(current == current->prev) //ensures the last word is pushed
            endList=true;           //one time, but will exit loop after
        current=current->prev; //goes to prev word in word ladder
    }
    while(!stack.isStackEmpty()){
        cout<<stack.pop()<<endl; //prints stack
    }
}

/*isOneApart: checks whether the passed words are one char a part
parameter: const string, const string
return type: bool*/
bool wordLadder::isOneApart(const string word, const string compareWord) const{
    int differCount=0;

    for(int i=0; i < 5; i++){ //compares every char of the 5 letter words
        if(word[i] != compareWord[i])
            differCount++; //counts amount of differences
    }
    if(differCount == 1)
        return true;
    return false;
}

/*searchPtr: searches for the address in wordNode of the passed string
parameter: const string &
return type: wordNode * */
wordNode * wordLadder::searchPtr(const string & search) const{
    wordNode * current=nullptr;

    current=first;
    while(current != nullptr){
        if(current->info == search)
            return current; //if word matches, it returns the address
        current=current->link;
    }
    return nullptr;
}