#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    
    ard.connect("/dev/cu.usbmodemfd121", 57600);
    //ard.connect("/dev/cu.usbmodemfa131", 57600);
    
    ofAddListener(ard.EInitialized, this, &testApp::setupArduino);
}

void testApp::setupArduino(const int &version){
    
    ofRemoveListener(ard.EInitialized, this, &testApp::setupArduino);
    
    ard.sendDigitalPinMode(9, ARD_OUTPUT);
    ard.sendDigitalPinMode(10, ARD_OUTPUT);
    
}

//--------------------------------------------------------------
void testApp::update(){
    
    ard.update();
    
}

//--------------------------------------------------------------
void testApp::draw(){
    
    forward(255);
    cout << "Forward" << endl;
    delay(500);
    
    despin(true);
    cout << "Despin(with brake)" << endl;
    delay(1000);
    
    reverse(255);
    cout << "Reverse" << endl;
    delay(500);
    
    despin(false);
    cout << "Despin(without brake)" << endl;
    delay(1000);
    
}

void testApp::forward(int value){
    ard.sendDigital(9, ARD_HIGH);
    ard.sendDigital(10, ARD_LOW);
    
}

void testApp::reverse(int value){
    ard.sendDigital(9, ARD_LOW);
    ard.sendDigital(10, ARD_HIGH);
    
}

void testApp::despin(bool useBrake = true){
    if (useBrake) {
        ard.sendDigital(9, ARD_HIGH);
        ard.sendDigital(10, ARD_HIGH);
    }
    else{
        ard.sendDigital(9, ARD_LOW);
        ard.sendDigital(10, ARD_LOW);
    }
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