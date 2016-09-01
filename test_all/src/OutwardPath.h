#pragma once

#include "ofMain.h"
#include "ofxAudioVisualApp.h"

class OutwardPath {
public:
    void setup();
    void draw(ofxAudioVisualApp* app, vector<float>* drawBins, float threshold);
    void reset();
    
    ofFbo fbo;
    
    float radius;
};