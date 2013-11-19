#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    //glFrontFace(GL_CCW);
    //glFrontFace(GL_CW);
    ofEnableDepthTest();

    
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
    
    ofSetWindowTitle("ofxSyphon Example");
    
	mainOutputSyphonServer.setName("Screen Output");
    
	font.setup("Vera.ttf"); //load verdana font, set lineHeight to be 130%
	unicodeFont.setup("Arial Unicode.ttf"); //load verdana font, set lineHeight to be 130%
    
    
    // this is our buffer to stroe the text data
    ofBuffer buffer = ofBufferFromFile("message.txt");
    
    if(buffer.size()) {
        
        // we now keep grabbing the next line
        // until we reach the end of the file
        while(buffer.isLastLine() == false) {
            
            // move on to the next line
            string line = buffer.getNextLine();
            
            // copy the line to draw later
            // make sure its not a empty line
            if(line.empty() == false) {
                msgLines.push_back(line);
            }
            
            // print out the line
            cout << line << endl;
            
        }
        
    }
    
    //setup the server to listen on 11999
	TCP.setup(11999);
	//optionally set the delimiter to something else.  The delimter in the client and the server have to be the same, default being [/TCP]
	TCP.setMessageDelimiter("\t");
    curr_str ="";
    
    material.setDiffuseColor(ofFloatColor(255,0,0));
    //material.setEmissiveColor(ofFloatColor(255,0,0));
    icoSphere.setRadius(50);
    icoSphere.setMode( OF_PRIMITIVE_TRIANGLES );
    vector<ofMeshFace> triangles = icoSphere.getMesh().getUniqueFaces();
    icoSphere.getMesh().setFromTriangles(triangles,true);
    
    cam1ViewPort = ofRectangle(192, 64, 640, 640);
    
    cam1.setFov(60);
    cam1.setPosition(0, 0, 190);
    cam1Light.setPosition(0, 0, 190);
    cam1Light.enable();
    

    
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
    ofBackground(0);

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
    
    /* I commented this from ofMesh.cpp */
    
    //	// tig: flip face(=triangle) winding order, so that we are consistent with all other ofPrimitives.
    //	// i wish there was a more elegant way to do this, but anything happening before "split vertices"
    //	// makes things very, very complicated.
    //
    //	for (int i = 0; i < (int)faces.size(); i+=3) {
    //		std::swap(faces[i+1], faces[i+2]);
    //	}
    
    ofFill();
    ofSetColor(255,0,0);
    icoSphere.draw();

    ofSetColor(255, 255, 0);
    icoSphere.drawWireframe();
    icoSphere.drawNormals(10,true);

    //icoSphere.drawAxes(icoSphere.getRadius() + 30);
    
    
    
    ofSetColor(0, 0, 255);
    ofDrawBox(0, 0, 0, 20);

    ofSetColor(0, 255, 0);
    ofDrawBox(0, 50, 0, 50);

//    material.end();

    cam1.end();


    
    
    ofSetColor(255);
    ofDisableLighting();
    
   
    // OF 는 보통은 CW
    // 이 밑으로는 모두 CW winding
    glCullFace(GL_FRONT);
    
    // OF 에서는 glCullFace를 안쓸 수 있다.
    // 이땐 밑에 주석을 풀고 보통 처럼 그려라.
//    glDisable(GL_CULL_FACE);

    ofPushStyle();
    ofSetColor(255, 0, 0);
    ofNoFill();
//    ofFill();
    ofRect(cam1ViewPort);
    
    ofSetColor(255, 0, 255);
    ofFill();
    //    ofFill();
    ofRect(0,0,100,100);
    
    ofPopStyle();
    
    //for each connected client lets get the data being sent and lets print it to the screen
	for(unsigned int i = 0; i < (unsigned int)TCP.getLastID(); i++){
        
		if( !TCP.isClientConnected(i) )continue;
        
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
            
			storeText[i] = str;
		}
        
		//draw the info text and the received text bellow it
		ofDrawBitmapString(info, xPos, yPos);
		ofDrawBitmapString(storeText[i], 25, yPos + 20);
        
	}
    
//    ofRotateY(40);
    
    float fontSize = 28;
    
    ofRectangle wbox = unicodeFont.getBBox(testSentence.getSentence(), fontSize, 0, 0);
    ofSetColor(255);
    unicodeFont.draw(curr_str, fontSize, 100, 100);
    unicodeFont.draw(testSentence.getSentence(), fontSize, 100, 100+fontSize);
    unicodeFont.draw(ofToString(testSentence.getWordsCount()), fontSize, 40, 100+fontSize);

    
    for (int i = 0; i < testSentence.getWordsCount(); i++) {
        unicodeFont.draw(testSentence.getWords()[i], fontSize, 100, 100+fontSize*(i+2));
    }

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
