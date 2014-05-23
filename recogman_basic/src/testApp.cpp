#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    lock = true;
    
    ard.connect("/dev/cu.usbmodemfd121", 57600);
    //ard.connect("/dev/cu.usbmodemfa131", 57600);
    
    ofAddListener(ard.EInitialized, this, &testApp::setupArduino);
}

void testApp::setupArduino(const int &version){
    
    ofRemoveListener(ard.EInitialized, this, &testApp::setupArduino);
    
    ard.sendDigitalPinMode(3, ARD_INPUT);
    
    cout << "calibrating";
    for (int i = 0; i < 30; i++) {
        cout << ".";
        delay(1000);
    }
    cout << "done!";
    
}

//--------------------------------------------------------------
void testApp::update(){
    
    ard.update();
    
}

//--------------------------------------------------------------
void testApp::draw(){

    if (ard.getDigital(3) == ARD_HIGH) {
        if (lock) {
            cout << "motion detect! at ";
            cout << ofGetElapsedTimef() << endl;;
            lock = false;
            delay(50);
        }
        takeLowTime = true;
    }
    if (ard.getDigital(3) == ARD_LOW) {
        if (takeLowTime) {
            lowStart = ofGetElapsedTimef();
            takeLowTime = false;
        }
        if (!lock && ofGetElapsedTimef() - lowStart > 5) {
            cout << "motion ended at ";
            cout << ofGetElapsedTimef() << endl;
            delay(50);
            lock = true;
        }
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