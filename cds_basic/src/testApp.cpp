#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    
    ofBackground(255);
    ofSetLineWidth(3);
    
    ard.connect("/dev/cu.usbmodemfd121", 57600);
    //ard.connect("/dev/cu.usbmodemfa131", 57600);
    
    ofAddListener(ard.EInitialized, this, &testApp::setupArduino);
}

void testApp::setupArduino(const int &version){
    
    ofRemoveListener(ard.EInitialized, this, &testApp::setupArduino);
    
    ard.sendDigitalPinMode(9, ARD_PWM);
    
    ard.sendAnalogPinReporting(0, ARD_ANALOG);
    
    ofAddListener(ard.EAnalogPinChanged, this, &testApp::analogPinChanged);
}

//--------------------------------------------------------------
void testApp::update(){
    
    ard.update();
    
}

//--------------------------------------------------------------
void testApp::draw(){
    
    int n_value = ofMap(analog_value, 0, 1023, 0, 255);
    
    ard.sendPwm(9, n_value);//0~255!!(analogWrite)
    
    ofSetColor(0);
    ofLine(ofGetWidth()/4, ofGetHeight()*2/3, ofGetWidth()*3/4, ofGetHeight()*2/3);
    ofLine(ofGetWidth()/4, ofGetHeight()*2/3, ofGetWidth()/4, ofGetHeight()/3);
    
    int x, y;
    
    for (int i = 0; i < LENGTH; i++) {
        cout << buffer[i] << endl;
        
        x = ofGetWidth()/4 + (i * 10);
        y = ofGetHeight()*2/3 - buffer[i];
        
        data[i].x = x;
        data[i].y = y;
        
    }
    
    calc_avarage(data);
    calc_median(data);
    
    for (int i = 1; i < LENGTH; i++) {
        ofSetColor(0, 0, 255);
        ofLine(data[i-1].x, data[i-1].y, data[i].x, data[i].y);
        ofSetColor(255, 0, 0);
        ofLine(data[i-1].x, avarage[i-1], data[i].x, avarage[i]);
        ofSetColor(0, 255, 0);
        ofLine(data[i-1].x, median[i-1], data[i].x, median[i]);
        cout << median[i] << endl;
    }
    
}

void testApp::calc_avarage(ofVec2f *array){
    int sum, size;
    
    for (int i = 0; i < LENGTH; i++) {
        sum = 0;
        size = 0;
        for (int j = i-2; j <= i+2; j++) {
            if (j < 0 || j >= LENGTH) {
                continue;
            }
            sum += array[j].y;
            size++;
        }
        sum /= size;
        avarage[i] = sum;
    }
}

void testApp::calc_median(ofVec2f *array){
    int size;
    
    for (int i = 0; i < LENGTH; i++) {
        size = 0;
        for (int j = i-2; j <= i+2; j++) {
            if (j < 0 || j >= LENGTH) {
                continue;
            }
            s_median[size++] = array[j].y;
        }
        sort(s_median, s_median + size);
        median[i] = s_median[size / 2];
    }
}

void testApp::analogPinChanged(const int &pinNum){
    analog_value = ard.getAnalog(pinNum);//0~1023(analogRead)
    
    int n_value = ofMap(analog_value, 0, 1024, 0, 200, true);
    
    if (buffer.size() >= LENGTH) {
        buffer.pop_front();
    }
    buffer.push_back(n_value);
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