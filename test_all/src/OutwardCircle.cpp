#include "OutwardCircle.h"

void OutwardCircle::setup(ofxFft* fft){
    mesh.setMode(OF_PRIMITIVE_LINE_LOOP);
    
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    for(int i = 0; i < fft->getBinSize(); i++) {
        mesh.addVertex(ofVec3f(0, 0, 0));
        mesh.addColor(ofColor(255));
    }
    ofPopMatrix();
    
    radius = 0;
}

void OutwardCircle::draw(ofxAudioVisualApp* app, vector<float>* drawBins, float threshold){
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    
    int binSize = abs(app->endBin - app->startBin) + 1;
    
    if(binSize != mesh.getNumVertices()){
        resizeMesh(binSize);
    }
    
    for(int i = 0, j = app->startBin; i < binSize; i++, j++) {
        float theta = M_TWO_PI * i/binSize;
        
        float x = radius * cos(theta);
        float y = radius * sin(theta);
        float z = ofMap(drawBins->at(i), 0.0, 0.1, 0, 50);
        
        ofColor col = app->getColor(j, app->soundPlayer->getPositionMS());
        mesh.setColor(i, col);
        
        mesh.setVertex(i, ofVec3f(x, y, z));
    }
    
    radius += 0.1 * app->drawSpeed;
    
    mesh.draw();
    
//    if(radius > min(ofGetHeight()/2, ofGetWidth()/2)){
//        radius = 0;
//    }
}

void OutwardCircle::reset(){
    radius = 0;
}

void OutwardCircle::resizeMesh(int size){
    mesh.clear();
    
    for(int i = 0; i < size; i++) {
        mesh.addVertex(ofVec3f(0, 0, 0));
        mesh.addColor(ofColor(255));
    }
}
