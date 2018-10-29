#include "History.h"

void History::setup(ofxFft* fft){
    myMesh.setMode(OF_PRIMITIVE_LINE_STRIP);
    float x = 0;
    float y = ofGetHeight()/2;
    for(int i = 0; i < fft->getBinSize(); i++) {
		myMesh.addVertex(ofVec3f(x, y, 0));
		myMesh.addColor(ofColor(255));
        x += ofGetWidth()/fft->getBinSize()*2;
    }
    yOffset = 0;
    
    buff.allocate(1920, 1200);
}

void History::draw(ofxAudioVisualApp* app, vector<float>* drawBins, float threshold){
    buff.begin();
    binSize = abs(app->endBin - app->startBin);
    ofClear(0);
    float height = ofGetHeight();
    for(int i = 0, j = app->startBin + ofMap(app->startTime, 0, 1, 0, binSize, true); i < binSize; i++, j++, j%= binSize) {
        ofVec3f vertex = myMesh.getVertex(i);
        float newHeight = ofMap(drawBins->at(j), 0.0, 0.1, 0, height * app->historyScale, true);
        ofColor col = app->getColor(j, app->soundPlayer->getPositionMS());
        myMesh.setColor(i, col);
        myMesh.setVertex(i, ofVec3f(vertex.x, yOffset + newHeight - app->yOffset, vertex.z));
    }

    yOffset += 10 * app->drawSpeed;
    
    myMesh.draw();
    
    ofPushStyle();
    if(yOffset > ofGetHeight()) {
        yOffset = 0;
        ofSetColor(0);
        ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    }else if(yOffset < 0){
        yOffset = ofGetHeight();
        ofSetColor(0);
        ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    }
    ofPopStyle();
    buff.end();
    buff.draw(0, 0, 1606, ofGetHeight()); // 1500 for 8x10
}

void History::reset(){
    float x = 0;
    float y = ofGetHeight()/2;
    
    myMesh.clear();
    for(int i = 0; i < binSize; i++) {
        myMesh.addVertex(ofVec3f(x, y, 0));
        myMesh.addColor(ofColor(255));
        x += ofGetWidth()/(float)binSize*4;
    }
    yOffset = 0;
}
