//
//  ACSentence.h
//  FontReadViewTest
//
//  Created by songhojun on 11/19/13.
//
//

#pragma once

#include "ofMain.h"
#include "ACUtil.h"

using namespace ACUtil;

class ACSentence {
    
public:
    ACSentence();
    ~ACSentence();
    
    string sentence;
    vector <string> words;

    void setSentence(string str);
    string getSentence();

    vector<string> getWords();
    int getWordsCount();

private:


};