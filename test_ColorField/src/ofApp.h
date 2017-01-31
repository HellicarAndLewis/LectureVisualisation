#pragma once

#include "ofMain.h"

//#define COLOR_ON_VOLUME

class ofApp : public ofBaseApp{

	struct text {
		string displayText;
		float rotation;
		ofVec2f position;
		ofColor col;
		ofImage img;
		ofFbo textBuffer;
		void draw() {
			ofPushMatrix();
			ofSetColor(col);
			ofTranslate(position);
			ofRotate(rotation);
			textBuffer.draw(0, 0);
			//ofDrawBitmapString(displayText, 0, 0);
			ofPopMatrix();
		}
		void renderText(string _text) {
			displayText = _text;
			textBuffer.allocate((_text.size() - 1) * 10, 10);
			textBuffer.begin();
			ofSetColor(0, 0, 0, 0);
			ofDrawRectangle(0, 0, textBuffer.getWidth(), textBuffer.getHeight());
			ofSetColor(255);
			ofDrawBitmapString(_text, 0, 10);
			textBuffer.end();
		}
	};

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		void drawTimeTarget(float angle, ofColor col);
		float calculateTimeAngle(string time);

		void renderTimeSweep(float angle1, float angle2, ofColor col);

		float* spectrum;

		ofFbo sweepBuffer;

		ofSoundPlayer player;
		float x;
		float y;
		float brightness;
		ofColor col;

		text title;
		text startTime;
		text endTime;
		text duration;
		text dayOfWeek;
		text date;
		text speaker;

		float timeAngle;
		float startTimeAngle;
		float endTimeAngle;

		float songDuration;

		float border;

		float stepInterval;

		float timeOfLastStep;

		float timePercentage;

		float durationPercentage;

		bool singlePoint;

		ofVec2f lastPoint;

		ofColor baseCol; // 8, 58, 146
		ofColor timeCol; // 207, 141, 149
};
