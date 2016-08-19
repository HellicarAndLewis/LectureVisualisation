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

    float x;
    
    void setupGui();
    void drawGui(ofEventArgs & args);
    
    ofParameter<float> threshold;
    ofParameter<bool> symmetrical;
    
    Gerhard gerhard;
    Circle circle;
    History history;
    GerhardStrip gStrip;
};
