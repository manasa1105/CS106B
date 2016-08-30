#include <iostream>
#include "hello.h"
#include "console.h"
#include "simpio.h"
#include "queue.h"
#include "lexicon.h"
#include "vector.h"
#include "strlib.h"
using namespace std;


int main() {
    Lexicon english("EnglishWords.txt");
    Queue<Vector<string> > queue;
    Vector<string> ladder;
    Vector<string> oneLetterAwayVec;
    Vector<string> dequeuedVector;
    Lexicon usedWords;
    usedWords.clear();
    string startWord = getLine("Enter the start word");
    startWord = toLowerCase(startWord);
    usedWords.add(startWord);
    string endWord = getLine("Enter the end word");
    endWord = toLowerCase(endWord);
    ladder.add(startWord);
    queue.enqueue(ladder);
    while(!queue.isEmpty()) {
        if(!dequeueAndIterateNextHop(dequeuedVector, usedWords,
                                 oneLetterAwayVec, queue, english, endWord)) {
            break;
        }
    }
    if(queue.isEmpty()) {
        cout << "No ladder found." << endl;
    }
    else {
        cout << "final ladder" << dequeuedVector.toString() << endl;
    }
    return 0;
}

void WordsOneCharAway(Lexicon & english, Vector<string> & oneLetterAwayVec, string word) {
    oneLetterAwayVec.clear();
    for(int i=0; i<(int)word.size(); i++) {
        string wordCopy = word;
        char ch = tolower(wordCopy[i]);
        for(char j='a'; j<='z'; j++) {
            if(ch!=j) {
                wordCopy[i]=j;
                if(english.contains(wordCopy)) {
                    oneLetterAwayVec.add(wordCopy);
                }
            }
        }
    }
}

bool dequeueAndIterateNextHop(Vector<string> & dequeuedVector,
                              Lexicon & usedWords, Vector<string> & oneLetterAwayVec,
                                 Queue<Vector<string> > & queue, Lexicon & english, string endWord) {
    //cout << "queue contains: " << queue.toString() << endl;
    dequeuedVector = queue.dequeue();
    //cout << "dequeued vector " << dequeuedVector.toString() << endl;
    if (dequeuedVector[dequeuedVector.size()-1]!=endWord) {
        WordsOneCharAway(english, oneLetterAwayVec,
                         dequeuedVector[dequeuedVector.size()-1]);
        //cout << "oneLetterAwayVec " << oneLetterAwayVec.toString() << endl;
        for(int i=0; i<(int)oneLetterAwayVec.size(); i++) {
            if(!usedWords.contains(oneLetterAwayVec[i])) {
                Vector<string> ladderCopy = dequeuedVector;
                ladderCopy.add(oneLetterAwayVec[i]);
                usedWords.add(oneLetterAwayVec[i]);
                queue.enqueue(ladderCopy);
            }
        }
        return true;
    }
    return false;
}
