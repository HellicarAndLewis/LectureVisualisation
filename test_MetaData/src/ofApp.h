#pragma once

#include "ofxAudioVisualApp.h"

class ofApp : public ofxAudioVisualApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);

		void guiKeyPressed(ofKeyEventArgs & args);

		//void onSettingChanged(ofAbstractParameter &p);
		//void onVisualizationChanged(ofAbstractParameter &p);
		//void onBinSizeChanged(ofAbstractParameter &p);

		//void reset();

		ofxPanel gui;

		ofParameter<int> month;
		ofParameter<int> day;
		ofParameter<int> hour;
		ofParameter<int> minute;
		ofParameter<int> duration;


		void setupGui();
		void drawGui(ofEventArgs & args);

		ofVec2f velocity;
		ofVec2f position;
		//void guiKeyPressed(ofKeyEventArgs & args);
};
