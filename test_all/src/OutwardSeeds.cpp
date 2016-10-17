#include "OutwardSeeds.h"

//------------------------------- Seed -------------------------------------
void Seed::setup(){
    reset();
}

void Seed::draw(ofxAudioVisualApp* app, vector<float>* drawBins, float threshold){
    fbo.begin();
        if(app->backgroundRefresh){
            ofClear(0);
        }
        ofTranslate(cx, cy);
        
        int binSize = abs(app->endBin - app->startBin) + 1;
        ofBeginShape();
        ofNoFill();
        for(int i = 0, j = app->startBin; i < binSize; i++, j++) {
            float theta = M_TWO_PI * i/binSize;
            
            float x = radius * cos(theta);
            float y = radius * sin(theta);
            float z = ofMap(drawBins->at(i), 0.0, 0.05, 0, 100);
            
            ofColor col = app->getColor(j, app->soundPlayer->getPositionMS());
            ofSetColor(col);
            
            ofCurveVertex(x, y, z);
        }
        ofEndShape(true);
        
        radius += 0.1 * app->drawSpeed;
    fbo.end();
    
    fbo.draw(0,0);
    
}

void Seed::reset(){
    fbo.clear();
    fbo.allocate(ofGetScreenWidth(), ofGetScreenHeight());
    fbo.begin();
        ofClear(0);
    fbo.end();
    
    cx = ofRandom(0, ofGetScreenWidth());
    cy = ofRandom(0, ofGetScreenHeight());
    radius = 0;
    active = false;
}

//------------------------------- Display -------------------------------------
void OutwardSeeds::setup(){
    seeds.resize(10);
    activeSeeds.clear();
    
    for(int i = 0; i < seeds.size(); i++){
        seeds[i].setup();
    }
    
    Seed* initialSeed = &seeds[(int)ofRandom(seeds.size())];
    initialSeed->active = true;
    activeSeeds.push_back(initialSeed);
}

void OutwardSeeds::draw(ofxAudioVisualApp* app, vector<float>* drawBins, float threshold){
    vector<Seed*> newActiveSeeds;
    
    for (int i = 0; i < activeSeeds.size(); i++){
        
        for (int j = 0; j < seeds.size(); j++){
            if(seeds[j].active) continue;
            
            bool collided = collisionDetect(activeSeeds[i], &seeds[j]);
            if (collided) {
                seeds[j].active = true;
                newActiveSeeds.push_back(&seeds[j]);
            }
        }
        
        activeSeeds[i]->draw(app, drawBins, threshold);
    }
//    ofLog()<<newActiveSeeds.size();
    activeSeeds.insert(activeSeeds.end(), newActiveSeeds.begin(), newActiveSeeds.end());
}

void OutwardSeeds::reset(){
    for(int i = 0; i < seeds.size(); i++){
        seeds[i].reset();
        activeSeeds.clear();
    }
    
    Seed* initialSeed = &seeds[(int)ofRandom(10)];
    initialSeed->active = true;
    activeSeeds.push_back(initialSeed);
}

bool OutwardSeeds::collisionDetect(Seed* origin, Seed* target){
    if(ofDistSquared(origin->cx, origin->cy, target->cx, target->cy) < (origin->radius * origin->radius)){
        return true;
    }else{
        return false;
    }
}
