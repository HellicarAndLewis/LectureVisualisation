#include "ofxAudioVisualApp.h"

void ofxAudioVisualApp::setup() {
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
    //soundPlayer->load("sounds/Lecture1.wav");
    soundPlayer->setLoop(OF_LOOP_NORMAL);
    soundPlayer->setVolume(1.0);
    
    settings.add(sampleHeight.set("Sample Height", sampleImage.getHeight()/2, 0, sampleImage.getHeight()));
    settings.add(outputOn.set("Output On", false));
    settings.add(play.set("Play!", false));
    settings.add(backgroundRefresh.set("Background Auto", false));
    settings.add(exposure.set("Duration Percentage", 1.0, 0.0, 10.0));
    settings.add(colHigh.set("High", ofColor(255)));
    settings.add(colLow.set("Low", ofColor(0)));
    settings.add(usePalette.set("Use palette", false));
    settings.add(spectrumY.set("Sample Y", 0, 0, 100));
    
    gui.setup("settings/settings.xml");
    gui.add(settings);
    
    ofxNestedFileLoader loader;
    
    ofSetDataPathRoot("../../../../../SharedData/");
    vector<string> soundPaths = loader.load("lectures");
    
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
    
    if(soundPaths.size()) {
        soundPlayer->load(soundPaths[0]);
    } else {
        ofLogError("No Lectures Loaded");
    }

    
    
    loader.clearPaths();
    
    vector<string> spectrumPaths = loader.load("spectra");
    
    for(int i = 0; i < spectrumPaths.size(); i++) {
        vector<string> tempPath = ofSplitString(spectrumPaths[i], "/");
        string nameWithExtension = tempPath[tempPath.size()-1];
        vector<string> tempName = ofSplitString(nameWithExtension, ".");
        if(tempName.size() == 2) {
            ofParameter<bool>* spectrum;
            spectrum = new ofParameter<bool>;
            bool initialValue = i == 0 ? true : false;
            spectrum->set(tempName[0], initialValue);
            spectra[tempName[0]] = spectrumPaths[i];
            spectrumGroup.add(*spectrum);
            
        } else {
            ofLogError("Your File name had a '.' in it which is weird..., skipping file: " + nameWithExtension);
        }
    }
    
    if(spectrumPaths.size()) {
        spectrum.load(spectra.begin()->second);
    } else {
        ofLogError("No Spectra Loaded");
    }
    
    //spectrum.load(spectra["rainbow"]);
    
    gui.add(clips);
    gui.add(spectrumGroup);
    
    drawGui = true;
    
    ofAddListener(clips.parameterChangedE(), this, &ofxAudioVisualApp::onClipChanged);
    
    ofAddListener(spectrumGroup.parameterChangedE(), this, &ofxAudioVisualApp::onSpectrumChanged);
    
    ofAddListener(settings.parameterChangedE(), this, &ofxAudioVisualApp::onSettingChanged);
	
	ofBackground(0, 0, 0);
    ofSetBackgroundAuto(backgroundRefresh);
    
    ofSetLineWidth(2);
}

void ofxAudioVisualApp::update() {
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

void ofxAudioVisualApp::draw() {
    if(drawGui) {
        gui.draw();
        ofDrawBitmapString(ofToString(ofGetFrameRate()), ofGetWidth() - 100, ofGetHeight() - 20);
    }
}

float ofxAudioVisualApp::getAverageVolume(vector<float>& buffer) {
    float n = buffer.size();
    long double average = 0;
    for(int i = 0; i < n; i++) {
        average += buffer[i];
    }
    average /= n;
    return average;
}

void ofxAudioVisualApp::plot(vector<float>& buffer, float scale, float offset) {
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

void ofxAudioVisualApp::audioReceived(float* input, int bufferSize, int nChannels) {
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

void ofxAudioVisualApp::onSpectrumChanged(ofAbstractParameter &p) {
    string spectrumName = spectra[p.getName()];
    for(auto it = spectra.begin(); it != spectra.end(); it++) {
        string name = it->first;
        if(name != p.getName()) {
            spectrumGroup.get<bool>(name).setWithoutEventNotifications(false);
        }
    }
    spectrum.load(spectrumName);
}

void ofxAudioVisualApp::onSettingChanged(ofAbstractParameter &p) {
    string name = p.getName();
    if(name == "Play!") {
        ofClear(0);
        if(outputOn) {
//            soundPlayer->play();
//            soundPlayer->setPosition(0.5f);
//            int sampleDuration = 2*soundPlayer->getPositionMS();
//            sampleDuration /= 0.001;
//            soundPlayer->setPosition(0.0);
            soundPlayer->setSpeed(exposure);
            soundPlayer->stop();
            soundPlayer->play();
            ofHideCursor();
            //soundPlayer->setVolume(0.0);
        }
        ofSetFullscreen(true);
        drawGui = false;
    }
    if(name == "Background Auto") {
        if(backgroundRefresh) {
            ofSetBackgroundAuto(true);
        } else {
            ofSetBackgroundAuto(false);
        }
    }
}

void ofxAudioVisualApp::onClipChanged(ofAbstractParameter &p) {
    string clipName = soundClips[p.getName()];
    if(soundPlayer->isPlaying()) {
        soundPlayer->stop();
    }
    soundPlayer->load(clipName);
    if(outputOn) {
        soundPlayer->play();
    }
}

void ofxAudioVisualApp::keyPressed(int key) {
    switch (key) {
        case 'g':
            drawGui = !drawGui;
            break;
        case 'f':
            ofToggleFullscreen();
            break;
        case 'b':
            ofSetBackgroundAuto(!ofGetBackgroundAuto());
            break;
        case 'm':
            ofShowCursor();
            break;
        default:
            break;
    }
}

ofColor ofxAudioVisualApp::getColorLerp(int i) {
    float percent = ofMap(drawBins[i], 0, 0.1, 0, 1, true);
    ofColor inBetween = colLow.get().getLerped(colHigh.get(), percent);
//    ofSetColor(inBetween);
    return inBetween;
}

ofColor ofxAudioVisualApp::getColorFromSpectrum(int i) {
    float percent = ofMap(drawBins[i], 0, 0.1, 0, 1, true);
    ofColor inBetween = spectrum.getColor(ofMap(percent, 0, 1, 0, spectrum.getWidth()-1, true), (int)ofMap(spectrumY, 0, 100, 0, spectrum.getHeight()-1, true));
    return inBetween;
}

ofColor ofxAudioVisualApp::getColor(int i){
    if (usePalette){
        return getColorFromSpectrum(i);
    }else{
        return getColorLerp(i);
    }
}


void ofxAudioVisualApp::exit() {
    ofSoundStreamClose();
}
