//
//  ACUtil.cpp
//  FontReadViewTest
//
//  Created by songhojun on 11/19/13.
//
//

#include "ACUtil.h"

namespace ACUtil {

    // trim trailing spaces
    string ofxTrimStringRight(string str) {
        size_t endpos = str.find_last_not_of(" \t\r\n");
        return (string::npos != endpos) ? str.substr( 0, endpos+1) : str;
    }

    // trim trailing spaces
    string ofxTrimStringLeft(string str) {
        size_t startpos = str.find_first_not_of(" \t\r\n");
        return (string::npos != startpos) ? str.substr(startpos) : str;
    }

    string ofxTrimString(string str) {
        return ofxTrimStringLeft(ofxTrimStringRight(str));;
    }
}