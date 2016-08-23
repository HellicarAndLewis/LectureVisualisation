#pragma once

#include "ofMain.h"
#include "ofxAudioVisualApp.h"

class Stream : public ofBaseApp {
public:
    void setup();
    void draw(ofxAudioVisualApp* app, vector<float>* drawBins, float threshold);
    void drawFbo(ofxAudioVisualApp* app, vector<float>* drawBins, float threshold);
    
    float x;
    
    ofFbo fbo, fbo2;
    
    ofImage screen;
};