#pragma once

#include "ofxAudioVisualApp.h"

class ofApp : public ofxAudioVisualApp {
public:
	void setup();
	void draw();
    void onSettingChanged(ofAbstractParameter &p);
    void onStyleChanged(ofAbstractParameter &p);
    void keyPressed(int key);
    
    void reinitialize();
    
    ofParameter<int> numSpirals;
    ofParameter<float> spiralRadius;
    ofParameterGroup styleGroup;
    vector<string> circleStyles;
    string currentStyle;
    
    float theta;
    float xPosition, yPosition;
    float noiseOffset;
    
    ofParameter<bool> verticallyCentered;
    ofParameter<bool> horizontallyCentered;
};
