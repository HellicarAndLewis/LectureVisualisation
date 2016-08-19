#pragma once

#include "ofMain.h"
#include "ofxAudioVisualApp.h"

class GerhardStrip : public ofBaseApp {
public:
    void draw(ofxAudioVisualApp* app, vector<float>* drawBins, float thresholdl, bool symmetrical);
    
    void setXY(float newX, float newY);
    
    float x = 0;
    float y = 0;
};