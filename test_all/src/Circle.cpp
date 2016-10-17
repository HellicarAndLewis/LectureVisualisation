#include "Circle.h"

void Circle::draw(ofxAudioVisualApp* app, vector<float>* drawBins, float threshold){
    ofPushMatrix();
    ofPushStyle();
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    ofRotate(theta, 0, 0, 1);
    
    int binSize = abs(app->endBin - app->startBin);
    for(int i = app->startBin, j = 0; j < binSize; i++, j++) {
        ofColor col;
        if(drawBins->at(i) > threshold){
            col = app->getColor(i, app->soundPlayer->getPositionMS());
        }else{
            col = (0,0,0);
        }
        ofSetColor(col);
        ofDrawCircle(0, ofMap(i, app->startBin, binSize, 0, 500, true), 2);
    }
    
    ofPopStyle();
    ofPopMatrix();
    
    theta += 0.1 * app->drawSpeed;
    if(theta > 360){
        theta = 0;
    }else if(theta < 0){
        theta = 360;
    }
}

void Circle::reset(){
    theta = 0;
}
