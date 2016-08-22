#include "History.h"

void History::setup(ofxFft* fft){
    mesh.setMode(OF_PRIMITIVE_LINE_STRIP);
    float x = 0;
    float y = ofGetHeight()/2;
    for(int i = 0; i < fft->getBinSize(); i++) {
        mesh.addVertex(ofVec3f(x, y, 0));
        mesh.addColor(ofColor(255));
        x += ofGetWidth()/fft->getBinSize()*2;
    }
    yOffset = 10;
}

void History::draw(ofxAudioVisualApp* app, vector<float>* drawBins, float threshold){
    binSize = app->endBin - app->startBin;
    for(int i = 0, j = app->startBin; i < binSize; i++, j++) {
        ofVec3f vertex = mesh.getVertex(i);
        float newHeight = ofMap(drawBins->at(j), 0.0, 0.1, 0, ofGetHeight()/2, true);
        ofColor col = app->getColor(j);
        mesh.setColor(i, col);
        mesh.setVertex(i, ofVec3f(vertex.x, yOffset + newHeight, vertex.z));
    }
    
//    for(int i = 0; i < drawBins->size(); i++) {
//        ofVec3f vertex = mesh.getVertex(i);
//        float newHeight = ofMap(drawBins->at(i), 0.0, 0.1, 0, ofGetHeight()/2, true);
//        ofColor col = app->getColor(i);
//        mesh.setColor(i, col);
//        mesh.setVertex(i, ofVec3f(vertex.x, yOffset + newHeight, vertex.z));
//    }
    
    yOffset += 10 * app->drawSpeed;
    
    if(yOffset > ofGetHeight()) {
        yOffset = 0;
        ofSetColor(0);
        ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    }
    
    ofSetColor(255);
    mesh.draw();
}

void History::resetMesh(){
    float x = 0;
    float y = ofGetHeight()/2;
    
    mesh.clear();
    for(int i = 0; i < binSize; i++) {
        mesh.addVertex(ofVec3f(x, y, 0));
        mesh.addColor(ofColor(255));
        x += ofGetWidth()/(float)binSize*4;
    }
    yOffset = 10;
}
