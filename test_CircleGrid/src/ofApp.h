#pragma once

#include "ofMain.h"
#include "ofxFft.h"
#include "ofxGui.h"
#include "ofxNestedFileLoader.h"

class ofApp : public ofBaseApp {
public:
	void setup();
	void plot(vector<float>& buffer, float scale, float offset);
	void audioReceived(float* input, int bufferSize, int nChannels);
    void onSettingChanged(ofAbstractParameter &p);
    void onClipChanged(ofAbstractParameter &p);
    float getAverageVolume(vector<float>& buffer);
    
    void update();
	void draw();
    void exit();

	int plotHeight, bufferSize;
    
    ofImage sampleImage;
    ofPixels samplePixels;
    
    ofxPanel gui;
    ofParameter<int> sampleHeight;
    
    ofParameterGroup settings;
    ofParameter<bool> outputOn;
    ofParameter<bool> backgroundRefreshOn;
    ofParameter<int> numSpirals;
    ofParameter<float> spiralRadius;
    
    ofParameterGroup clips;
    map< string, string > soundClips;
    
    ofSoundPlayer* soundPlayer;

	ofxFft* fft;
    
    float theta;
	
	ofMutex soundMutex;
	vector<float> drawBins, middleBins, audioBins;
};
