#pragma once

#include "ofMain.h"
#include "ofxAudioVisualApp.h"

class Seed{
public:
    float cx, cy, radius;
    bool active;
    
    ofFbo fbo;
    
    void setup();
    void draw(ofxAudioVisualApp* app, vector<float>* drawBins, float threshold);
    void reset();
};



class OutwardSeeds {
public:
    void setup();
    void draw(ofxAudioVisualApp* app, vector<float>* drawBins, float threshold);
    void reset();
    bool collisionDetect(Seed* origin, Seed* target);
    
    vector<Seed> seeds;
    vector<Seed*> activeSeeds;
};