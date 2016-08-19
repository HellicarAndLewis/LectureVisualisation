#pragma once

#include "ofMain.h"
#include "ofxAudioVisualApp.h"

class Gerhard : public ofBaseApp {
public:
    void draw(ofxAudioVisualApp* app, vector<float>* drawBins, float threshold, bool symmetrical);
    
    float x = 0;
};