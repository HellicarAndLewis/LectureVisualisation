#pragma once

#include "ofxAudioVisualApp.h"
#include "Gerhard.h"
#include "Circle.h"
#include "History.h"
#include "GerhardStrip.h"

class ofApp : public ofxAudioVisualApp {
public:
    void setup();
	void draw();
    void keyPressed(int key);
    void onSettingChanged(ofAbstractParameter &p);
    void onVisualizationChanged(ofAbstractParameter &p);
    void reset();
    
    bool resetting;

    float x;
    
    void setupGui();
    void drawGui(ofEventArgs & args);
    
    ofParameter<float> threshold;
    ofParameter<bool> symmetrical;
    
    Gerhard gerhard;
    Circle circle;
    History history;
    GerhardStrip gStrip;
    
    ofParameterGroup visualizations;
    ofParameter<bool> isGerhard;
    ofParameter<bool> isCircle;
    ofParameter<bool> isHistory;
    ofParameter<bool> isGerhardStrip;
    
    vector< ofParameter<bool>* > visGroup;
};
