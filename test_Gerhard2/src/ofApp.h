#pragma once

#include "ofxAudioVisualApp.h"

class ofApp : public ofxAudioVisualApp {
public:
    void setup();
	void draw();
    void keyPressed(int key);
    void onSettingChanged(ofAbstractParameter &p);

    float x;
    
    
    void setupGui();
    void drawGui(ofEventArgs & args);
    
    ofParameter<float> threshold;
    ofParameter<bool> symmetrical;
};
