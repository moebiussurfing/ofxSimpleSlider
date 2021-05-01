#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	canvas.bGui = bGui;

	canvas.setVisibleOnlyIfHoverX(true);
}

//--------------------------------------------------------------
void ofApp::update() {
}

//--------------------------------------------------------------
void ofApp::draw() {

	//filled
	ofFill();
	int alpha = 255;
	ofSetColor(ofColor::red, alpha);
	ofDrawRectangle(canvas.r1);
	ofSetColor(ofColor::green, alpha);
	ofDrawRectangle(canvas.r2);
	ofSetColor(ofColor::blue, alpha);
	ofDrawRectangle(canvas.r3);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	ofLogNotice(__FUNCTION__) << key;

	if (key == 'G') canvas.bGui = !canvas.bGui;
}