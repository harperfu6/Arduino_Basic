#pragma once

#include "ofMain.h"

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
    
    ofEasyCam cam;
    
private:
    void setupArduino(const int &version);
    void analogPinChanged(const int &pinNum);
    
    int x, y, z;
    float pre_x, pre_y, pre_z;
    float n_x, n_y, n_z;
    float r_x, r_y, r_z;
};
