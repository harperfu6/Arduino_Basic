#pragma once
#include "TemplateData.h"

#include "ofMain.h"
const unsigned long samplingInterval = 5;
const unsigned char sampleDataLength = 25;
char sampleData[sampleDataLength][numAxises];

class testApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    void beginCapture();
    void endCapture();
    void processSample(int x, int y, int z);
    char quantizeAccelData(int accData);
    int detectGesture();
    unsigned int getDTMDistance(int templateIndex);
    void waitForAction();
    void delay(int msec);
    
    ofArduino ard;
    
private:
    void setupArduino(const int &version);

    char sampleData[sampleDataLength][3];
    int sampleCount = 0;
    bool isCapturing = false;
    bool wasButtonPressed = false;
    const int notFound = -1;
};
