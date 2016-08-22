#pragma once

#include "ofMain.h"
#include "ofxAudioVisualApp.h"

class History : public ofBaseApp {
public:
    void setup(ofxFft* fft);
    void draw(ofxAudioVisualApp* app, vector<float>* drawBins, float threshold);
    void resetMesh();
    
    ofMesh mesh;
    
    int yOffset, binSize;
};