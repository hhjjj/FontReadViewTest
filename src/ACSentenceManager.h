//
//  ACSentenceManager.h
//  FontReadViewTest
//
//  Created by songhojun on 11/19/13.
//
//

#pragma once

#include "ofMain.h"
#include "ACSentence.h"

class ACSentenceManager {
    
    
public:
    ACSentenceManager();
    ~ACSentenceManager();

    void addSetence(string str);
    
    int getWordCount();
    int getSentenceCount();
    
    string getWord(int index);
    string getSentence(int index);
    
    vector<string> getAllSentences();
    vector<string> getAllWords();

private:
    vector<ACSentence> sentences;
    vector<string> wordsInAllSentences;
};
