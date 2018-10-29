#include "ofApp.h"

//----------------------- App -----------------------------------------------

void ofApp::setup() {
    ofxAudioVisualApp::setup();
    
//    gradientSampler.setup();
    isHistory.set("History", true);
    
    visGroup.push_back(&isHistory);
    
    for (auto vis : visGroup){
        visualizations.add(*vis);
    }
    
    gui2.add(visualizations);
    ofAddListener(visualizations.parameterChangedE(), this, &ofApp::onVisualizationChanged);
    ofAddListener(startEndBin.parameterChangedE(), this, &ofApp::onBinSizeChanged);
    ofAddListener(settings.parameterChangedE(), this, &ofApp::onSettingChanged);
    
    resetting = false;
    history.setup(fft);
}

void ofApp::draw() {
    ofxAudioVisualApp::draw();
    
    if (resetting){
        ofPushStyle();
        ofSetColor(0);
        ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
        ofPopStyle();
        resetting = false;
    }
    
//    if (isGerhard){
////        gradientSampler.update(gerhard.x);
//        gerhard.draw(this, &drawBins, threshold);
//    }else if (isCircle){
//        circle.draw(this, &drawBins, threshold);
//    }else if (isHistory){
    history.draw(this, &drawBins, threshold);
    history.buff.draw(buffX, 0, buffWidth, ofGetHeight()); // 1500 for 8x10

//    }else if (isGerhardStrip){
//        gStrip.draw(this, &drawBins, threshold, symmetrical);
//    }else if (isStream){
//        stream.draw(this, &drawBins, threshold);
//    }else if (isOutwardCircle){
//        outwardCircle.draw(this, &drawBins, threshold);
//    }else if (isOutwardPath){
//        outwardPath.draw(this, &drawBins, threshold);
//    }else if (isOutwardSeeds){
//        outwardSeeds.draw(this, &drawBins, threshold);
//    }
    
    ofDrawBitmapStringHighlight("FPS: " + ofToString(ofGetFrameRate()), ofGetWidth() - 100, 10);
}

void ofApp::keyPressed(int key) {
    ofxAudioVisualApp::keyPressed(key);
    
    switch (key) {
        case 'a':
            symmetrical = !symmetrical;
            break;
        case 's':
            saveScreenShots("main");
            break;
        case 'l':
            loadingSettings = true;
            gui.loadFromFile("./settings/settings1.xml");
            gui2.loadFromFile("./settings/settings2.xml");
            loadingSettings = false;
            break;
        default:
            break;
    }
}

//----------------------- GUI -----------------------------------------------

void ofApp::setupGui(){
    ofxAudioVisualApp::setupGui();
}

void ofApp::drawGui(ofEventArgs & args){
    ofxAudioVisualApp::drawGui(args);
    
//    gradientSampler.draw(ofGetWidth() - 270, ofGetHeight() - 600, 200, 200);
}

void ofApp::guiKeyPressed(ofKeyEventArgs & args){
    switch (args.key){
        case 's':
            saveScreenShots("gui");
            break;
        case 'g':
            gui.saveToFile("./settings/settings1.xml");
            gui2.saveToFile("./settings/settings2.xml");
            break;
        case 'l':
            loadingSettings = true;
            gui.loadFromFile("./settings/settings1.xml");
            gui2.loadFromFile("./settings/settings2.xml");
            loadingSettings = false;
            break;
        default:
            break;
    }
}

void ofApp::onSettingChanged(ofAbstractParameter &p){
    string name = p.getName();
    if(name == "Play") {
        reset();
    }
}

void ofApp::onVisualizationChanged(ofAbstractParameter &p){
    reset();
    if(!loadingSettings){
        string name = p.getName();
        
        for (int i = 0; i < visGroup.size(); i++){
            if (visGroup[i]->getName() == name){
                visGroup[i]->setWithoutEventNotifications(true);
            }else{
                visGroup[i]->setWithoutEventNotifications(false);
            }
        }
    }
}


//----------------------- Utilities ---------------------------------------

void ofApp::onBinSizeChanged(ofAbstractParameter &p){
    history.reset();
}

void ofApp::reset(){
    history.reset();
    resetting = true;
}

void ofApp::saveScreenShots(string contextName){
    ofImage screen;
    string timestamp = ofGetTimestampString("%Y-%m-%d-%H-%M-%S-");
    screen.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
    screen.update();
    screen.save("./documentation/" + timestamp + contextName + ".png");
}
