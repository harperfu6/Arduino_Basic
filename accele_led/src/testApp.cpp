#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    
    ard.connect("/dev/cu.usbmodemfd121", 57600);
    //ard.connect("/dev/cu.usbmodemfa131", 57600);
    
    for (int i = 0; i < bufferLength; i++) {
        buffer[i] = 511;
    }
    index = 0;
    
    ofAddListener(ard.EInitialized, this, &testApp::setupArduino);
}

void testApp::setupArduino(const int &version){
    
    ofRemoveListener(ard.EInitialized, this, &testApp::setupArduino);
    
    ard.sendDigitalPinMode(9, ARD_PWM);
//    ard.sendDigitalPinMode(9, ARD_OUTPUT);
    
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

    cout << x - sum << endl;
    if (abs(x - sum) > THRESHOLD) {
        cout << "aaa" << endl;
        intensity = 1024;
    }
    else{
        intensity *= 0.9;
    }
        ard.sendPwm(9, intensity);
    
}

void testApp::analogPinChanged(const int &pinNum){
    
    //cout << x << endl;
    
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
    
    sum = 0;
    buffer[index] = x;
    index = (index + 1) % bufferLength;
    
    for (int i = 0; i < bufferLength; i++) {
        sum += buffer[i];
    }
    
    sum /= bufferLength;
    
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