#pragma once

#include "ofMain.h"

class GradientSampler {
public:
    void setup();
    void update(float x);
    void draw(float x, float y, float w, float h);
    float getBrightness(int i);
    
    ofImage image;
    
    float sampleX;
};