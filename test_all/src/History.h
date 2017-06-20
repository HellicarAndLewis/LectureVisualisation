#pragma once

#include "ofMain.h"
#include "ofxAudioVisualApp.h"

class History {
public:
    void setup(ofxFft* fft);
    void draw(ofxAudioVisualApp* app, vector<float>* drawBins, float threshold);
    void reset();
    
    ofMesh myMesh;
    
    ofFbo buff;
    
    int yOffset, binSize;
};
