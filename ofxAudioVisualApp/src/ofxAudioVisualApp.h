#pragma once

#include "ofMain.h"
#include "ofxFft.h"
#include "ofxGui.h"
#include "ofxNestedFileLoader.h"

class ofxAudioVisualApp : public ofBaseApp {
public:
	void setup();
	void plot(vector<float>& buffer, float scale, float offset);
	void audioReceived(float* input, int bufferSize, int nChannels);
    void keyPressed(int key);
    void onSettingChanged(ofAbstractParameter &p);
    void onSpectrumChanged(ofAbstractParameter &p);
    
    void onClipChanged(ofAbstractParameter &p);
    float getAverageVolume(vector<float>& buffer);
    ofColor setColorLerp(int i);
    ofColor getColorFromSpectrum(int i);
    
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
    ofParameter<bool> backgroundRefresh;
    ofParameter<bool> play;
    ofParameter<float> exposure;
    ofParameter<int> spectrumY;
    ofParameter<ofColor> colLow;
    ofParameter<ofColor> colHigh;
    
    bool drawGui;
    
    ofParameterGroup clips;
    map< string, string > soundClips;
    
    ofParameterGroup spectrumGroup;
    map< string, string > spectra;
    
    ofImage spectrum;
    
    ofSoundPlayer* soundPlayer;

	ofxFft* fft;
	
	ofMutex soundMutex;
	vector<float> drawBins, middleBins, audioBins;
};