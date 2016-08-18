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
    void createSectors(int vert, int hori, vector< vector<float> >* targetVector);
    void setActiveSectors(int sectorNo);
    
    ofParameter<int> numSpirals;
    ofParameter<float> spiralRadius;
    ofParameterGroup styleGroup;
    vector<string> circleStyles;
    string currentStyle;
    
    float theta;
    float xPosition, yPosition;
    float noiseOffset;
    
    int vertSectors, horiSectors;
    vector< vector<float> > sectors;
    vector<bool> activeSectors;
};
