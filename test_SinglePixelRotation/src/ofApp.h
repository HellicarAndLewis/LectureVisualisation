#pragma once

#include "ofMain.h"
#include "ofxFft.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp {
public:
	void setup();
	void plot(vector<float>& buffer, float scale, float offset);
	void audioReceived(float* input, int bufferSize, int nChannels);
    float getAverageVolume(vector<float>& buffer);
	void draw();

	int plotHeight, bufferSize;
    
    ofImage sampleImage;
    ofPixels samplePixels;
    
    ofxPanel gui;
    ofParameter<int> sampleHeight;

	ofxFft* fft;
	
	ofMutex soundMutex;
	vector<float> drawBins, middleBins, audioBins;
};
