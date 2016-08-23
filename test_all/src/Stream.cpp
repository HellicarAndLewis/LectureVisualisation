#include "Stream.h"

void Stream::setup(){
    fbo.allocate(ofGetWidth(), ofGetHeight());
    fbo.begin();
    ofClear(0);
    fbo.end();
    
    fbo2.allocate(ofGetWidth(), ofGetHeight());
    fbo2.begin();
    ofClear(0);
    fbo2.end();
    
    x = 0;
}

void Stream::draw(ofxAudioVisualApp* app, vector<float>* drawBins, float threshold){
    fbo.begin();
        drawFbo(app, drawBins, threshold);
    fbo.end();
    
    if(!(x > ofGetWidth())){
        ofTranslate(x-ofGetWidth(), 0);
    }
    
    fbo.draw(0,0);
    
    x += 1 * app->drawSpeed;
}

void Stream::drawFbo(ofxAudioVisualApp* app, vector<float>* drawBins, float threshold){    
    for(int i = app->startBin; i < app->endBin; i++){
        ofColor col;
        if(drawBins->at(i) > threshold){
            col = app->getColor(i);
        }else{
            col = (0,0,0);
        }
        ofSetColor(col);
        
        if (!(x > ofGetWidth())){
            ofDrawCircle(ofGetWidth() - x, ofMap(i, app->startBin, app->endBin, 0, ofGetHeight()), 2);
        }else{
            ofDrawCircle(0, ofMap(i, app->startBin, app->endBin, 0, ofGetHeight()), 2);
        }
    }
}