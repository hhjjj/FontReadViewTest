//
//  ACUtil.h
//  FontReadViewTest
//
//  Created by songhojun on 11/19/13.
//
//

#pragma once

#include "ofMain.h"

namespace ACUtil {
    
    // trim function from
    // https://github.com/companje/ofxExtras
    // trim trailing spaces
    string ofxTrimStringRight(string str);
    // trim trailing spaces
    string ofxTrimStringLeft(string str);
    string ofxTrimString(string str);
}