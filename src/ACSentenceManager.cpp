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

void ACSentenceManager::setFont(string fontPath, float fontSize){
    wordFontSize = fontSize;
    wordFont.setup(fontPath);
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

// This draw only works in ofCamera
// make sure to enclose the function with glCullFace(GL_FRONT);

void ACSentenceManager::drawWordIn3D(int index, ofVec3f virterx , ofVec3f normal){
    string word = wordsInAllSentences[index];
    ofRectangle boundingBox = wordFont.getBBox(word, wordFontSize, 0, 0);
    

    
    ofPushMatrix();
    ofTranslate(ofPoint(virterx.x,virterx.y,virterx.z));
    
    // Rotate properly based on Normal vector
    // degree to rotate along X axis
    ofRotateX(atan2(normal.y, sqrt(normal.x*normal.x + normal.z*normal.z)));
    // degree to rotate along Y axis
    ofRotateY(ofRadToDeg(atan2(normal.y, normal.x)));
    ofScale(0.05, 0.05);
    ofTranslate(-boundingBox.getWidth()/2.0, -boundingBox.getHeight()/2.0);
    glScalef(1,-1,1);
    wordFont.draw(word, wordFontSize, 0, 0);
    ofPopMatrix();
}


