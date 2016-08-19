#pragma once

#include "ofxAudioVisualApp.h"

class ofApp : public ofxAudioVisualApp {
public:
    void setup();
	void draw();

    float x;
    
    void setupGui();
    void drawGui(ofEventArgs & args);
};
