#pragma once

#include "ofxAudioVisualApp.h"

class ofApp : public ofxAudioVisualApp {
public:
    void setup();
	void draw();
    void onSettingChanged(ofAbstractParameter &p);

    float y;
    float theta;
    float size;
    
    ofParameter<float> threshold;
};
