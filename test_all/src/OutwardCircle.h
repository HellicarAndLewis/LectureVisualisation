#pragma once

#include "ofMain.h"
#include "ofxAudioVisualApp.h"

class OutwardCircle {
public:
    void setup(ofxFft* fft);
    void draw(ofxAudioVisualApp* app, vector<float>* drawBins, float threshold);
    void reset();
    void resizeMesh(int size);
    
    ofMesh mesh;
//    ofEasyCam cam;
    
    float radius;
};