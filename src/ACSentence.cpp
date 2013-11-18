//
//  ACSentence.cpp
//  FontReadViewTest
//
//  Created by songhojun on 11/19/13.
//
//

#include "ACSentence.h"

ACSentence::ACSentence(){
    sentence = "";
}

ACSentence::~ACSentence(){
    
}

void ACSentence::setSentence(string str){
    sentence = str;
    words.clear();
    // store trimed words 
    words = ofSplitString(ofxTrimString(str)," ");
    
}

string ACSentence::getSentence(){
    return sentence;
}


vector<string> ACSentence::getWords(){
    return words;
}

int ACSentence::getWordsCount(){
    return words.size();
}
