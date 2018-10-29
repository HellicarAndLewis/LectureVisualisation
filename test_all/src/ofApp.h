#pragma once

#include "ofxAudioVisualApp.h"
#include "History.h"

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
    
    void setupGui();
    void drawGui(ofEventArgs & args);
    void guiKeyPressed(ofKeyEventArgs & args);
    void saveScreenShots(string contextName);
    
    History history;
    
    ofParameterGroup visualizations;
    ofParameter<bool> isHistory;

    vector< ofParameter<bool>* > visGroup;
    
//    GradientSampler gradientSampler;
};
