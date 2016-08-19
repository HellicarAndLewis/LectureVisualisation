#pragma once

#include "ofMain.h"
#include "ofxFft.h"
#include "ofxGui.h"
#include "ofxNestedFileLoader.h"
#include "ofxAudioVisualApp.h"

class ofApp : public ofxAudioVisualApp {
public:
    void setup();
    //void update();
	void draw();
    
    float theta;
    
    void setupGui();
    void drawGui(ofEventArgs & args);
};
