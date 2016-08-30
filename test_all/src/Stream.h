#pragma once

#include "ofMain.h"
#include "ofxAudioVisualApp.h"

class Stream {
public:
    void setup(ofxAudioVisualApp* app);
    void draw(ofxAudioVisualApp* app, vector<float>* drawBins, float threshold);
    void drawFbo(ofxAudioVisualApp* app, vector<float>* drawBins, float threshold);
    void trimPixels();
    void reset();
    
    ofFbo fbo;
    ofPixels pixels;
    ofImage image;
    
    ofParameter<bool> enableTearing;
};