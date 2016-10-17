#include "ofxAudioVisualApp.h"

//----------------------- App -----------------------------------------------

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

            // Apply metadata after this
            metadata[soundPaths[i]]["time"] = "14:00";
            metadata[soundPaths[i]]["length"] = "200";
            metadata[soundPaths[i]]["date"] = "20_04_2016";
            metadata[soundPaths[i]]["dayOfYear"] = "360";
            metadata[soundPaths[i]]["day"] = "Wednesday";
            metadata[soundPaths[i]]["maxTemp"] = "14";
            metadata[soundPaths[i]]["minTemp"] = "4";
            metadata[soundPaths[i]]["gender"] = "male";
            metadata[soundPaths[i]]["category"] = "science";

        } else {
            ofLogError("Your File name had a '.' in it which is weird..., skipping file: " + nameWithExtension);
        }
    }
    
    if(soundPaths.size()) {
        soundPlayer->load(soundPaths[0]);
        currentClip = soundPaths[0];
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
        setBaseColor();
    } else {
        ofLogError("No Spectra Loaded");
    }
    
    // These need the files to be loaded before adding to gui
    gui.add(clips);
    gui.add(spectrumGroup);
    ofAddListener(clips.parameterChangedE(), this, &ofxAudioVisualApp::onClipChanged);
    ofAddListener(spectrumGroup.parameterChangedE(), this, &ofxAudioVisualApp::onSpectrumChanged);

    // Set the different colours assigned to different categories
    categoryColors["science"] = ofColor(255, 0, 0);
    categoryColors["history"] = ofColor(206, 213, 0);
    categoryColors["religion"] = ofColor(0, 170, 144);


	ofBackground(0, 0, 0);
    ofSetBackgroundAuto(false);
    ofSetLineWidth(2);
    loadingSettings = false;
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
            drawBins[i] = ofClamp(drawBins[i], cutUp, cutDown);
        }
    } else {
        soundMutex.lock();
        for (int i = 0;i < nBandsToGet; i++){
            // take the max, either the smoothed or the incoming:
            if (drawBins[i] < middleBins[i]) drawBins[i] = middleBins[i];
            drawBins[i] = ofClamp(drawBins[i], cutUp, cutDown);
        }
        soundMutex.unlock();
    }
    
    if (useFFT){
        if (usePalette){
            spectrumY = ofLerp(spectrumY, ofMap(getAverageVolume(drawBins), 0.0001, 0.015, 0, 100, true), 0.1);
        }else{
            setColorFromFFT();
        }
    }
}

void ofxAudioVisualApp::draw() {
    
    if (backgroundRefresh){
        ofPushStyle();
        ofSetColor(0);
        ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
        ofPopStyle();
    }
    
}

//----------------------- GUI -----------------------------------------------

void ofxAudioVisualApp::setupGui(){
    settings.add(sampleHeight.set("Sample Height", sampleImage.getHeight()/2, 0, sampleImage.getHeight()));
    settings.add(outputOn.set("Output On", false));
    settings.add(play.set("Play", false));
    settings.add(backgroundRefresh.set("Background Auto", false));
    settings.add(exposure.set("Speed", 1.0, 0.0, 10.0));
    settings.add(scrub.set("Scrub", 0, 0, 1));
    settings.add(drawSpeed.set("Draw Speed", 1, -5, 5));
    
    settings.add(colHigh.set("High", ofColor(255)));
    settings.add(colLow.set("Low", ofColor(0)));
    settings.add(useFFT.set("Use FFT", false));
    settings.add(usePalette.set("Use palette", false));
    settings.add(useMetadata.set("Use metadata", true));
    settings.add(spectrumY.set("Sample Y", 0, 0, 100));
    
    gui.setup("Main");
    gui.add(settings);
    ofAddListener(settings.parameterChangedE(), this, &ofxAudioVisualApp::onSettingChanged);

    
    gui2.setup();
    gui2.setPosition(230, 10);
    
    gui2.add(threshold.set("Threshold", 0.0038, 0, 0.009));
    gui2.add(symmetrical.set("Symmetrical", false));
    
    startEndBin.add(startBin.set("Start Bin", 0, 0, 512));
    startEndBin.add(endBin.set("End Bin", 1024, 0, 1024));
    gui2.add(startEndBin);
    
    cutUpDown.add(cutUp.set("Cut Up", 0, 0, 0.1));
    cutUpDown.add(cutDown.set("Cut Down", 0.1, 0, 0.1));
    gui2.add(cutUpDown);
}

void ofxAudioVisualApp::drawGui(ofEventArgs & args){
    ofBackground(50);
    gui.draw();
    
    gui2.draw();
    
    ofDrawBitmapString(ofGetTimestampString("%Y/%m/%d  %Z %H:%M:%S"), 20, ofGetHeight() - 20);
    ofDrawBitmapString(ofToString(ofGetFrameRate()), ofGetWidth() - 100, ofGetHeight() - 20);
    
    ofPushMatrix();
    ofPushStyle();
    
    ofTranslate(ofGetWidth() - 270, ofGetHeight() - 270);
    spectrum.update();
    spectrum.draw(0, 0, 200, 200);
    ofNoFill();
    ofSetColor(255);
    ofSetLineWidth(2);
    ofDrawRectangle(0, ofMap(spectrumY, 0, 100, 0, 196), 200, 4);
    
    ofPopStyle();
    ofPopMatrix();
}

//---------------------------------------------------------------------------

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
    if(!loadingSettings){
        string spectrumName = spectra[p.getName()];
        for(auto it = spectra.begin(); it != spectra.end(); it++) {
            string name = it->first;
            if(name != p.getName()) {
                spectrumGroup.get<bool>(name).setWithoutEventNotifications(false);
            }
        }
        spectrum.load(spectrumName);
    }
}

void ofxAudioVisualApp::onSettingChanged(ofAbstractParameter &p) {
    string name = p.getName();
    if(name == "Play") {
        ofClear(0);
        if(outputOn) {
            soundPlayer->setSpeed(exposure);
            soundPlayer->stop();
            soundPlayer->play();
            soundPlayer->setPosition(scrub);
        }
    }
    
    if(name == "Scrub"){
        soundPlayer->setPosition(scrub);
    }
    
    if(name == "Speed"){
        soundPlayer->setSpeed(exposure);
    }
}

void ofxAudioVisualApp::onClipChanged(ofAbstractParameter &p) {
    if(!loadingSettings){
        string clipName = soundClips[p.getName()];
        if(soundPlayer->isPlaying()) {
            soundPlayer->stop();
        }
        soundPlayer->load(clipName);
        if(outputOn) {
            soundPlayer->play();
        }

        currentClip = clipName;

        setBaseColor();
    }
}

void ofxAudioVisualApp::keyPressed(int key) {
    switch (key) {
        case 'f':
            ofToggleFullscreen();
            break;
        case 'b':
            backgroundRefresh = !backgroundRefresh;
            break;
        default:
            break;
    }
}

void ofxAudioVisualApp::setBaseColor(){
    //Colour etc change here with clip's metadata
    vector<string> startTime = ofSplitString(metadata[currentClip]["time"], ":");
    int startHour = ofToInt(startTime[0]);
    int startMinute = ofToInt(startTime[1]);
    float redValue = ofMap(startHour, 12, 24, 0, 255, true);

    int dayOfYear = ofToInt(metadata[currentClip]["dayOfYear"]);
    float greenValue = ofMap(dayOfYear, 1, 365, 0, 255);

    // blueValue to be decided on the subject, assuming now
    float blueValue = 128;

    baseColor = ofColor(redValue, greenValue , blueValue);
}

ofColor ofxAudioVisualApp::getColorLerp(int i) {
    float percent = ofMap(drawBins[i], 0, 0.1, 0, 1, true);
    ofColor inBetween = colLow.get().getLerped(colHigh.get(), percent);
    return inBetween;
}

ofColor ofxAudioVisualApp::getColorFromSpectrum(int i) {
    float percent = ofMap(drawBins[i], 0, 0.1, 0, 1, true);
    ofColor inBetween = spectrum.getColor(
                            ofMap(percent, 0, 1, 0, spectrum.getWidth()-1, true),
                            (int)ofMap(spectrumY, 0, 100, 0, spectrum.getHeight()-1, true)
                        );
    return inBetween;
}

ofColor ofxAudioVisualApp::getColorFromMetadata(int i, int position){
    float percent = ofMap(drawBins[i], 0, 0.1, 0, 1, true);

    float positionHours = position/1000/60/60;
    float positionMinutes = position/1000/60;

    float startHour = ofToInt(ofSplitString(metadata[currentClip]["time"], ":")[0]);
    float currentHour = startHour + positionHours;

    float redValue = ofMap(currentHour, 12, 24, 0, 255, true);

    float greenValue = baseColor.g;
    float blueValue = baseColor.b;

    ofColor newColor;
    ofColor newColorLow = ofColor(redValue, greenValue, blueValue);
    ofColor newColorHigh = categoryColors[metadata[currentClip]["category"]];

    newColor = newColorLow.getLerped(newColorHigh, percent);

    return newColor;
}

void ofxAudioVisualApp::setColorFromFFT(){
    float r1, g1, b1, r2, g2, b2, average = 0, count = 0;
    int divider1 = drawBins.size() * log10(2.00005 * 10/12);
    int divider2 = drawBins.size() * log10(2.005 * 10/12);
    int divider3 = drawBins.size() * log10(2.05 * 10/12);
    int divider4 = drawBins.size() * log10(2.1 * 10/12);
    int divider5 = drawBins.size() * log10(2.2 * 10/12);
    int divider6 = drawBins.size() * log10(12 * 10/12);
    
    for (int i = 0; i < drawBins.size(); i++){
        float mappedValue = ofMap(drawBins[i], 0, 0.007, 0, 255, true);
        
        count++;
        if(i < divider1){
            average += mappedValue;
            if(i == divider1 - 1){
                r1 = average/count;
                average = 0;
                count = 0;
            }
        }else if(i < divider2){
            average += mappedValue;
            if(i == divider2 - 1){
                g1 = average/count;
                average = 0;
                count = 0;
            }
        }else if(i < divider3){
            average += mappedValue;
            if(i == divider3 - 1){
                b1 = average/count;
                average = 0;
                count = 0;
            }
        }else if(i < divider4){
            average += mappedValue;
            if(i == divider4 - 1){
                r2 = average/count;
                average = 0;
                count = 0;
            }
        }else if(i < divider5){
            average += mappedValue;
            if(i == divider5 - 1){
                g2 = average/count;
                average = 0;
                count = 0;
            }
        }else if(i < divider6){
            average += mappedValue;
            if(i == divider6 - 1){
                b2 = average/count;
                average = 0;
                count = 0;
            }
        }
    }
    
    colHigh.set(colHigh->getLerped(ofColor(r1, g1, b1, colHigh->a), 0.1));
    colLow.set(colLow->getLerped(ofColor(r2, g2, b2, colLow->a), 0.1));
}

ofColor ofxAudioVisualApp::getColor(int i, int position){
    if (usePalette){
        return getColorFromSpectrum(i);
    }else if(useMetadata){
        return getColorFromMetadata(i, position);
    }else{
        return getColorLerp(i);
    }
}


void ofxAudioVisualApp::exit() {
    ofSoundStreamClose();
}
