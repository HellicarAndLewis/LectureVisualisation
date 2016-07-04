#include "ofApp.h"

void ofApp::setup() {
	ofSetVerticalSync(true);
	
	plotHeight = 700;
	bufferSize = 2048;
	
	fft = ofxFft::create(bufferSize, OF_FFT_WINDOW_HAMMING);
	// To use FFTW, try:
	//fft = ofxFft::create(bufferSize, OF_FFT_WINDOW_HAMMING, OF_FFT_FFTW);
	
	drawBins.resize(fft->getBinSize());
	middleBins.resize(fft->getBinSize());
	audioBins.resize(fft->getBinSize());
	
	// 0 output channels,
	// 1 input channel
	// 44100 samples per second
	// [bins] samples per buffer
	// 4 num buffers (latency)
    
    soundPlayer = new ofSoundPlayer();
    soundPlayer->load("sounds/Lecture1.wav");
    // soundPlayer->play();
    soundPlayer->setLoop(OF_LOOP_NORMAL);
    soundPlayer->setVolume(1.0);
    
    settings.add(sampleHeight.set("Sample Height", sampleImage.getHeight()/2, 0, sampleImage.getHeight()));
    settings.add(outputOn.set("Output On", false));
    settings.add(backgroundRefreshOn.set("Background Refresh", true));
    settings.add(numSpirals.set("Spirals", 5, 1, 10));
    settings.add(spiralRadius.set("Radius", 20, 10, 500));
    
    gui.setup("settings/settings.xml");
    gui.add(settings);
    
    ofxNestedFileLoader loader;
    
    vector<string> soundPaths = loader.load("sounds");
    
    for(int i = 0; i < soundPaths.size(); i++) {
        vector<string> tempPath = ofSplitString(soundPaths[i], "/");
        string nameWithExtension = tempPath[tempPath.size()-1];
        vector<string> tempName = ofSplitString(nameWithExtension, ".");
        if(tempName.size() == 2) {
            ofParameter<bool>* clip;
            clip = new ofParameter<bool>;
            clip->set(tempName[0], false);
            soundClips[tempName[0]] = soundPaths[i];
            clips.add(*clip);
            
        } else {
            ofLogError("Your File name had a '.' in it which is weird..., skipping file: " + nameWithExtension);
        }
    }
    
    gui.add(clips);
    
    ofAddListener(clips.parameterChangedE(), this, &ofApp::onClipChanged);
    
    ofAddListener(settings.parameterChangedE(), this, &ofApp::onSettingChanged);
	
	ofSoundStreamSetup(0, 1, this, 44100, bufferSize, 4);
	
	ofBackground(0, 0, 0);
    
    ofSetLineWidth(2);
    theta = -90;
}

void ofApp::update() {
    int nBandsToGet = fft->getBinSize();
    float * val = ofSoundGetSpectrum(nBandsToGet);		// request 128 values for fft
    for (int i = 0;i < nBandsToGet; i++){
        // let the smoothed value sink to zero:
        drawBins[i] *= 0.96f;
    }
    
    if (outputOn) {
        for (int i = 0;i < nBandsToGet; i++){
            // take the max, either the smoothed or the incoming:
            if (drawBins[i] < val[i]) drawBins[i] = val[i];
        }
    } else {
        soundMutex.lock();
        for (int i = 0;i < nBandsToGet; i++){
            // take the max, either the smoothed or the incoming:
            if (drawBins[i] < middleBins[i]) drawBins[i] = middleBins[i];
        }
        soundMutex.unlock();
    }
}

void ofApp::draw() {
    int numSpiralsPerRow = ofGetWidth() / spiralRadius.get()*2;
    int numRows = max(numSpirals.get() / numSpiralsPerRow, 1);
    for(int y = 0; y < numRows; y++) {
        for(int x = 0; x < numSpiralsPerRow; x++) {
            ofPushMatrix();
            float xPosition = ofMap(x, 0, numSpiralsPerRow, spiralRadius, ofGetWidth() - spiralRadius);
            float yPosition = ofMap(y, 0, numRows, spiralRadius, ofGetHeight() - spiralRadius);
            ofTranslate(xPosition, yPosition);
            ofRotate(theta, 0, 0, 1);
            for(int i = 0; i < drawBins.size(); i++) {
                ofColor col = ofColor(ofMap(drawBins[i], 0, 0.01, 0, 255, true));
                float drawRadius = spiralRadius;
                if(col.r + col.g + col.b == 0) drawRadius = 0;
                ofDrawCircle(0, ofMap(i, 0, drawBins.size(), 0, drawRadius), ofMap(drawBins[i], 0, 0.01, 0, 2, true));
            }
            ofPopMatrix();
        }
    }
    gui.draw();
    theta += 0.1;
    
}

float ofApp::getAverageVolume(vector<float>& buffer) {
    float n = buffer.size();
    long double average = 0;
    for(int i = 0; i < n; i++) {
        average += buffer[i];
    }
    average /= n;
    return average;
}

void ofApp::plot(vector<float>& buffer, float scale, float offset) {
	ofNoFill();
	float n = buffer.size();
	ofDrawRectangle(0, 0, n, plotHeight);
	glPushMatrix();
	glTranslatef(0, plotHeight / 2 + offset, 0);
	//ofBeginShape();
    samplePixels = sampleImage.getPixels();
    ofColor col;
	for (int i = 0; i < n; i ++) {
        col = ofColor(255);// samplePixels.getColor(i/n * samplePixels.getWidth(), sampleHeight);
        ofSetColor(col);
		ofDrawLine(i, 0, i, sqrt(buffer[i]) * scale);
	}
	//ofEndShape();
	glPopMatrix();
}

void ofApp::audioReceived(float* input, int bufferSize, int nChannels) {	
	float maxValue = 0;
	for(int i = 0; i < bufferSize; i++) {
		if(abs(input[i]) > maxValue) {
			maxValue = abs(input[i]);
		}
	}
	for(int i = 0; i < bufferSize; i++) {
		input[i] /= maxValue;
	}
	
	fft->setSignal(input);
	
	float* curFft = fft->getAmplitude();
	memcpy(&audioBins[0], curFft, sizeof(float) * fft->getBinSize());
	
	maxValue = 0;
	for(int i = 0; i < fft->getBinSize(); i++) {
		if(abs(audioBins[i]) > maxValue) {
			maxValue = abs(audioBins[i]);
		}
	}
	for(int i = 0; i < fft->getBinSize(); i++) {
		audioBins[i] /= maxValue;
	}
	
	soundMutex.lock();
	middleBins = audioBins;
	soundMutex.unlock();
}

void ofApp::onSettingChanged(ofAbstractParameter &p) {
    string name = p.getName();
    if(name == "Output On") {
        if(outputOn) {
            soundPlayer->play();
        } else {
            soundPlayer->stop();
        }
    }
    if(name == "Background Refresh") {
        ofSetBackgroundAuto(backgroundRefreshOn);
    }
}

void ofApp::onClipChanged(ofAbstractParameter &p) {
    string clipName = soundClips[p.getName()];
    if(soundPlayer->isPlaying()) {
        soundPlayer->stop();
    }
    soundPlayer->load(clipName);
    if(outputOn) {
        soundPlayer->play();
    }
}


void ofApp::exit() {
    ofSoundStreamClose();
}
