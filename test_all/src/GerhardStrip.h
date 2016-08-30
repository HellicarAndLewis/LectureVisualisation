#pragma once

#include "ofMain.h"
#include "ofxAudioVisualApp.h"

class GerhardStrip {
public:
    void draw(ofxAudioVisualApp* app, vector<float>* drawBins, float threshold, bool symmetrical);
    
    void reset();
    
    float x = 0;
    float y = 0;
};