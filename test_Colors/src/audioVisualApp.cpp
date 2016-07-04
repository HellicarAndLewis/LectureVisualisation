#include "audioVisualApp.h"

void audioVisualApp::setup() {
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
    settings.add(play.set("Play!", false));
    settings.add(exposure.set("Exposure (sec)", 300, 1, 600));
    
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
    
    drawGui = true;
    
    ofAddListener(clips.parameterChangedE(), this, &audioVisualApp::onClipChanged);
    
    ofAddListener(settings.parameterChangedE(), this, &audioVisualApp::onSettingChanged);
	
	ofSoundStreamSetup(0, 1, this, 44100, bufferSize, 4);
	
	ofBackground(0, 0, 0);
    ofSetBackgroundAuto(false);
    
    ofSetLineWidth(2);
}

void audioVisualApp::update() {
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

void audioVisualApp::draw() {
    if(drawGui) {
        gui.draw();
    }
}

float audioVisualApp::getAverageVolume(vector<float>& buffer) {
    float n = buffer.size();
    long double average = 0;
    for(int i = 0; i < n; i++) {
        average += buffer[i];
    }
    average /= n;
    return average;
}

void audioVisualApp::plot(vector<float>& buffer, float scale, float offset) {
	ofNoFill();
	float n = buffer.size();
	ofDrawRectangle(0, 0, n, plotHeight);
	glPushMatrix();
	glTranslatef(0, plotHeight / 2 + offset, 0);
    samplePixels = sampleImage.getPixels();
    ofColor col;
	for (int i = 0; i < n; i ++) {
        col = ofColor(255);// samplePixels.getColor(i/n * samplePixels.getWidth(), sampleHeight);
        ofSetColor(col);
		ofDrawLine(i, 0, i, sqrt(buffer[i]) * scale);
	}
	glPopMatrix();
}

void audioVisualApp::audioReceived(float* input, int bufferSize, int nChannels) {
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

void audioVisualApp::onSettingChanged(ofAbstractParameter &p) {
    string name = p.getName();
    if(name == "Play!") {
        if(outputOn) {
            soundPlayer->play();
        }
    }
}

void audioVisualApp::onClipChanged(ofAbstractParameter &p) {
    string clipName = soundClips[p.getName()];
    if(soundPlayer->isPlaying()) {
        soundPlayer->stop();
    }
    soundPlayer->load(clipName);
    if(outputOn) {
        soundPlayer->play();
    }
}

void audioVisualApp::keyPressed(int key) {
    switch (key) {
        case 'g':
            drawGui = !drawGui;
            break;
        case 'f':
            ofToggleFullscreen();
            break;
        default:
            break;
    }
}


void audioVisualApp::exit() {
    ofSoundStreamClose();
}
