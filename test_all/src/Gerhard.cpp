#include "Gerhard.h"

void Gerhard::setup(){
    baseColor = ofColor(255, 255, 0);
}

void Gerhard::draw(ofxAudioVisualApp* app, vector<float>* drawBins, float threshold) {
    ofPushMatrix();
    ofPushStyle();

    int binSize = abs(app->endBin - app->startBin);
    for(int i = app->startBin, j = 0; j < binSize; i++, j++){
        ofColor col;
        if(drawBins->at(i) > threshold){
            col = app->getColor(i, app->soundPlayer->getPositionMS());
        }else{
            col = (0,0,0);
        }
        
        ofSetColor(col);

        float height;
        height = ofMap(i, app->startBin, binSize, 0, ofGetHeight());

        ofDrawCircle(x, height, 2);
    }
    
    ofPopStyle();
    ofPopMatrix();
    
    x += 1 * app->drawSpeed;
    if(x > ofGetWidth()){
        x = 0;
    }else if(x < 0){
        x = ofGetWidth();
    }
}

void Gerhard::reset(){
    x = 0;
}
