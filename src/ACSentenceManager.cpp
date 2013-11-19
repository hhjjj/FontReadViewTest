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
    
    // store sentence
    sentences.push_back(tmpSentence);
    

    // store words
    vector<string> tmpWords = tmpSentence.getWords();
    for (int i = 0; i < tmpWords.size(); i++) {
        wordsInAllSentences.push_back(tmpWords[i]);
    }
}

int ACSentenceManager::getSentenceCount(){
    return sentences.size();
}

int ACSentenceManager::getWordCount(){
    return wordsInAllSentences.size();
}

string ACSentenceManager::getSentence(int index){
    return sentences[index].getSentence();
}

string ACSentenceManager::getWord(int index){
    return wordsInAllSentences[index];
}


vector<string> ACSentenceManager::getAllSentences(){
    vector<string> allSetences;
    
    for (int i = 0; i < sentences.size(); i++) {
        allSetences.push_back(sentences[i].getSentence());
    }
    return allSetences;
}

vector<string> ACSentenceManager::getAllWords(){
    return wordsInAllSentences;
}
