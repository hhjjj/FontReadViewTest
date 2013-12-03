#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    //glFrontFace(GL_CCW);
    //glFrontFace(GL_CW);
//    ofEnableDepthTest();
    // for archiving in Mac App
    ofSetDataPathRoot("../Resources/data/");
    
    if( XML.loadFile("mySettings.xml") ){
        // will return false when xml file is empty
		cout<< "mySettings.xml loaded!" << endl;
	}else{
		cout<< "unable to load mySettings.xml check data/ folder" << endl;
	}
    
    
	ofEnableAlphaBlending();
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	ofBackground(22, 22, 22, 255);
    
    receiver.setup(PORT);
    
    ofSetWindowTitle("ANTICLIMAX");
    
	mainOutputSyphonServer.setName("12345");
    
	font.setup("Vera.ttf"); //load verdana font, set lineHeight to be 130%
	unicodeFont.setup("Arial Unicode.ttf"); //load verdana font, set lineHeight to be 130%
    
    trueFont.loadFont("Vera.ttf", 100);
    // this is our buffer to stroe the text data
//    ofBuffer buffer = ofBufferFromFile("message.txt");
//    
//    if(buffer.size()) {
//        
//        // we now keep grabbing the next line
//        // until we reach the end of the file
//        while(buffer.isLastLine() == false) {
//            
//            // move on to the next line
//            string line = buffer.getNextLine();
//            
//            // copy the line to draw later
//            // make sure its not a empty line
//            if(line.empty() == false) {
//                msgLines.push_back(line);
//            }
//            
//            // print out the line
//            cout << line << endl;
//            
//        }
//        
//    }
    
    //setup the server to listen on 11999
	TCP.setup(12345);
	//optionally set the delimiter to something else.  The delimter in the client and the server have to be the same, default being [/TCP]
	TCP.setMessageDelimiter("\t");
    curr_str ="";
    
    material.setDiffuseColor(ofFloatColor(255,0,0));
    //material.setEmissiveColor(ofFloatColor(255,0,0));
    icoSphere.setRadius(50);
    icoSphere.setMode( OF_PRIMITIVE_TRIANGLES );
//    vector<ofMeshFace> triangles = icoSphere.getMesh().getUniqueFaces();
//    icoSphere.getMesh().setFromTriangles(triangles,true);

    cam1ViewPort = ofRectangle(192, 64, 640, 640);
    
    cam1.setFov(60);
    cam1.setPosition(0, 0, 190);
    cam1Light.setPosition(0, 0, 190);
    cam1.setDistance(100);
    cam1Light.enable();
    

    connectionColor = ofColor(255,0,0);
    bConnectFill = false;
}

void testApp::update(){
    //for each client lets send them a message letting them know what port they are connected on
	for(int i = 0; i < TCP.getLastID(); i++){
		if( !TCP.isClientConnected(i) )continue;
        
		//TCP.send(i, "hello client - you are connected on port - "+ofToString(TCP.getClientPort(i)) );
	}
    
    
    while(receiver.hasWaitingMessages()){
		// get the next message
		ofxOscMessage m;
		receiver.getNextMessage(&m);
        
		// check for mouse moved message
		if(m.getAddress() == "/mouse/position"){
			// both the arguments are int32's
			mouseX = m.getArgAsInt32(0);
			mouseY = m.getArgAsInt32(1);
		}
		// check for mouse button message
		else if(m.getAddress() == "/mouse/button"){
			// the single argument is a string
			mouseButtonState = m.getArgAsString(0);
            cout << "button" << endl;
		}
		else{
			// unrecognized message: display on the bottom of the screen
			string msg_string;
			msg_string = m.getAddress();
			msg_string += ": ";
			for(int i = 0; i < m.getNumArgs(); i++){
				// get the argument type
				msg_string += m.getArgTypeName(i);
				msg_string += ":";
				// display the argument - make sure we get the right type
				if(m.getArgType(i) == OFXOSC_TYPE_INT32){
					msg_string += ofToString(m.getArgAsInt32(i));
				}
				else if(m.getArgType(i) == OFXOSC_TYPE_FLOAT){
					msg_string += ofToString(m.getArgAsFloat(i));
				}
				else if(m.getArgType(i) == OFXOSC_TYPE_STRING){
					msg_string += m.getArgAsString(i);
				}
				else{
					msg_string += "unknown";
				}
			}
			// add to the list of strings to display
//			msg_strings[current_msg_string] = msg_string;
//			timers[current_msg_string] = ofGetElapsedTimef() + 5.0f;
//			current_msg_string = (current_msg_string + 1) % NUM_MSG_STRINGS;
//			// clear the next line
//			msg_strings[current_msg_string] = "";
		}
        
	}

    
}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(0,255);
    
    
    /*
    
    
    
    ofEnableDepthTest();

    // 카메라에서 보이는 쪽만 그려라 ( winding 방향이 제대로 되어 있어야 한다.)
    glEnable(GL_CULL_FACE);

    ofEnableLighting();
    
    cam1.begin(cam1ViewPort);

    //OF는 카메라 안에서는 CCW
    
//    material.begin();



    
    //glCullFace(GL_FRONT); // for testing
    //glCullFace(GL_BACK); // for testing

    //draw the Back
//    glCullFace(GL_FRONT);
    
    
    //draw the front
    glCullFace(GL_BACK);
    
    // I commented this from ofMesh.cpp 
    
    //	// tig: flip face(=triangle) winding order, so that we are consistent with all other ofPrimitives.
    //	// i wish there was a more elegant way to do this, but anything happening before "split vertices"
    //	// makes things very, very complicated.
    //
    //	for (int i = 0; i < (int)faces.size(); i+=3) {
    //		std::swap(faces[i+1], faces[i+2]);
    //	}
    
    ofFill();
    ofSetColor(255,0,0);
    //icoSphere.draw();

    ofSetColor(255, 255, 0);
    icoSphere.drawWireframe();
    // draw face normals
//    icoSphere.drawNormals(10,true);
    // draw normal
    ofSetColor(255, 255, 0);
    icoSphere.drawNormals(10);

//    icoSphere.drawAxes(icoSphere.getRadius() + 30);
    
//    ofSetColor(0, 0, 255);
//    ofDrawBox(0, 0, 0, 20);
    
    
    
    
    
    // drawing some rectangles
    ofSetColor(255,0,0);
    for (int i = 0; i < icoSphere.getMesh().getVertices().size(); i++) {
        
        ofMatrix4x4 m;
        m.makeRotationMatrix(ofVec3f(0,0,1), icoSphere.getMesh().getNormal(i));
        
        ofPushMatrix();
        ofTranslate(ofPoint(icoSphere.getMesh().getVertex(i).x,icoSphere.getMesh().getVertex(i).y,icoSphere.getMesh().getVertex(i).z));
        ofMultMatrix(m);
        ofRect(-3, -3, 6, 6);
        ofPopMatrix();
        
    }

    
    
    
    // ofxStash Font draw with  glCullFace(GL_FRONT) and glScalef(1,-1,1);
    
    glCullFace(GL_FRONT);

    ofRectangle boundingBox = unicodeFont.getBBox("홀리", 200, 0, 0);
    ofSetColor(255,0,0);
    ofPushMatrix();
    ofScale(0.05, 0.05);
    ofTranslate(-boundingBox.getWidth()/2.0, -boundingBox.getHeight()/2.0);
    glScalef(1,-1,1);
    unicodeFont.draw("홀리", 200, 0, 0);
//    trueFont.drawString("Hello", 0, 0);
    ofPopMatrix();

    ofSetColor(255,255,0);
    for (int i = 0; i < icoSphere.getMesh().getVertices().size(); i++) {
        
    
    
        ofRectangle ddBox = unicodeFont.getBBox("ㅋ", 200, 0, 0);
        ofMatrix4x4 m;
        m.makeRotationMatrix(ofVec3f(0,0,1), icoSphere.getMesh().getNormal(i));

        ofPushMatrix();
        ofTranslate(ofPoint(icoSphere.getMesh().getVertex(i).x*1.01,icoSphere.getMesh().getVertex(i).y*1.01,icoSphere.getMesh().getVertex(i).z*1.01));
        ofMultMatrix(m);

        
        ofScale(0.05, 0.05);
            
        ofTranslate(-ddBox.getWidth()/2.0, -ddBox.getHeight()/2.0);
        glScalef(1,-1,1);
        unicodeFont.draw("ㅋ", 200, 0, 0);
        ofPopMatrix();

    }
    
    
    
    //glDisable(GL_CULL_FACE);
   
    
    
//    ofSetColor(0, 255, 0);
//    ofDrawBox(0, 50, 0, 50);

//    material.end();

    cam1.end();

    
    ofSetColor(255);
    
    //let's create noraml OF Drawing Environment from below:
    ofDisableLighting();
    ofDisableDepthTest();

    // OF 는 보통은 CW
    // 이 밑으로는 모두 CW winding
    // OF 에서는 glCullFace를 안쓸 수 있다.
    // 이땐 밑에 주석을 풀고 보통 처럼 그려라.
    glDisable(GL_CULL_FACE);
    
    
   
*/

    ofPushStyle();
    ofSetColor(connectionColor);
    if (bConnectFill) {
        ofFill();
    }
    else{
    ofNoFill();
//    ofFill();
    
    }
    ofRect(cam1ViewPort);
//    ofSetColor(255, 0, 255);
//    ofFill();
//    //    ofFill();
//    ofRect(0,0,100,100);
    
    ofPopStyle();
    
    //for each connected client lets get the data being sent and lets print it to the screen
	for(unsigned int i = 0; i < (unsigned int)TCP.getLastID(); i++){
        
        
        if( !TCP.isClientConnected(i) ) {
            bConnectFill = false;
        }
        
		if( !TCP.isClientConnected(i) ) {
            continue;
        }
        bConnectFill = true;
        
		//give each client its own color
		ofSetColor(255 - i*30, 255 - i * 20, 100 + i*40);
        
		//calculate where to draw the text
		int xPos = 15;
		int yPos = 80 + (12 * i * 4);
        
		//get the ip and port of the client
		string port = ofToString( TCP.getClientPort(i) );
		string ip   = TCP.getClientIP(i);
		string info = "client "+ofToString(i)+" -connected from "+ip+" on port: "+port;
        
        
		//if we don't have a string allocated yet
		//lets create one
		if(i >= storeText.size() ){
			storeText.push_back( string() );
		}
        
		//we only want to update the text we have recieved there is data
		string str = TCP.receive(i);
        
        // check userID
        size_t startpos1 = str.find_first_not_of("/user2/");
        if (string::npos != startpos1) {
            // for user1
            str = str.substr(startpos1);
            
            if(str.length() > 0){
                
                // 스트링 비교 되네!!!
                if (str.compare("야") ==0) {
                    cout<<"야 이다!"<<endl;
                }
                else if (str.compare("ㅇㅇ") ==0) {
                    cout<<"ㅇㅇ 이다!"<<endl;
                }
                
                
                
                
                const char *c = str.c_str();
                
                
                
                // Cocoa 에서 TCP 로 데이터가 오면 순서가 뒤집히는거 같다.
                // 그래서 제일 처음에 '\n'이 오는걸 체크해야한다.
                if(c[0] == '\n'){
                    cout<< "sentence set with return key" << endl;
                    testSentence.setSentence(curr_str);
                    sentences.addSetence(curr_str);
                    curr_str="";
                    
                    for (int i = 0; i < sentences.getSentenceCount(); i++) {
                        cout << sentences.getSentence(i) << endl;
                    }
                    
                    for (int i = 0; i < sentences.getWordCount(); i++) {
                        cout << sentences.getWord(i) << endl;
                    }
                }
                else{
                    
                    curr_str = str;
                }
            }
            
//            size_t startpos2 = str.find_first_not_of("/user2/");
//            if (string::npos != startpos2) {
//                // for user2
//                str = str.substr(startpos2);
//            }
            
			storeText[i] = str;
		}
        
		//draw the info text and the received text bellow it
        

//		ofDrawBitmapString(info, xPos, yPos);
//		ofDrawBitmapString(storeText[i], 25, yPos + 20);
        
	}
    
//    ofRotateY(40);
        ofSetColor(255,255,255,255);
    float fontSize = 80;
    ofFill();
    //unicodeFont.draw("Hello", fontSize, 40, 40);

    ofRectangle wbox = unicodeFont.getBBox(testSentence.getSentence(), fontSize, 0, 0);

//    unicodeFont.draw(curr_str, fontSize, 100, 100);
//    unicodeFont.draw(testSentence.getSentence(), fontSize, 100, 100+fontSize);
    //unicodeFont.draw(ofToString(testSentence.getWordsCount()), fontSize, 40, 100+fontSize);

    for (int i = 0; i < testSentence.getWordsCount(); i++) {
        ofRectangle wbBox = unicodeFont.getBBox(testSentence.getWords()[i], fontSize, 0, 0);
        
        ofSetColor(255, 255, 0);
        unicodeFont.draw(testSentence.getWords()[i], fontSize, cam1ViewPort.x+ cam1ViewPort.width /2 -  wbBox.width/2, cam1ViewPort.y +fontSize*(i+1));
        //        ofSetColor(255, 0, 0, 200);
        //        ofFill();
        //        ofRect(ofRectangle(cam1ViewPort.x+ cam1ViewPort.width /2 -  wbBox.width/2, cam1ViewPort.y + fontSize*(i+1), wbBox.width, wbBox.height));
    }


    ofSetColor(255, 255,255);
    unicodeFont.drawMultiLineColumn(curr_str, fontSize, cam1ViewPort.x, cam1ViewPort.y + fontSize, cam1ViewPort.width);
    
    
    
    
    
    mainOutputSyphonServer.publishScreen();

}

void testApp::drawPoint(float x, float y){
	ofSetColor(0, 255, 0, 128);	
	ofCircle(x, y, 2);
}



//--------------------------------------------------------------
void testApp::keyPressed(int key){
    //no data gets saved unless you hit the s key
    if(key == 's'){
        XML.saveFile("mySettings.xml");
        cout<< "settings saved to xml!" << endl;
    }
//    if(key == '1') {
//        ofEnableDepthTest();
//    } else if(key == '2') {
//        ofDisableDepthTest();
//    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){
    
}
