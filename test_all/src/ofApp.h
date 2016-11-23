#pragma once

#include "ofxAudioVisualApp.h"
#include "Gerhard.h"
#include "Circle.h"
#include "History.h"
#include "GerhardStrip.h"
#include "Stream.h"
#include "OutwardCircle.h"
#include "OutwardPath.h"
#include "OutwardSeeds.h"

//#include "util_GradientSampler.h"

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
    
    Gerhard gerhard;
    Circle circle;
    History history;
    GerhardStrip gStrip;
    Stream stream;
    OutwardCircle outwardCircle;
    OutwardPath outwardPath;
    OutwardSeeds outwardSeeds;
    
    ofParameterGroup visualizations;
    ofParameter<bool> isGerhard;
    ofParameter<bool> isCircle;
    ofParameter<bool> isHistory;
    ofParameter<bool> isGerhardStrip;
    ofParameter<bool> isStream;
    ofParameter<bool> isOutwardCircle;
    ofParameter<bool> isOutwardPath;
    ofParameter<bool> isOutwardSeeds;

    vector< ofParameter<bool>* > visGroup;
    
//    GradientSampler gradientSampler;
};
