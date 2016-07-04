//
//  ofApp.h
//  Skeleton
//
//  Created by cafe on 04/07/2016.
//
//

#ifndef ofApp_h
#define ofApp_h

#include "ofxAudioVisualApp.h"

class ofApp : public ofxAudioVisualApp {
public:
    void setup();
    void draw();
    
    ofParameter<float> size;
    ofShader shader;
    ofImage image;
    ofFbo buffer;
};

#endif /* ofApp_hpp */
