#pragma once

#include "ofMain.h"
#include "ofxFft.h"
#include "ofxGui.h"
#include "ofxNestedFileLoader.h"

class ofxAudioVisualApp : public ofBaseApp {
public:
    // App
	void setup();
	void plot(vector<float>& buffer, float scale, float offset);
	void audioReceived(float* input, int bufferSize, int nChannels);
    void keyPressed(int key);
    void onSettingChanged(ofAbstractParameter &p);
    void onSpectrumChanged(ofAbstractParameter &p);
    
    void onClipChanged(ofAbstractParameter &p);
    float getAverageVolume(vector<float>& buffer);
    ofColor getColorLerp(int i);
    ofColor getColorFromSpectrum(int i);
    ofColor getColor(int i);
    
    void update();
	void draw();
    void exit();

	int plotHeight, bufferSize;
    
    ofImage sampleImage;
    ofPixels samplePixels;
    
    ofImage spectrum;
    
    ofSoundPlayer* soundPlayer;
    
    ofxFft* fft;
    
    ofMutex soundMutex;
    vector<float> drawBins, middleBins, audioBins;
    
 
    // GUI
    void setupGui();
    void drawGui(ofEventArgs & args);
    
    ofxPanel gui, gui2;
    ofParameter<int> sampleHeight;
    
    ofParameterGroup settings;
    ofParameter<bool> outputOn;
    ofParameter<bool> backgroundRefresh;
    ofParameter<bool> play;
    ofParameter<float> exposure;
    ofParameter<float> scrub;
    ofParameter<float> drawSpeed;
    
    ofParameter<int> spectrumY;
    ofParameter<ofColor> colLow;
    ofParameter<ofColor> colHigh;
    ofParameter<bool> usePalette;
    
    ofParameterGroup clips;
    map< string, string > soundClips;
    
    ofParameterGroup spectrumGroup;
    map< string, string > spectra;
    
    
    ofParameter<float> threshold;
    ofParameter<bool> symmetrical;

    ofParameterGroup startEndBin;
    ofParameter<int> startBin;
    ofParameter<int> endBin;
    
    ofParameterGroup cutUpDown;
    ofParameter<float> cutUp;
    ofParameter<float> cutDown;
};