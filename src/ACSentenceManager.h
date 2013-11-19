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
#include "ofxFontStash.h"

class ACSentenceManager {
    
    
public:
    ACSentenceManager();
    ~ACSentenceManager();

    void setFont(string fontPath, float fontSize);
    
    void addSetence(string str);
    
    int getWordCount();
    int getSentenceCount();
    
    string getWord(int index);
    string getSentence(int index);
    
    vector<string> getAllSentences();
    vector<string> getAllWords();
    
    void drawWordIn3D(int index, ofVec3f virterx , ofVec3f normal);
    void drawWordIn3D(string word, ofVec3f virterx , ofVec3f normal);


private:
    ofxFontStash wordFont;
    float wordFontSize;
    vector<ACSentence> sentences;
    vector<string> wordsInAllSentences;
};
