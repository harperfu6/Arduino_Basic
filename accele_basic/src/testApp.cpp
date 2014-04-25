#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    
    ard.connect("/dev/cu.usbmodemfd121", 57600);
    //ard.connect("/dev/cu.usbmodemfa131", 57600);
    
    ofEnableDepthTest();
    ofSetLineWidth(3);
    
    ofAddListener(ard.EInitialized, this, &testApp::setupArduino);
}

void testApp::setupArduino(const int &version){
    
    ofRemoveListener(ard.EInitialized, this, &testApp::setupArduino);
    
    ard.sendAnalogPinReporting(0, ARD_ANALOG);
    ard.sendAnalogPinReporting(1, ARD_ANALOG);
    ard.sendAnalogPinReporting(2, ARD_ANALOG);
    
    ofAddListener(ard.EAnalogPinChanged, this, &testApp::analogPinChanged);
}

//--------------------------------------------------------------
void testApp::update(){
    
    ard.update();
    
}

//--------------------------------------------------------------
void testApp::draw(){
    
    cout << x << " " << y << " " << z << endl;
    
    n_x = ofMap(x, 306, 716, -180, 180, 1);
    n_y = ofMap(y, 306, 716, -180, 180, 1);
    n_z = ofMap(z, 306, 716, -180, 180, 1);
    
    if (abs(n_x - pre_x) > 5) {
        r_x = n_x;
    }
    if (abs(n_y - pre_y) > 5) {
        r_y = n_y;
    }
    if (abs(n_z - pre_z) > 5) {
        r_z = n_z;
    }

    cam.begin();
    
    ofFill();
    ofSetColor(150, 0, 20);
    ofRotateX(r_x);
    ofRotateY(r_y);
    ofRotateZ(r_z);
    //ofNoFill();
    ofDrawBox(0, 0, 0, 100, 100, 100);
    ofNoFill();
    ofSetColor(0, 0, 0);
    ofDrawBox(0, 0, 0, 101, 101, 101);
    cam.end();
    
    pre_x = n_x;
    pre_y = n_y;
    pre_z = n_z;
    
//    n_x = ofMap(x, 306, 716, -1, 1, 1);
//    n_y = ofMap(y, 306, 716, -1, 1, 1);
//    n_z = ofMap(z, 306, 716, -1, 1, 1);
//    
//    r_x = floor(asin(n_x) * 180 / PI);
//    r_y = floor(asin(n_y) * 180 / PI);
//    r_z = floor(asin(n_z) * 180 / PI);
//    
//    cam.begin();
//    
//    ofFill();
//    ofSetColor(150, 0, 20);
//    ofRotateX(r_x);
//    ofRotateY(r_y);
//    ofRotateZ(r_z);
//    //ofNoFill();
//    ofDrawBox(0, 0, 0, 100, 100, 100);
//    ofNoFill();
//    ofSetColor(0, 0, 0);
//    ofDrawBox(0, 0, 0, 101, 101, 101);
//    cam.end();
}

void testApp::analogPinChanged(const int &pinNum){
    
    switch (pinNum) {
        case 0:
            x = ard.getAnalog(pinNum);
            break;
        case 1:
            y = ard.getAnalog(pinNum);
            break;
        case 2:
            z = ard.getAnalog(pinNum);
            break;
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