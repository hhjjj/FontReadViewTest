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
    int getSentenceCount();
    string getSentence(int index);

private:
    vector<ACSentence> sentences;

};
