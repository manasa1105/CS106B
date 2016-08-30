// This header file doesn't do much, but it's good to demonstrate that it's
// possible to create and edit header files

#include <iostream>
#include "vector.h"
#include "queue.h"
#include "lexicon.h"
using namespace std;

void WordsOneCharAway(Lexicon & english, Vector<string> & oneLetterAwayVec, string word);
bool dequeueAndIterateNextHop(Vector<string> &dequeuedVector, Lexicon &usedWords, Vector<string> & oneLetterAwayVec,
                                 Queue<Vector<string> > & queue, Lexicon & english, string endWord);
