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
    ofMesh mesh;
    
    int yOffset;
};

#endif /* ofApp_hpp */
