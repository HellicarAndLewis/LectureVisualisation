#include "util_GradientSampler.h"

void GradientSampler::setup(){
    image.load("./images/checkerbox.jpg");
    sampleX = 0;
}

void GradientSampler::update(float x){
    sampleX = ofMap(x, 0, ofGetWidth(), 0, image.getWidth());
    
    if(sampleX > image.getWidth()){
        sampleX = 0;
    }
}

void GradientSampler::draw(float x, float y, float w, float h){
    image.draw(x, y, w, h);
    
    ofPushMatrix();
    ofPushStyle();
    
    ofTranslate(ofMap(sampleX, 0, image.getWidth(), 0, 200, true), 0);
    
    ofNoFill();
    ofSetColor(255);
    ofSetLineWidth(2);
    ofDrawRectangle(x, y, 4, h);
    
    ofPopStyle();
    ofPopMatrix();
}

float GradientSampler::getBrightness(int i){
    float y = ofMap(i, 0, ofGetHeight(), 0, image.getHeight());
    ofColor color = image.getColor(sampleX, y);
    
    return color.getBrightness();
}