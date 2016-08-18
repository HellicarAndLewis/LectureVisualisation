#include "ofApp.h"

void ofApp::setup() {
    ofxAudioVisualApp::setup();
    
    circleStyles = {"normal", "noise", "volume"};
    currentStyle = circleStyles[0];
    
    for (int i = 0; i < circleStyles.size(); i++){
        ofParameter<bool>* style;
        style = new ofParameter<bool>;
        style->set(circleStyles[i], i==0 ? true : false);
        styleGroup.add(*style);
    }
    
    gui.add(numSpirals.set("Spirals", 5, 1, 10));
    gui.add(spiralRadius.set("Radius", 20, 10, 500));
    gui.add(styleGroup);
    
    noiseOffset = ofRandom(-100, 100);
    
    ofAddListener(settings.parameterChangedE(), this, &ofApp::onSettingChanged);
    ofAddListener(styleGroup.parameterChangedE(), this, &ofApp::onStyleChanged);
    
    vertSectors = 3;
    horiSectors = 3;
    createSectors(vertSectors, horiSectors, &sectors);
    activeSectors = vector<bool> (vertSectors * horiSectors, false);
    activeSectors[4] = true;
    
    reinitialize();
}

void ofApp::draw() {
    ofPushMatrix();
    ofPushStyle();
    ofTranslate(xPosition, yPosition);
    ofRotate(theta, 0, 0, 1);
    
    for(int i = 0; i < drawBins.size(); i++) {
        ofColor col = ofxAudioVisualApp::setColorLerp(i);
        
        float drawRadius;
        if (currentStyle == "normal"){
            drawRadius = spiralRadius;
        } else if (currentStyle == "noise"){
            drawRadius = spiralRadius * ofNoise((noiseOffset+theta)/100) + spiralRadius*0.25;
        } else if (currentStyle == "volume"){
            drawRadius = ofMap(getAverageVolume(drawBins), 0, 0.008, 0, spiralRadius, true);
        }
        
        if(col.r + col.g + col.b == 0) drawRadius = 0;
        ofDrawCircle(0, ofMap(i, 0, drawBins.size(), 0, drawRadius), ofMap(drawBins[i], 0, 0.01, 0, 2, true));
    }
    ofPopStyle();
    ofPopMatrix();
    
    theta += 1.0;
    if(theta >= 360) {
        reinitialize();
        colLow = ofColor(ofRandom(255), ofRandom(255), ofRandom(255), ofRandom(127));
        colHigh = ofColor(ofRandom(255), ofRandom(255), ofRandom(255), ofRandom(127));
        noiseOffset = ofRandom(-100, 100);
//        Randomly choosing sector don't work with keypress, will always rewrite
//        setActiveSectors((int)ofRandom(8));
    }
    ofxAudioVisualApp::draw();
}

void ofApp::keyPressed(int key) {
    ofxAudioVisualApp::keyPressed(key);
    
    switch (key) {
        case 'i':
            setActiveSectors(0);
            break;
        case 'o':
            setActiveSectors(1);
            break;
        case 'p':
            setActiveSectors(2);
            break;
        case 'k':
            setActiveSectors(3);
            break;
        case 'l':
            setActiveSectors(4);
            break;
        case ';':
            setActiveSectors(5);
            break;
        case ',':
            setActiveSectors(6);
            break;
        case '.':
            setActiveSectors(7);
            break;
        case '/':
            setActiveSectors(8);
            break;
        default:
            break;
    }
}

void ofApp::setActiveSectors(int sectorNo){
    for (auto sector : activeSectors){
        sector = false;
    }
    
    activeSectors[sectorNo] = true;
    
}

void ofApp::onSettingChanged(ofAbstractParameter &p){
    string name = p.getName();
    if(name == "Play!") {
        reinitialize();
    }
}

void ofApp::onStyleChanged(ofAbstractParameter &p){
    string name = p.getName();
    
    for (int i = 0; i < circleStyles.size(); i++){
        if (name == circleStyles[i]){
            currentStyle = circleStyles[i];
            break;
        }
    }
    
    for (int i = 0; i < styleGroup.size(); i++){
        string it = styleGroup.getName(i);
        if (name != it){
            styleGroup.get<bool>(circleStyles[i]).setWithoutEventNotifications(false);
        }
    }
}

void ofApp::reinitialize(){
    spiralRadius = ofRandom(300, 500);
    theta = 0.0;
    
    createSectors(vertSectors, horiSectors, &sectors);
    
    for (int i = 0; i < activeSectors.size(); i++){
        if (activeSectors[i]){
            // Random positio in the rectangle sector
//            xPosition = ofRandom(sectors[i][0], sectors[i][0]+sectors[i][2]);
//            yPosition = ofRandom(sectors[i][1], sectors[i][1]+sectors[i][3]);
            // Center of the rectangle sector
            xPosition = sectors[i][0] + sectors[i][2]/2;
            yPosition = sectors[i][1] + sectors[i][3]/2;
            break;
        }
    }
}

void ofApp::createSectors(int vert, int hori, vector< vector<float> >* targetVector){
    float w, h;
    w = ofClamp(ofGetWidth() / horiSectors, 0, ofGetWidth());
    h = ofClamp(ofGetHeight() / vertSectors, 0, ofGetHeight());
    
    targetVector->clear();
    
    for (int i = 0; i < vertSectors; i++){
        for (int j = 0; j < horiSectors; j++){
            float x, y;
            
            x = j * w;
            y = i * h;
            
            vector<float> singleSector = {x, y, w, h};
            targetVector->push_back(singleSector);
        }
    }
}
