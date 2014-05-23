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
    
    ard.sendDigitalPinMode(2, ARD_INPUT);
    
    ard.sendAnalogPinReporting(0, ARD_ANALOG);
    ard.sendAnalogPinReporting(1, ARD_ANALOG);
    ard.sendAnalogPinReporting(2, ARD_ANALOG);
    
}

//--------------------------------------------------------------
void testApp::update(){
    
    ard.update();
    
}

//--------------------------------------------------------------
void testApp::draw(){
    
    unsigned long start = ofGetElapsedTimeMillis();
    
    bool isButtonPressed = (ard.getDigital(2) == ARD_HIGH);
    
    if (!wasButtonPressed && isButtonPressed) {
        cout << "aaa\n";
        waitForAction();
        beginCapture();
    }
    
    if (isCapturing) {
        int x = ard.getAnalog(0);
        int y = ard.getAnalog(1);
        int z = ard.getAnalog(2);
        processSample(x, y, z);
    }
    
    wasButtonPressed = isButtonPressed;
    unsigned long elapsedTime = ofGetElapsedTimeMillis() - start;
    
    if (elapsedTime < samplingInterval) {
        delay(samplingInterval - elapsedTime);
    }

}

void testApp::beginCapture(){
    
    sampleCount = 0;
    isCapturing = true;
    
}

void testApp::endCapture(){
    
    if (!isCapturing) {
        return;
    }
    
    isCapturing = false;
    cout << "data" << endl;
    for (int i = 0; i < sampleDataLength; i++) {
        printf("{%d, ", sampleData[i][0]);
        printf("%d, ", sampleData[i][1]);
        printf("%d},\n", sampleData[i][2]);
    }
    cout << endl;
    
}

void testApp::processSample(int x, int y, int z){
    
    const int samplesToAverage = 4;
    static int count = 0;
    static int totalX, totalY, totalZ = 0;
    
    totalX += x;
    totalY += y;
    totalZ += z;
    
    count++;
    
    if (count == samplesToAverage) {
        sampleData[sampleCount][0] = quantizeAccelData(totalX / samplesToAverage);
        sampleData[sampleCount][1] = quantizeAccelData(totalY / samplesToAverage);
        sampleData[sampleCount][2] = quantizeAccelData(totalZ / samplesToAverage);
        
        sampleCount++;
        
        totalX = totalY = totalZ = 0;
        count = 0;
    }
    
    if(sampleCount > (sampleDataLength - 1)){
        endCapture();
        
        int gesture = detectGesture();
        
        cout << "Gesture: " << gesture << endl;
    }
}

char testApp::quantizeAccelData(int accData){
    
    const int plus2G = 919;
    const int plus1G = 715;
    const int zeroG = 511;
    const int minus1G = 307;
    const int minus2G = 103;
    
    char quantize = 0;
    
    if (plus2G < accData) {
        quantize = 16;
    }
    else if (plus1G < accData && accData <= plus2G){
        quantize = ofMap(accData, plus1G + 1, plus2G, 11, 15);
    }
    else if (zeroG < accData && accData <= plus1G){
        quantize = ofMap(accData, zeroG + 1, plus1G, 1, 10);
    }
    else if (minus1G <= accData && accData < zeroG){
        quantize = ofMap(accData, minus1G, zeroG - 1, -10, -1);
    }
    else if (minus2G <= accData && accData < minus1G){
        quantize = ofMap(accData, minus2G, minus1G - 1, -15, -11);
    }
    else if (accData < minus2G){
        quantize = -16;
    }
    
    return quantize;
    
}

int testApp::detectGesture(){
    
    int gesture = notFound;
    
    unsigned int minimumDistance = 1000;
    
    for (int i = 0; i < numTemplates; i++) {
        unsigned int distance = getDTMDistance(i);
        
        if (distance < minimumDistance) {
            gesture = i;
            minimumDistance = distance;
        }
    }
    return gesture;
}

unsigned int testApp::getDTMDistance(int templateIndex){
    
    static unsigned int DTW[sampleDataLength + 1][sampleDataLength + 1];
    
    cout << "bbb" << endl;
    
    for (int i = 1; i <= sampleDataLength; i++) {
        DTW[i][0] = 65535;
    }
    for (int i = 1; i <= sampleDataLength; i++) {
        DTW[0][i] = 65535;
    }
    DTW[0][0] = 0;
    
    unsigned int d0, d1 = 0;
    char sx, sy, sz, tx, ty, tz = 0;
    
    for (int i = 1, is = 0; i <= sampleDataLength; i++, is++) {
        for (int j = 1, it = 0; j <= sampleDataLength; j++, it++) {
            tx = templateData[templateIndex][it][0];
            ty = templateData[templateIndex][it][1];
            tz = templateData[templateIndex][it][2];
            
            sx = sampleData[is][0];
            sy = sampleData[is][1];
            sz = sampleData[is][2];
            
            d0 = sqrt(sqrt(sx - tx) + sqrt(sy - ty) + sqrt(sz - tz));
            
            d1 = MIN(DTW[i - 1][j], MIN(DTW[i][j - 1], DTW[i - 1][j - 1]));
            
            DTW[i][j] = d0 + d1;
        }
    }
    return DTW[sampleDataLength][sampleDataLength];
}

void testApp::waitForAction(){
    
    char initX = quantizeAccelData(ard.getAnalog(0));
    char initY = quantizeAccelData(ard.getAnalog(1));
    char initZ = quantizeAccelData(ard.getAnalog(2));
    
    int count = 200;
    
    //約200ms，アクションがあるかどうかを待つ
    while (--count > 0) {
        char x = quantizeAccelData(ard.getAnalog(0));
        char y = quantizeAccelData(ard.getAnalog(1));
        char z = quantizeAccelData(ard.getAnalog(2));
        
        unsigned int distance = 0;
        distance += abs(x - initX);
        distance += abs(y - initY);
        distance += abs(z - initZ);
        
        if (distance > 5) {
            return;
        }
        
        delay(1);
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