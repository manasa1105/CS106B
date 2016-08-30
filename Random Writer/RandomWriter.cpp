/*
 * File: RandomWriter.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the random writer problem
 * on Assignment #2.
 * [TODO: extend the documentation]
 */

#include <fstream>
#include <iostream>
#include <string>
#include "console.h"
#include "map.h"
#include "hashmap.h"
#include "random.h"
#include "strlib.h"
#include "vector.h"
#include "simpio.h"
#include "filelib.h"
using namespace std;

void MapSetup(HashMap<string, Vector<string> > &map, int order, ifstream &infile);
void GenerateRandomText(HashMap<string, Vector<string> > &map, int order);
const int RANDOM_TEXT_LENGTH = 2000;

/*
int main() {
    Vector<string> frequencyVec;
    Map<string, Vector<string> > map;
    ifstream infile;
    promptUserForFile(infile, "Please enter file name containing source text. ");
    int order = getInteger("What order of analysis (1 - 10): ");
    string keystr = "";
    while (true) {
        int ch = infile.get();
        if (ch == EOF) break;
            MapSetup(map, keystr, ch, order);
    }
    map.put(keystr, frequencyVec);
    infile.close();
    cout <<"Map Size: " << map.size() << endl;
    //cout <<"Map: " << map.toString() << endl;
//    GenerateRandomText(map, order);
    return 0;
}

void MapSetup(Map<string, Vector<string> > & map,
               string & keystr, char ch, int order) {
    Vector<string> frequencyVec;
    keystr += ch;

    if(keystr.length() > order) {
        string key = keystr.substr(0,order);
        string value = keystr.substr(order);
        if(map.containsKey(key)) {
            frequencyVec = map.get(key);
            frequencyVec.add(value);
            map.put(key, frequencyVec);
        }
        else{
            frequencyVec.add(value);
            map.put(key, frequencyVec);
        }
        keystr.erase(0,1);
    }
}

void GenerateRandomText(Map<string, Vector<string> > & map, int order) {
    //determining the seed(s) which occuered most frequently
    Vector<string> AllKeys = map.keys();
    Vector<string> keysOfMaxOccurrances;
    int maxOccurances = 0;
    for(int i=0; i<AllKeys.size(); i++) {
        Vector<string> valueOfithKey = map.get(AllKeys[i]);
        if(valueOfithKey.size() > maxOccurances) {
            maxOccurances = valueOfithKey.size();
        }
    }
    for(int i=0; i<AllKeys.size(); i++) {
        Vector<string> valueOfithKey = map.get(AllKeys[i]);
        if(valueOfithKey.size() == maxOccurances) {
            keysOfMaxOccurrances.add(AllKeys[i]);
        }
    }
    string seed = keysOfMaxOccurrances[randomInteger(0, keysOfMaxOccurrances.size()-1)];
    cout << "Initial random seed is: " << seed << endl;

    //generate the text
    string randomText = "";
    randomText+=seed;
    int wordCount = 2;
    while(wordCount < RANDOM_TEXT_LENGTH) {
        Vector<string> valueOfithKey = map.get(seed);
        if(valueOfithKey.size() == 0) break;
        randomText += valueOfithKey[randomInteger(0, valueOfithKey.size()-1)];
        seed = randomText.substr(randomText.length()-order);
        wordCount++;
    }
    cout << "final randomText: " << randomText << endl;
}
*/

int main() {
    Vector<string> frequencyVec;
    HashMap<string, Vector<string> > map;
    ifstream infile;
    promptUserForFile(infile, "Please enter file name containing source text. ");
    int order = getInteger("What order of analysis (1 - 10): ");
    MapSetup(map, order, infile);
    //cout <<"Map Size: " << map.size() << endl;
    //cout <<"Map: " << map.toString() << endl;
    GenerateRandomText(map, order);
    return 0;
}

void MapSetup(HashMap<string, Vector<string> > &map, int order, ifstream & infile) {
    string keystr = "";
    Vector<string> frequencyVec;
    while (true) {
        frequencyVec.clear();
        int ch = infile.get();
        if (ch == EOF) break;
        keystr += ch;
        if(keystr.length() > order) {
            string key = keystr.substr(0,order);
            string value = keystr.substr(order);
            if(map.containsKey(key)) {
                //frequencyVec = map.get(key);
                frequencyVec.add(value);
                map.put(key, frequencyVec);
            }
            else{
                frequencyVec.add(value);
                map.put(key, frequencyVec);
            }
            keystr.erase(0,1);
        }
    }
    map.put(keystr, frequencyVec);
    infile.close();
    //cout << "map size: " << map.size() << endl;
}

void GenerateRandomText(HashMap<string, Vector<string> > & map, int order) {
    //determining the seed(s) which occuered most frequently
    Vector<string> AllKeys = map.keys();
    Vector<string> keysOfMaxOccurrances;
    int maxOccurances = 0;
    for(int i=0; i<AllKeys.size(); i++) {
        Vector<string> valueOfithKey = map.get(AllKeys[i]);
        if(valueOfithKey.size() > maxOccurances) {
            maxOccurances = valueOfithKey.size();
        }
    }
    for(int i=0; i<AllKeys.size(); i++) {
        Vector<string> valueOfithKey = map.get(AllKeys[i]);
        if(valueOfithKey.size() == maxOccurances) {
            keysOfMaxOccurrances.add(AllKeys[i]);
        }
    }
    string seed = keysOfMaxOccurrances[randomInteger(0, keysOfMaxOccurrances.size()-1)];
    cout << "Initial random seed is: " << seed << endl;

    //generate the text
    string randomText = "";
    randomText+=seed;
    int wordCount = 2;
    while(wordCount < RANDOM_TEXT_LENGTH) {
        Vector<string> valueOfithKey = map.get(seed);
        if(valueOfithKey.size() == 0) break;
        randomText += valueOfithKey[randomInteger(0, valueOfithKey.size()-1)];
        seed = randomText.substr(randomText.length()-order);
        wordCount++;
    }
    cout << "final randomText: " << randomText << endl;
}
