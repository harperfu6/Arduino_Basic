#pragma once

#include "ofMain.h"
#define LENGTH 50
#define S_LENGTH 5

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
    
    ofArduino ard;
    int analog_value;
    
private:
    void setupArduino(const int &version);
    void calc_avarage(ofVec2f *array);
    void calc_median(ofVec2f *array);
    void analogPinChanged(const int &pinNum);
    deque<int> buffer;
    int avarage[LENGTH] = {};
    int median[LENGTH] = {};
    int s_median[S_LENGTH] = {};
    ofVec2f data[LENGTH] = {};
};
