#pragma once

#include "ofMain.h"
#include "ofxAudioVisualApp.h"

class Circle : public ofBaseApp {
public:
    void draw(ofxAudioVisualApp* app, vector<float>* drawBins, float threshold);
    
    float theta = -90;
};