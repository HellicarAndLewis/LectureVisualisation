#include "OutwardPath.h"

void OutwardPath::setup(ofxFft* fft){
    reset();
}

void OutwardPath::draw(ofxAudioVisualApp* app, vector<float>* drawBins, float threshold){
    fbo.begin();
        if(app->backgroundRefresh){
            ofClear(0);
        }
        ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
        
        int binSize = abs(app->endBin - app->startBin) + 1;
        ofBeginShape();
        ofNoFill();
        for(int i = 0, j = app->startBin; i < binSize; i++, j++) {
            float theta = M_TWO_PI * i/binSize;
            
            float x = radius * cos(theta);
            float y = radius * sin(theta);
            float z = ofMap(drawBins->at(i), 0.0, 0.05, 0, 100);
            
            ofColor col = app->getColor(j);
            ofSetColor(col);
            
            ofCurveVertex(x, y, z);
        }
        ofEndShape(true);
        
        radius += 0.1 * app->drawSpeed;
    fbo.end();
    
    fbo.draw(0,0);
    
}

void OutwardPath::reset(){
    fbo.clear();
    fbo.allocate(ofGetScreenWidth(), ofGetScreenHeight());
    fbo.begin();
        ofClear(0);
    fbo.end();
    
    radius = 0;
}