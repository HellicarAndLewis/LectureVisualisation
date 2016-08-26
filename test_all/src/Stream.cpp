#include "Stream.h"

void Stream::setup(){
    fbo.allocate(ofGetWidth(), ofGetHeight());
    fbo.begin();
        ofClear(0);
    fbo.end();
}

void Stream::draw(ofxAudioVisualApp* app, vector<float>* drawBins, float threshold){
    fbo.readToPixels(pixels);
    image.setFromPixels(pixels);
    image.update();
    
    fbo.begin();
        drawFbo(app, drawBins, threshold);
    fbo.end();
    
    fbo.draw(0,0);
}

void Stream::drawFbo(ofxAudioVisualApp* app, vector<float>* drawBins, float threshold){
    image.draw(app->drawSpeed, 0);
    
    for(int i = app->startBin; i < app->endBin; i++){
        ofColor col;
        if(drawBins->at(i) > threshold){
            col = app->getColor(i);
        }else{
            col = (0,0,0);
        }
        ofSetColor(col);
        
        ofDrawCircle(0, ofMap(i, app->startBin, app->endBin, 0, ofGetHeight()), 2);
    }
}