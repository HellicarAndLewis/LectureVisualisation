#include "ofApp.h"

#define TARGET_SIZE 20
#define SIZE 25

float mapNonLinear(float in, float inMin, float inMax, float outMin, float outMax, float shaper) {
	// (1) convert to pct (0-1)
	float pct = ofMap(in, inMin, inMax, 0, 1, true);
	// raise this number to a power
	pct = powf(pct, shaper);
	float out = ofMap(pct, 0, 1, outMin, outMax, true);
	return out;
}
//--------------------------------------------------------------
void ofApp::setup(){
	//ofSetDataPathRoot("../../../../SharedData");

	player.load("lectures/Damned Statistics.mp3");

	player.play();
	player.setPosition(0.9999f);
	float speed = 5.0f;
	player.setSpeed(speed);
	songDuration = player.getPositionMS();
	cout << player.getPositionMS() << endl;
	songDuration /= speed;
	player.setPosition(0);
	player.stop();

	ofSetBackgroundAuto(false);

	singlePoint = true;

	border = 30;

	float numTotalStepsToTake = (ofGetWidth() - border) * (ofGetHeight() - border);

	float frameRate = numTotalStepsToTake / songDuration;
	frameRate *= 1000;

	baseCol = ofColor(82, 130, 255);
	timeCol = ofColor(255, 0, 0);

	x = border;
	y = border;
	brightness = 0;
	col = baseCol;

	//Setup our display text pieces:
	startTime.renderText("18:10");
	endTime.renderText("18:55");

	//split up the time get the duration
	vector<string> startTimeSplit = ofSplitString(startTime.displayText, ":");
	vector<string> endTimeSplit = ofSplitString(endTime.displayText, ":");
	int durationHours = ofToInt(endTimeSplit[0]) - ofToInt(startTimeSplit[0]);
	int durationMinutes = ofToInt(endTimeSplit[1]) - ofToInt(startTimeSplit[0]);
	float totalDuration = durationHours * 60 + durationMinutes;

	float startPercentage = ofMap(ofToInt(startTimeSplit[0]) % 12, 0, 12, 0, 1);
	float endPercentage = ofMap(ofToInt(endTimeSplit[0]) % 12, 0, 12, 0, 1);

	timePercentage = (startPercentage + endPercentage) / 2;

	durationPercentage = ofMap(totalDuration, 30, 60, 0.1, 0.7);

	// set the position of our start and end time display text:
	startTime.position.x = ofMap(ofToInt(startTimeSplit[0])%12, 0, 12, 0, ofGetWidth());
	startTime.position.y = border/2;
	startTime.rotation = 0;
	startTime.col = ofColor(255);

	endTime.position.x = ofMap(ofToInt(endTimeSplit[0])%12, 0, 12, 0, ofGetWidth());
	endTime.position.y = border / 2;
	endTime.rotation = 0;
	endTime.col = ofColor(255);
	
	duration.renderText(ofToString(totalDuration));

	title.renderText("Simon Kovesi");
	title.rotation = -90;
	title.position.x = 15;
	title.position.y = ofMap(totalDuration, 30, 180, ofGetHeight()-10, ofGetHeight() / 2, true);

	speaker.renderText("Working Class Literature");

	speaker.rotation = -90;
	speaker.position.x = 15;
	speaker.position.y = speaker.textBuffer.getWidth() + 20;

	dayOfWeek.renderText("Tuesday");

	date.renderText("7/1/2017");
	date.rotation = 0;
	date.position.x = ofGetWidth() - 100;
	date.position.y = 15;

	//Calculate the time angle for displaying our target
	startTimeAngle = calculateTimeAngle(startTime.displayText);
	endTimeAngle = calculateTimeAngle(endTime.displayText);

	renderTimeSweep(startTimeAngle, endTimeAngle, ofColor(255, 255, 0));

	ofSetFrameRate(frameRate);

	ofHideCursor();
	//player.play();

	ofBackground(0);
}

//--------------------------------------------------------------
void ofApp::update(){
	if (player.isPlaying()) {
		spectrum = ofSoundGetSpectrum(1);
		brightness = ofMap(*spectrum, 0, 0.06, 0.2, 2.0);
#ifdef COLOR_ON_VOLUME
		col = baseCol.getLerped(timeCol, brightness);
#endif
		lastPoint.x = x;
		lastPoint.y = y;
		y+=SIZE;
		if (y >= ofGetHeight()) {
			y = border;
			x+=SIZE;
		}
	}
#ifndef COLOR_ON_VOLUME
	float percentDownThePage = x / ofGetWidth();
	float diff = abs(timePercentage - percentDownThePage);
	float dist = mapNonLinear(diff, 0.0, timePercentage, 1.0, 0.0, durationPercentage);
	col = baseCol.getLerped(timeCol, dist);
#endif
}

//--------------------------------------------------------------
void ofApp::draw(){
	if (singlePoint) {
		ofSetColor(0);
		ofDrawRectangle(lastPoint.x, lastPoint.y, SIZE, SIZE);
	}
	ofSetColor(col * brightness);
	ofDrawRectangle(x, y, SIZE, SIZE);


	ofSetColor(255);
	//startTime.buff.draw(ofGetWidth() / 2, ofGetHeight() / 2);

	//startTime.draw();
	//endTime.draw();
	//title.draw();
	//speaker.draw();
	//date.draw();

	//sweepBuffer.draw(0, 0);

	//ofDrawBitmapStringHighlight(ofToString(ofGetFrameRate()), 10, 10);

}

//--------------------------------------------------------------
void ofApp::drawTimeTarget(float angle, ofColor col)
{
	ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
	ofRotate(angle);
	ofTranslate(0, -ofGetWidth() / 2 + TARGET_SIZE);
	ofSetColor(col);
	ofDrawCircle(0, 0, 1);
	//ofDrawLine(-TARGET_SIZE, 0, TARGET_SIZE, 0);
	//ofDrawLine(0, -TARGET_SIZE, 0, TARGET_SIZE);
}

void ofApp::renderTimeSweep(float angle1, float angle2, ofColor col) {
	sweepBuffer.allocate(ofGetWidth(), ofGetHeight());
	sweepBuffer.begin();
	ofSetColor(0, 0, 0, 0);
	ofDrawRectangle(0, 0, sweepBuffer.getWidth(), sweepBuffer.getHeight());
	float timeAngle = angle1;
	ofSetColor(col);
	for (float percent = 0.0; percent < 1.0; percent += 0.01) {
		timeAngle = ofLerp(angle1, angle2, percent);
		ofPushMatrix();
		drawTimeTarget(timeAngle, ofColor(255, 255, 0));
		ofPopMatrix();
	}
	sweepBuffer.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == ' ') {
		if (player.isPlaying()) {
			player.stop();
			x = border;
			y = border;
			ofSetBackgroundAuto(true);
		}
		else {
			player.play();
			ofSetBackgroundAuto(false);
		}
	}
	else if (key == 'p') {
		singlePoint = !singlePoint;
	}
    else if (key == 'f') {
        ofToggleFullscreen();
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

float ofApp::calculateTimeAngle(string time)
{
	vector<string> timeSplit = ofSplitString(time, ":");
	int hour = ofToInt(timeSplit[0]);
	int minute = ofToInt(timeSplit[1]);

	hour %= 12;

	float hourAngle = ofMap(hour, 0, 12, 0, 360);
	float minuteAngle = ofMap(minute, 0, 60, 0, 360 / 12);

	float totalAngle = hourAngle + minuteAngle;

	return totalAngle;
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
