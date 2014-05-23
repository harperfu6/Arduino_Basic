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
    
    ard.sendDigitalPinMode(12, ARD_OUTPUT);
}

//--------------------------------------------------------------
void testApp::update(){

    ard.update();
}

//--------------------------------------------------------------
void testApp::draw(){
    
    melody(523, BEAT);
    melody(494, BEAT);
    melody(440, BEAT);
    melody(392, BEAT);
    melody(349, BEAT);
    melody(330, BEAT);
    melody(294, BEAT);
    melody(262, BEAT);
    delay(3000);

}

void testApp::melody(int freq, int duration){
    
    int tones;
    
    tones = 1000000L / (2 * freq);
    
    for (long i = 0; i < duration * 1000L; i += tones * 2) {
        ard.sendDigital(12, ARD_HIGH);
        delayMicro(tones);
        ard.sendDigital(12, ARD_LOW);
        delayMicro(tones);
    }
}

void testApp::delay(int msec){
    long delayTime = ofGetElapsedTimeMillis() + msec;
    
    while (delayTime >= ofGetElapsedTimeMillis()) {
    }
}

void testApp::delayMicro(int msec){
    
    long delayTime = ofGetElapsedTimeMicros() + msec;
    
    while (delayTime >= ofGetElapsedTimeMicros()) {
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