//
//  ACSentenceManager.cpp
//  FontReadViewTest
//
//  Created by songhojun on 11/19/13.
//
//

#include "ACSentenceManager.h"

ACSentenceManager::ACSentenceManager(){
    
}

ACSentenceManager::~ACSentenceManager(){
    
}

void ACSentenceManager::addSetence(string str){
    ACSentence tmpSentence;
    tmpSentence.setSentence(str);
    sentences.push_back(tmpSentence);
}

int ACSentenceManager::getSentenceCount(){
    return sentences.size();
}

string ACSentenceManager::getSentence(int index){
    return sentences[index].getSentence();
}