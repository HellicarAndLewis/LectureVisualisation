#pragma once

#include "ofxAudioVisualApp.h"

class ofApp : public ofxAudioVisualApp {
public:
	void setup();

	void draw();
    
    ofParameter<int> numSpirals;
    ofParameter<float> spiralRadius;
    
    float theta;
    
    float xPosition, yPosition;
};
