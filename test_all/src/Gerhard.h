#pragma once

#include "ofMain.h"
#include "ofxAudioVisualApp.h"

class Gerhard {
public:
    void draw(ofxAudioVisualApp* app, vector<float>* drawBins, float threshold, bool symmetrical);
    void reset();
    
    float x = 0;
};