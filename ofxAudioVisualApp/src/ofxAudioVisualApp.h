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
    void setBaseColor();
    ofColor getColorLerp(int i);
    ofColor getColorFromSpectrum(int i);
    ofColor getColorFromMetadata(int i, int position);
    ofColor getColor(int i, int position);
    void setColorFromFFT();
    
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
    
    bool loadingSettings;
    
 
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
    ofParameter<bool> useMetadata;
    ofParameter<bool> useFFT;
    
    ofParameterGroup clips;
    map< string, string > soundClips;
    map< string, map<string, string> > metadata;
    map< string, ofColor > categoryColors;
    string currentClip;
    ofColor baseColor;
    
    ofParameterGroup spectrumGroup;
    map< string, string > spectra;
    
    ofParameter<float> threshold;
    ofParameter<bool> symmetrical;

    ofParameterGroup startEndBin;
    ofParameter<int> startBin;
    ofParameter<int> endBin;
    ofParameter<float> startTime;
    
    ofParameterGroup cutUpDown;
    ofParameter<float> cutUp;
    ofParameter<float> cutDown;
};
