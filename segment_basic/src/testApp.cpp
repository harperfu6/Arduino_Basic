#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    
    //ard.connect("/dev/cu.usbmodemfd121", 57600);
    ard.connect("/dev/cu.usbmodemfa131", 57600);
    
    ofAddListener(ard.EInitialized, this, &testApp::setupArduino);
}

void testApp::setupArduino(const int &version){
    
    ofRemoveListener(ard.EInitialized, this, &testApp::setupArduino);
    
    ard.sendDigitalPinMode(2, ARD_OUTPUT);
    ard.sendDigitalPinMode(3, ARD_OUTPUT);
    ard.sendDigitalPinMode(4, ARD_OUTPUT);
    ard.sendDigitalPinMode(5, ARD_OUTPUT);
    ard.sendDigitalPinMode(6, ARD_OUTPUT);
}

//--------------------------------------------------------------
void testApp::update(){
    
    ard.update();
}

//--------------------------------------------------------------
void testApp::draw(){
   
    ard.sendDigital(2, ARD_HIGH);
    ard.sendDigital(3, ARD_HIGH);
    //ard.sendDigital(4, ARD_HIGH);
    //ard.sendDigital(5, ARD_HIGH);
    //ard.sendDigital(6, ARD_HIGH);
    
    /*
    for (int i = 2; i < 2 + 5; i++) {
        ard.sendDigital(i, ARD_HIGH);
        delay(200);
        ard.sendDigital(i, ARD_LOW);
    }
     */
    

}

void testApp::delay(int msec){
    long delayTime = ofGetElapsedTimeMillis() + msec;
    
    while (delayTime >= ofGetElapsedTimeMillis()) {
    }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

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