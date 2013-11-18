#include "testApp.h"

#include "testApp.h"
string ohstr;
//--------------------------------------------------------------
void testApp::setup(){
    
	ofEnableAlphaBlending();
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	ofBackground(22, 22, 22, 255);
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
    ohstr ="";
    
}

void testApp::update(){
    //for each client lets send them a message letting them know what port they are connected on
	for(int i = 0; i < TCP.getLastID(); i++){
		if( !TCP.isClientConnected(i) )continue;
        
		//TCP.send(i, "hello client - you are connected on port - "+ofToString(TCP.getClientPort(i)) );
	}
    
}

//--------------------------------------------------------------
void testApp::draw(){
    
    string temp;
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
            ohstr = str;
//            if (ohstr.length()>3) {
            const char * c = ohstr.c_str();
                if(c[0] == '\n'){
                oneWords.clear();
                }
//            }
                else{
                    oneWords.push_back(str);
                }
            temp = str;
			storeText[i] = str;
		}
        
		//draw the info text and the received text bellow it
		ofDrawBitmapString(info, xPos, yPos);
		ofDrawBitmapString(storeText[i], 25, yPos + 20);
        
	}
    
//    ofRotateY(40);
    
	float lineHeight = ofMap(mouseY, 0, ofGetHeight(), 0, 2, true);
	unicodeFont.setLineHeight(lineHeight);
    
	float x = 30;
	float y = 40;
	
	string demoText = "This is my text in BitStream Vera font.";
	float fontSize = 28;
    
	// simple demo //////////////////////////////////////////////////////////
	
	drawPoint(x, y);		//draw insertion point
	
	ofSetColor(255);
	TIME_SAMPLE_START("simple draw");
	font.draw(
              demoText,	//text to draw
              fontSize,	//font size
              x,		//x coord where to draw
              y			//y coord where to draw
			  );
	TIME_SAMPLE_STOP("simple draw");
	
	// bounding box demo ///////////////////////////////////////////////////
	
	ofSetColor(255, 0, 0, 32);
	TIME_SAMPLE_START("bbox");
	ofRectangle bbox = font.getBBox( demoText, fontSize, x, y);
	TIME_SAMPLE_STOP("bbox");
	ofRect( bbox );
    
	
	// draw multiline text /////////////////////////////////////////////////
	
	y += 25 + bbox.height;
	drawPoint(x, y); //draw insertion point
	
	ofSetColor(255);
	string s = (string)"ofxFontStash can draw multiline text" + "\n" +
	"It also supports unicode strings: " + "\n" +
	"槊監しゅ祟䤂לרפובליקה. אם מיזם 銆銌 憉 圩芰敔 तकनिकल कार्यलय";
    
	TIME_SAMPLE_START("drawMultiLine");
	unicodeFont.drawMultiLine( s,  fontSize, x, y);
	TIME_SAMPLE_STOP("drawMultiLine");
	
	// multiline bbox /////////////////////////////////////////////////////
    
	ofSetColor(0, 255, 0, 32);
	TIME_SAMPLE_START("getBoundingBoxSize");
	ofRectangle bboxMultiline = unicodeFont.getBBox( s, fontSize, x, y);
	TIME_SAMPLE_STOP("getBoundingBoxSize");
	ofRect( bboxMultiline );
    
    
	// draw multiline column with a fixed width ///////////////////////////
    
	y += 25 + bboxMultiline.height;
	drawPoint(x, y); //draw insertion point
    
	ofSetColor(255);
//	s = "And you can wrap text to a certain (mouseX) width:\n\nLorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam.에라 이놈들아 잘먹고 잘살아라 ";
    
    s = msgLines[1];
	TIME_SAMPLE_START("drawMultiLineColumn");
//    if(temp != ""){
//        temp = ohstr;
//        ohstr="";
//    ofRectangle wbox = unicodeFont.getBBox(ohstr, fontSize, 0, 0);
//    ofSetColor(255);
//    unicodeFont.draw(ohstr, fontSize, 100, 100);

//    for (int i  = 0; i< oneWords.size(); i++) {
//        //ofRectangle column = unicodeFont.drawMultiLineColumn( oneWords[i],  fontSize, x, y, MAX( 200 ,mouseX - x) );
//        ofRectangle wbox = unicodeFont.getBBox(oneWords[i], fontSize, 0, 0);
//        ofSetColor(255);
//        unicodeFont.draw(oneWords[i], fontSize, 50*i, y);
//
//        TIME_SAMPLE_STOP("drawMultiLineColumn");
//        ofSetColor(255,32);
//        ofRect(50*i, y, 0.0, wbox.getWidth(), wbox.getHeight());
////        ofRect(wbox);
//        
//        // batch drawing, optimized for multiple drawing calls /////////////////
//        //y += wbox.height + 25;
//        drawPoint(50*i, y); //draw insertion point
//    }
	
//    }
    

    
	ofSetColor(255);
	TIME_SAMPLE_START("drawBatch");
	font.beginBatch();	//call "begin" before drawing fonts
	for (int i = 0; i < 5; i++){
		font.drawBatch("batch mode #" + ofToString(i+1), fontSize, x, y + i * fontSize );
	}
	font.endBatch();		//call "end" once finished
	TIME_SAMPLE_STOP("drawBatch");
    
	// rotating text ///////////////////////////////////////////////////////
	
	ofPushMatrix();
    ofTranslate(x + 400, y + 50);
    ofRotate( -200 * ofGetElapsedTimef(), 0, 0, 1);
    ofSetColor(ofRandom(255), ofRandom(255), ofRandom(255));
    font.draw("surrealismoooo!", fontSize, 0, 0 );
    drawPoint(0,0);
	ofPopMatrix();
    
	ofSetColor(255);
	TIME_SAMPLE_DRAW_BOTTOM_RIGHT();
    
    
    ofRectangle wbox = unicodeFont.getBBox(ohstr, fontSize, 0, 0);
    ofSetColor(255);
    unicodeFont.draw(ohstr, fontSize, 100, 100);

    mainOutputSyphonServer.publishScreen();

}

void testApp::drawPoint(float x, float y){
	ofSetColor(0, 255, 0, 128);	
	ofCircle(x, y, 2);
}



//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
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
