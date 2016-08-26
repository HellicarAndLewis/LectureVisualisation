#pragma once

#include "ofxAudioVisualApp.h"
#include "Gerhard.h"
#include "Circle.h"
#include "History.h"
#include "GerhardStrip.h"
#include "Stream.h"

class ofApp : public ofxAudioVisualApp {
public:
    void setup();
	void draw();
    void keyPressed(int key);
    void onSettingChanged(ofAbstractParameter &p);
    void onVisualizationChanged(ofAbstractParameter &p);
    void onBinSizeChanged(ofAbstractParameter &p);
    void reset();
    
    bool resetting;

    float x;
    
    void setupGui();
    void drawGui(ofEventArgs & args);
    void guiKeyPressed(ofKeyEventArgs & args);
    void saveScreenShots(string contextName);
    
    Gerhard gerhard;
    Circle circle;
    History history;
    GerhardStrip gStrip;
    Stream stream;
    
    ofParameterGroup visualizations;
    ofParameter<bool> isGerhard;
    ofParameter<bool> isCircle;
    ofParameter<bool> isHistory;
    ofParameter<bool> isGerhardStrip;
    ofParameter<bool> isStream;

    vector< ofParameter<bool>* > visGroup;
};
